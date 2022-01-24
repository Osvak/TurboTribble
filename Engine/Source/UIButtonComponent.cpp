#include "UIButtonComponent.h"

#include "Application.h"
#include "ModuleInput.h"
#include "Primitive.h"

#include "ModuleUI.h"

#include "glew/include/GL/glew.h"

UIButtonComponent::UIButtonComponent(GameObject* own, std::string text)
{
	type = ComponentType::UI_BUTTON;
	owner = own;
	buttonText.SetText(text, float2(5, 5), 0.5f, float4(255, 255, 255, 255));
}

UIButtonComponent::~UIButtonComponent()
{

}

bool UIButtonComponent::Update(float dt)
{

	if (active == false)
	{
		buttonState = UIState::DISABLED;
	}

	if (buttonState != UIState::DISABLED)
	{
		if (app->ui->UIGameObjectFocused == owner)
		{
			buttonState = UIState::FOCUSED;

			if (app->input->GetMouseButton(SDL_BUTTON_LEFT) == KeyState::KEY_DOWN ||
				app->input->GetMouseButton(SDL_BUTTON_LEFT) == KeyState::KEY_REPEAT)
			{
				buttonState = UIState::PRESSED;
			}

			if (app->input->GetMouseButton(SDL_BUTTON_LEFT) == KeyState::KEY_UP)
			{
				OnPressed();
			}
		}
		else
		{
			buttonState = UIState::ENABLED;
		}
	}

	

	return true;
}

void UIButtonComponent::Draw()
{
	PPlane* plane = nullptr;

	glColor3f(1.0f, 0.0f, 0.0f);

	plane->Draw();
	
}

void UIButtonComponent::OnEditor()
{
	ImGui::PushID(this);

	if (ImGui::CollapsingHeader("Button"))
	{
		ImGui::Checkbox("Active", &active);
		//ImGui::InputText("Text", &buttonText.GetText().c_str(), 20);
	}

	ImGui::PopID();
}

bool UIButtonComponent::OnPressed()
{
	buttonState = UIState::PRESSED;

	return true;
}