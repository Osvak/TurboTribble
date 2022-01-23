#include "ModuleUI.h"

#include "Globals.h"
#include "Application.h"
#include "ModuleCamera3D.h"
#include "ModuleScene.h"
#include "ModuleInput.h"
#include "ModuleEditor.h"

#include "2DTransformComponent.h"
#include "UIButtonComponent.h"
#include "UICheckBoxComponent.h"
#include "UIImageComponent.h"
#include "UIInputBoxComponent.h"
#include "UISliderComponent.h"

#include "CameraComponent.h"
#include "MaterialComponent.h"

#include <stack>
#include "glew/include/GL/glew.h"
#include <GL/gl.h>
#include "MathGeoLib/src/Geometry/Frustum.h"

//#include <ft2build.h>
//#include FT_FREETYPE_H 

Shader::Shader()
{
	// 1. retrieve the vertex/fragment source code from filePath
	std::string vertexCode = "#version 330 core\n  in vec4 vertex;\n out vec2 TexCoords;\n  uniform mat4 projection;\n  void main() {\n  gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);\n  TexCoords = vertex.zw; };";
	std::string fragmentCode = "#version 330 core\n  in vec2 TexCoords;\n  out vec4 color;\n  uniform sampler2D text;\n  uniform vec3 textColor;\n  void main() {\n  vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);\n  color = vec4(textColor, 1.0) * sampled;};"; //color = vec4(textColor, 1.0) * sampled;};";

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	// 2. compile shaders
	unsigned int vertex, fragment;
	// vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	CheckCompileErrors(vertex, "VERTEX");
	// fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	CheckCompileErrors(fragment, "FRAGMENT");

	// shader Program
	id = glCreateProgram();
	glAttachShader(id, vertex);
	glAttachShader(id, fragment);

	glLinkProgram(id);
	CheckCompileErrors(id, "PROGRAM");
	// delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertex);
	glDeleteShader(fragment);


}
// Activate the shader
// ------------------------------------------------------------------------
void Shader::Use()
{
	glUseProgram(id);
}
// Deactivate the shader
// ------------------------------------------------------------------------
void Shader::Stop()
{
	glUseProgram(0);
}
// utility function for checking shader compilation/linking errors.
// ------------------------------------------------------------------------
void Shader::CheckCompileErrors(GLuint shader, std::string type)
{
	GLint success;
	GLchar infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}

ModuleUI::ModuleUI(Application* app, bool startEnabled) : Module(startEnabled)
{
	UIGameObjectFocused = nullptr;
	UIGameObjectSelected = nullptr;
}
ModuleUI::~ModuleUI()
{
	UIGameObjectFocused = nullptr;
	UIGameObjectSelected = nullptr;
}


bool ModuleUI::Start()
{
	
	return true;
}
bool ModuleUI::PreUpdate(float dt)
{
	if (app->scene->GetGameState() == GameState::PLAYING)
	{
		float2 mousePos = { (float)app->input->GetMouseX() ,(float)app->input->GetMouseY() };
		float2 mPos = { ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y };
		float4 viewport = app->editor->GetViewport()->GetBounds();
		mousePos = { mPos.x - viewport.x , mPos.y - viewport.y };

		if (mousePos.x > viewport.x && mousePos.x < viewport.x + viewport.z && mousePos.y > viewport.y && mousePos.y < viewport.y + viewport.w)
		{
			for (int i = 0; i < UIGameObjects.size(); i++)
			{
				GameObject* go = UIGameObjects[i];
				Transform2DComponent* transform2D = go->GetComponent<Transform2DComponent>();

				float posXMin = ((viewport.z / 2) + (transform2D->position.x)) - (transform2D->buttonWidth / 2);
				float posXMax = ((viewport.z / 2) + (transform2D->position.x)) + (transform2D->buttonWidth / 2);

				float posYMin = ((viewport.w / 2) + (-transform2D->position.y)) - (transform2D->buttonHeight / 2);
				float posYMax = ((viewport.w / 2) + (-transform2D->position.y)) + (transform2D->buttonHeight / 2);

				if ((mousePos.x > posXMin && mousePos.x < posXMax && mousePos.y > posYMin && mousePos.y < posYMax) && go->GetComponent<UIImageComponent>() == nullptr)
				{
					hitObjs.push_back(go);
				}
			}

			if (hitObjs.size() > 0)
			{
				std::vector<float> distance;
				float nearestDistance = 100000.0f;
				int nearObj = 0;
				for (int i = 0; i < hitObjs.size(); ++i)
				{
					distance.push_back(hitObjs[i]->GetComponent<Transform2DComponent>()->position.z);
					if (distance[i] < nearestDistance)
					{
						nearestDistance = distance[i];
						nearObj = i;
					}
				}
				UIGameObjectFocused = hitObjs[nearObj];
				UIGameObjectSelected = nullptr;
				hitObjs.clear();
			}
			else
				UIGameObjectFocused = nullptr;
		}
	}

	return true;
}
bool ModuleUI::Update(float dt)
{
	// Update All UI Components

	/*if (App->gameMode)
	{*/
	if (!UIGameObjects.empty() && app->input->GetKey(SDL_SCANCODE_TAB) == KeyState::KEY_DOWN)
	{
		if (!UIGameObjectSelected)
			UIGameObjectSelected = UIGameObjects[0];
		else
		{
			if (nextUIGameObject != UIGameObjects.size())
			{
				UIGameObjectSelected = UIGameObjects[nextUIGameObject];
				nextUIGameObject++;
			}
			else
			{
				UIGameObjectSelected = UIGameObjects[0];
				nextUIGameObject = 1;
			}
		}
	}

	for (int i = 0; i < UIGameObjects.size(); i++)
	{
		GameObject* go = UIGameObjects[i];

		int button = go->GetComponentID(ComponentType::UI_BUTTON);
		int checkbox = go->GetComponentID(ComponentType::UI_CHECKBOX);
		int image = go->GetComponentID(ComponentType::UI_IMAGE);
		int inputbox = go->GetComponentID(ComponentType::UI_INPUTBOX);
		int slider = go->GetComponentID(ComponentType::UI_SLIDER);

		std::vector<Component*> components = go->GetComponents();

		if (button != -1)
		{
			components[button]->Update(dt);
			UIButtonComponent* auxiliar = go->GetComponent<UIButtonComponent>();
			defaultText = auxiliar->buttonText;
			color.x = auxiliar->textColor.r;
			color.y = auxiliar->textColor.g;
			color.z = auxiliar->textColor.b;
		}
		if (checkbox != -1)
		{
			components[checkbox]->Update(dt);
			UICheckBoxComponent* auxiliar = go->GetComponent<UICheckBoxComponent>();
			defaultText = auxiliar->text;
			color.x = auxiliar->textColor.r;
			color.y = auxiliar->textColor.g;
			color.z = auxiliar->textColor.b;
		}
		if (image != -1)
			components[image]->Update(dt);
		if (inputbox != -1)
		{
			components[inputbox]->Update(dt);
			UIInputBoxComponent* auxiliar = go->GetComponent<UIInputBoxComponent>();
			defaultText = auxiliar->text;
			color.x = auxiliar->textColor.r;
			color.y = auxiliar->textColor.g;
			color.z = auxiliar->textColor.b;
		}

		if (slider != -1)
		{
			components[slider]->Update(dt);
			UISliderComponent* auxiliar = go->GetComponent<UISliderComponent>();
			defaultText = auxiliar->text;
			color.x = auxiliar->textColor.r;
			color.y = auxiliar->textColor.g;
			color.z = auxiliar->textColor.b;
		}
	}

	return true;
}
bool ModuleUI::PostUpdate()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);

	glPushMatrix();

	app->editor->;
	app->viewportBuffer->Bind(app->camera->GameCam);

	Frustum frustum;
	frustum.SetPos(float3::zero);
	frustum.SetFront(float3::unitZ);
	frustum.SetUp(float3::unitY); //COGED EL UP DE LA CAMARA DE JUEGO
	frustum.SetKind(FrustumProjectiveSpace::FrustumSpaceGL, FrustumHandedness::FrustumRightHanded);
	frustum.orthographicHeight = app->camera->GameCam->size.y; //PONER EL TAMAÑO DEL VIEWPORT DONDE QUERAIS PINTAR
	frustum.orthographicWidth = app->camera->GameCam->size.x; //PONER EL TAMAÑO DEL VIEWPORT DONDE QUERAIS PINTAR
	frustum.SetViewPlaneDistances(0.1f, 1000.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(frustum.ProjectionMatrix().Transposed().ptr());
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	std::vector<GameObject*> orderedGameObjects;
	std::vector<uint> orderedIndices;

	for (int i = 0; i < UIGameObjects.size(); i++)
	{
		orderedIndices.push_back(i);
	}

	if (UIGameObjects.size() > 1)
	{
		for (int i = 0; i < (UIGameObjects.size() - 1); i++)
		{
			for (int j = 0; j < (UIGameObjects.size() - i - 1); j++)
			{
				if (UIGameObjects[j]->GetComponent<Transform2DComponent>()->position.z <= UIGameObjects[j + 1]->GetComponent<Transform2DComponent>()->position.z)
				{
					uint temp = j;
					orderedIndices[j] = orderedIndices[j + 1];
					orderedIndices[j + 1] = temp;
				}
			}
		}

		for (int i = 0; i < orderedIndices.size(); i++)
		{
			orderedGameObjects.push_back(UIGameObjects[orderedIndices[i]]);
		}

		for (int i = 0; i < orderedGameObjects.size(); i++)
		{
			GameObject* go = orderedGameObjects[i];

			int button = go->GetComponentID(ComponentType::UI_BUTTON);
			int checkbox = go->GetComponentID(ComponentType::UI_CHECKBOX);
			int image = go->GetComponentID(ComponentType::UI_IMAGE);
			int inputbox = go->GetComponentID(ComponentType::UI_INPUTBOX);
			int slider = go->GetComponentID(ComponentType::UI_SLIDER);

			std::vector<Component*> components = go->GetComponents();

			if (button != -1)
			{
				components[button]->Draw();
				UIButtonComponent* auxiliar = go->GetComponent<UIButtonComponent>();
				RenderText(auxiliar->buttonText.textt, auxiliar->buttonText.X, auxiliar->buttonText.Y, auxiliar->buttonText.Scale, auxiliar->buttonText.Color);
			}
			if (checkbox != -1)
			{
				components[checkbox]->Draw();
				UICheckBoxComponent* auxiliar = go->GetComponent<UICheckBoxComponent>();
				RenderText(auxiliar->checkboxText.textt, auxiliar->checkboxText.X, auxiliar->checkboxText.Y, auxiliar->checkboxText.Scale, auxiliar->checkboxText.Color);
			}
			if (image != -1)
			{
				components[image]->Draw();
			}
			if (inputbox != -1)
			{
				components[inputbox]->Draw();
				UIInputBoxComponent* auxiliar = go->GetComponent<UIInputBoxComponent>();
				RenderText(auxiliar->aux.textt, auxiliar->aux.X, auxiliar->aux.Y, auxiliar->aux.Scale, auxiliar->aux.Color);
			}
			if (slider != -1)
			{
				components[slider]->Draw();
				UISliderComponent* auxiliar = go->GetComponent<UISliderComponent>();
				RenderText(auxiliar->sliderText.textt, auxiliar->sliderText.X, auxiliar->sliderText.Y, auxiliar->sliderText.Scale, auxiliar->sliderText.Color);
			}
		}

		orderedGameObjects.clear();
		orderedIndices.clear();
	}
	else
	{
		for (int i = 0; i < UIGameObjects.size(); i++)
		{
			GameObject* go = UIGameObjects[i];

			int button = go->GetComponentID(ComponentType::UI_BUTTON);
			int checkbox = go->GetComponentID(ComponentType::UI_CHECKBOX);
			int image = go->GetComponentID(ComponentType::UI_IMAGE);
			int inputbox = go->GetComponentID(ComponentType::UI_INPUTBOX);
			int slider = go->GetComponentID(ComponentType::UI_SLIDER);

			std::vector<Component*> components = go->GetComponents();

			if (button != -1)
			{
				components[button]->Draw();
				UIButtonComponent* auxiliar = go->GetComponent<UIButtonComponent>();
				RenderText(auxiliar->buttonText.textt, auxiliar->buttonText.X, auxiliar->buttonText.Y, auxiliar->buttonText.Scale, auxiliar->buttonText.Color);
			}
			if (checkbox != -1)
			{
				components[checkbox]->Draw();
				UICheckBoxComponent* auxiliar = go->GetComponent<UICheckBoxComponent>();
				RenderText(auxiliar->checkboxText.textt, auxiliar->checkboxText.X, auxiliar->checkboxText.Y, auxiliar->checkboxText.Scale, auxiliar->checkboxText.Color);
			}
			if (image != -1)
			{
				components[image]->Draw();
			}
			if (inputbox != -1)
			{
				components[inputbox]->Draw();
				UIInputBoxComponent* auxiliar = go->GetComponent<UIInputBoxComponent>();
				RenderText(auxiliar->aux.textt, auxiliar->aux.X, auxiliar->aux.Y, auxiliar->aux.Scale, auxiliar->aux.Color);
			}
			if (slider != -1)
			{
				components[slider]->Draw();
				UISliderComponent* auxiliar = go->GetComponent<UISliderComponent>();
				RenderText(auxiliar->sliderText.textt, auxiliar->sliderText.X, auxiliar->sliderText.Y, auxiliar->sliderText.Scale, auxiliar->sliderText.Color);
			}
		}
	}

	glEnable(GL_DEPTH_TEST);
	glPopMatrix();
	app->viewportBuffer->UnBind();

	return true;
}
bool ModuleUI::CleanUp()
{
	return true;
}




void ModuleUI::RenderText(std::string text, float x, float y, float scale, float3 color)
{
	// activate corresponding render state	
	shader->Use();
	Frustum frustum;
	frustum.SetPos(app->scene->camera->GetComponent<CameraComponent>()->GetFrustum().Pos());
	frustum.SetFront(app->scene->camera->GetComponent<CameraComponent>()->GetFrustum().Front()); //COGED EL FRONT DE LA CAMARA DE JUEGO
	frustum.SetUp(app->scene->camera->GetComponent<CameraComponent>()->GetFrustum().Pos()); //COGED EL UP DE LA CAMARA DE JUEGO
	frustum.SetKind(FrustumProjectiveSpace::FrustumSpaceGL, FrustumHandedness::FrustumRightHanded);
	//frustum.SetOrthographic(app->scene->camera->GetComponent<CameraComponent>()., app->scene->camera->GetComponent<CameraComponent>()->GetFrustum().Pos());
	frustum.SetViewPlaneDistances(0.1f, 1000000.0f);

	auto p = frustum.ProjectionMatrix();
	glUniform3f(glGetUniformLocation(shader->id, "textColor"), color.x, color.y, color.z);
	glUniformMatrix4fv(glGetUniformLocation(shader->id, "projection"), 1, GL_TRUE, p.Transposed().ptr());
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(vao);

	// iterate through all characters
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = charMap[*c];

		float xpos = x + ch.bearing.x * scale;
		float ypos = y - (ch.size.y - ch.bearing.y) * scale;

		float w = ch.size.x * scale;
		float h = ch.size.y * scale;
		// update VBO for each character
		float vertices[6][4] = {
			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos,     ypos,       0.0f, 1.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },

			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },
			{ xpos + w, ypos + h,   1.0f, 0.0f }
		};
		// render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.textureID);
		// update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	shader->Stop();
}

void ModuleUI::DeleteUIGameObjects()
{
	int UIGameObjectsQuantity = UIGameObjects.size();

	for (int a = UIGameObjectsQuantity - 1; a >= 0; a--)
	{
		app->editor->objectSelected = UIGameObjects[a];
		int i;
		int id = app->editor->objectSelected->id;
		for (i = 0; i < app->scene->gameObjects.size(); i++)
		{
			if (id == app->scene->gameObjects[i]->id)
			{
				app->editor->objectSelected = nullptr;


				for (int i = 0; i < app->userInterface->UIGameObjects.size(); i++)
				{
					if (app->userInterface->UIGameObjects[i]->id == id)
					{
						GameObject* go = app->userInterface->UIGameObjects[i];
						uint comp = go->GetComponentID(ComponentType::UI_IMAGE);
						std::vector<Component*> components = go->GetComponents();
						if (comp == -1 || (comp != -1 && components[comp]->UIid != 10))
						{
							Transform2DComponent* component2d = app->userInterface->UIGameObjects[i]->getTransform2D();
							component2d->position.x = 70000;
							component2d->position.z = 70000;
						}
						break;
					}
				}
				break;
			}
		}
	}

	UIGameObjectSelected = nullptr;
}