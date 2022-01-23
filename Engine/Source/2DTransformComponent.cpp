#include "application.h"
#include "2DTransformComponent.h"
#include <math.h>
#include"CameraComponent.h"
#include "ModuleScene.h"

#include "Imgui/imgui.h"
#include "Imgui/imgui_impl_sdl.h"
#include "Imgui/imgui_impl_opengl3.h"

#include "JsonParsing.h"

Transform2DComponent::Transform2DComponent(GameObject* theObject, float3 pos, float3 sca, float3 rot)
{
	lastPosition = { 0,0,0 };
	lastRotation = { 0,0,0 };
	type = ComponentType::UI_2DTRANSFORM;

	position = pos;
	scale = sca;
	rotationEuler = rot;
	generalScale = 1.0f;

	buttonWidth = scale.x;
	buttonHeight = scale.y;

	rotationQuat = FromEulerToQuat(rotationEuler);

	float4x4 aux;
	transMatrix = aux.FromTRS(position, rotationQuat, scale);
	transmat = transMatrix;
	transMatrix = transMatrix.Transposed();

	name = "Transform2D Component";
}

Transform2DComponent::Transform2DComponent(float3 pos, float3 sca, float3 rot)
{
	lastPosition = { 0,0,0 };
	lastRotation = { 0,0,0 };
	type = ComponentType::UI_2DTRANSFORM;

	position = pos;
	scale = sca;
	rotationEuler = rot;
	generalScale = 1.0f;

	buttonWidth = scale.x;
	buttonHeight = scale.y;

	rotationQuat = FromEulerToQuat(rotationEuler);

	float4x4 aux;
	transMatrix = aux.FromTRS(position, rotationQuat, scale);
	transmat = transMatrix;
	transMatrix = transMatrix.Transposed();

	name = "Transform2D Component";
}

ComponentType Transform2DComponent::getComponentType()
{
	for (int b = 0; b < app->scene->gameObjects[app->scene->gameObjects.size() - 1]->components.size(); b++)
	{
		if (app->scene->gameObjects[app->scene->gameObjects.size() - 1]->components[b]->type == ComponentType::UI_BUTTON)
		{
			return ComponentType::UI_BUTTON;
		}
		else if (app->scene->gameObjects[app->scene->gameObjects.size() - 1]->components[b]->type == ComponentType::UI_CHECKBOX)
		{
			return ComponentType::UI_CHECKBOX;
		}
		else if (app->scene->gameObjects[app->scene->gameObjects.size() - 1]->components[b]->type == ComponentType::UI_INPUTBOX)
		{
			return ComponentType::UI_INPUTBOX;
		}
		else if (app->scene->gameObjects[app->scene->gameObjects.size() - 1]->components[b]->type == ComponentType::UI_SLIDER)
		{
			return ComponentType::UI_SLIDER;
		}

	}
}
Transform2DComponent::~Transform2DComponent()
{
}

void Transform2DComponent::Enable()
{
}

void Transform2DComponent::Update(bool releaseMouse)
{
	rotationQuat = FromEulerToQuat(rotationEuler);

	float4x4 aux;
	transMatrix = aux.FromTRS(position, rotationQuat, scale);
	transmat = transMatrix;
	transMatrix = transMatrix.Transposed();
	app->editor->objectSelected->matrix = transMatrix.ptr();

	float4x4 aux1;
	for (int a = 0; a < owner->childrens.size(); a++) {
		for (int b = 0; b < owner->childrens[a]->components.size(); b++) {
			if ((owner->childrens[a]->components[b]->type == ComponentType::TRANSFORM2D))
			{
				owner->childrens[a]->components[b]->position += (position - lastPosition);

				owner->childrens[a]->components[b]->transmat = aux1.FromTRS(owner->childrens[a]->components[b]->position, owner->childrens[a]->components[b]->rotationQuat, owner->childrens[a]->components[b]->scale);
				owner->childrens[a]->components[b]->transmat = owner->childrens[a]->components[b]->transmat.Transposed();
				owner->childrens[a]->matrix = owner->childrens[a]->components[b]->transmat.ptr();


			}
		}
	}
	lastScale = scale;
	lastPosition = position;
	lastRotation = rotationEuler;
	lastGeneralScale = generalScale;
}
void Transform2DComponent::setLast()
{
	lastScale = scale;
	lastPosition = position;
	lastRotation = rotationEuler;
	lastGeneralScale = generalScale;
}
void Transform2DComponent::Disable()
{
}

void Transform2DComponent::OnEditor(int i)
{
	lastScale = scale;
	lastPosition = position;
	lastRotation = rotationEuler;
	lastGeneralScale = generalScale;

	ImGui::TextColored(ImVec4(0, 0, 255, 255), "Size");
	if (ImGui::DragFloat("Width", &buttonWidth, 0.5f, 0, 1000000))
	{
		bool release = false;
		if (app->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_UP)
			release = true;
		scale.x = buttonWidth;
		scale.y = buttonHeight;
		Update(release);
	}
	if (ImGui::DragFloat("Height", &buttonHeight, 0.5f, 0, 1000000))
	{
		bool release = false;
		if (app->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_UP)
			release = true;
		scale.x = buttonWidth;
		scale.y = buttonHeight;
		Update(release);
	}

	ImGui::TextColored(ImVec4(0, 0, 255, 255), "Position");
	static bool wasNull = true;
	if (app->camera->GameCam != nullptr)
		wasNull = false;

	if (ImGui::DragFloat("Position X", &position.x, 0.5f))
	{
		bool release = false;
		if (app->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_UP)
			release = true;
		Update(release);
	}
	if (ImGui::DragFloat("Position Y", &position.y, 0.5f))
	{
		bool release = false;
		if (app->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_UP)
			release = true;
		Update(release);
	}
	if (ImGui::DragFloat("Position Z", &position.z, 0.5f))
	{
		bool release = false;
		if (app->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_UP)
			release = true;
		Update(release);
	}

	ImGui::TextColored(ImVec4(0, 0, 255, 255), "Rotation");
	
	if (ImGui::DragFloat("Rotation Z", &rotationEuler.z, 0.5f))
	{
		if (app->camera->GameCam == nullptr)
			wasNull = true;

		int camComponent = app->editor->objectSelected->SearchComponent(app->editor->objectSelected, ComponentType::CAMERA);
		if (camComponent != -1)
		{
			app->camera->GameCam = (ComponentCamera*)app->editor->objectSelected->components[camComponent];
			app->camera->GameCam->Rotate(rotationEuler.z - lastRotation.z, "Z");
			if (wasNull)
				app->camera->GameCam = nullptr;
		}
		bool release = false;
		if (app->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_UP)
			release = true;
		Update(release);
	}
}

void Transform2DComponent::Load(const char* path)
{
	//Reading JSON File
	JSON_Value* userData = json_parse_file(path);

	UID = json_object_get_number(json_object(userData), "UID");
	position.x = json_object_get_number(json_object(userData), "Position X");
	position.y = json_object_get_number(json_object(userData), "Position Y");
	position.z = json_object_get_number(json_object(userData), "Position Z");

	scale.x = json_object_get_number(json_object(userData), "Scale X");
	scale.y = json_object_get_number(json_object(userData), "Scale Y");
	scale.z = json_object_get_number(json_object(userData), "Scale Z");

	rotationEuler.x = json_object_get_number(json_object(userData), "Rotation X");
	rotationEuler.y = json_object_get_number(json_object(userData), "Rotation Y");
	rotationEuler.z = json_object_get_number(json_object(userData), "Rotation Z");

	app->editor->AddLog("Loaded Transform 2D Component Data\n");

	Update(false);
}

void Transform2DComponent::Save(const char* path)
{
	//Creating Json file
	JSON_Value* user_data = json_value_init_object();

	json_object_set_number(json_object(user_data), "UID", UID);
	json_object_set_number(json_object(user_data), "Position X", position.x);
	json_object_set_number(json_object(user_data), "Position Y", position.y);
	json_object_set_number(json_object(user_data), "Position Z", position.z);
	json_object_set_number(json_object(user_data), "Scale X", scale.x);
	json_object_set_number(json_object(user_data), "Scale Y", scale.y);
	json_object_set_number(json_object(user_data), "Scale Z", scale.z);
	json_object_set_number(json_object(user_data), "Rotation X", rotationEuler.x);
	json_object_set_number(json_object(user_data), "Rotation Y", rotationEuler.y);
	json_object_set_number(json_object(user_data), "Rotation Z", rotationEuler.z);


	json_serialize_to_file_pretty(user_data, path);

	app->editor->AddLog("Saved Transform 2D Component Data\n");
}
void Transform2DComponent::setOwner()
{
	owner->matrix = transMatrix.ptr();
}

void Transform2DComponent::CreateAABB(ComponentType type, GameObject* go, bool firstTime)
{
	GameObject* auxiliar = go;
	Model* model = nullptr;
	MyCube* cube = nullptr;
	MyPyramid* pyramid = nullptr;
	MyCylinder* cylinder = nullptr;
	MySphere* sphere = nullptr;
	MyPlane* plane = nullptr;

	switch (type)
	{
	case ComponentType::MESH:
		for (int i = 0; i < app->renderer3D->models.size(); i++)
		{
			if (go->id == app->renderer3D->models[i].id)
			{
				model = &app->renderer3D->models[i];
				break;
			}
		}
		break;
	case ComponentType::CUBE:
		for (int i = 0; i < app->editor->cubes.size(); i++)
		{
			if (go->id == app->editor->cubes[i]->id)
			{
				cube = app->editor->cubes[i];
				break;
			}
		}
		break;
	case ComponentType::PYRAMID:
		for (int i = 0; i < app->editor->pyramids.size(); i++)
		{
			if (go->id == app->editor->pyramids[i]->id)
			{
				pyramid = app->editor->pyramids[i];
				break;
			}
		}
		break;
	case ComponentType::SPHERE:
		for (int i = 0; i < app->editor->spheres.size(); i++)
		{
			if (go->id == app->editor->spheres[i]->id)
			{
				sphere = app->editor->spheres[i];
				break;
			}
		}
		break;
	case ComponentType::CYLINDER:
		for (int i = 0; i < app->editor->cylinders.size(); i++)
		{
			if (go->id == app->editor->cylinders[i]->id)
			{
				cylinder = app->editor->cylinders[i];
				break;
			}
		}
		break;
	case ComponentType::PLANE:
		for (int i = 0; i < app->editor->planes.size(); i++)
		{
			if (go->id == app->editor->planes[i]->id)
			{
				plane = app->editor->planes[i];
				break;
			}
		}
		break;
	default:
		break;
	}

	float4x4 aux2;
	transMatrix = aux2.FromTRS(position, rotationQuat, scale);
	transMatrix = transMatrix.Transposed();

	AABB* aux;
	OBB* aux1;
	BoundingBoxes* auxiliarCube;

	std::vector<float4> aabbVertexAux;
	std::vector<float3> aabbVertex;
	float3 MAX;
	float3 MIN;
	switch (type)
	{
	case ComponentType::MESH:
		for (int b = 0; b < model->meshes.size(); b++)
		{
			aux = new AABB();
			aux1 = new OBB();
			aux->SetNegativeInfinity();
			for (int a = 0; a < model->meshes[b].vertices.size(); a++)
			{
				vertices_aux.push_back(model->meshes[b].vertices[a].position);
			}
			for (int i = 0; i < vertices_aux.size(); i++)
			{
				float4 vertex(vertices_aux[i].x, vertices_aux[i].y, vertices_aux[i].z, 1);
				vertex = vertex * transMatrix;
				aabbVertexAux.push_back(vertex);
			}
			for (int i = 0; i < aabbVertexAux.size(); i++)
			{
				float3 vertex(aabbVertexAux[i].x, aabbVertexAux[i].y, aabbVertexAux[i].z);
				aabbVertex.push_back(vertex);
			}
			aux->Enclose((float3*)aabbVertex.data(), (size_t)aabbVertex.size());
			(*aux1) = (*aux);
			aux1->Transform(transMatrix);
			aux->SetNegativeInfinity();
			aux->Enclose(*aux1);
			go->aabb.push_back(aux);
			go->obb.push_back(aux1);
			if (firstTime)
			{
				auxiliarCube = new BoundingBoxes({ 0,0,0 }, scale, aux->maxPoint, aux->minPoint);
				go->boundingBoxes.push_back(auxiliarCube);
			}
		}
		break;
	case ComponentType::CUBE:
		aux = new AABB();
		aux1 = new OBB();
		aux->SetNegativeInfinity();
		vertices_aux = cube->getVertex();
		for (int i = 0; i < vertices_aux.size(); i++)
		{
			float4 vertex(vertices_aux[i].x, vertices_aux[i].y, vertices_aux[i].z, 1);
			vertex = vertex * transMatrix;
			aabbVertexAux.push_back(vertex);
		}
		for (int i = 0; i < aabbVertexAux.size(); i++)
		{
			float3 vertex(aabbVertexAux[i].x, aabbVertexAux[i].y, aabbVertexAux[i].z);
			aabbVertex.push_back(vertex);
		}
		aux->Enclose((float3*)aabbVertex.data(), (size_t)aabbVertex.size());
		(*aux1) = (*aux);
		aux1->Transform(transMatrix);
		aux->SetNegativeInfinity();
		aux->Enclose(*aux1);
		go->aabb.push_back(aux);
		go->obb.push_back(aux1);
		if (firstTime)
		{
			auxiliarCube = new BoundingBoxes({ 0,0,0 }, scale, aux->maxPoint, aux->minPoint);
			go->boundingBoxes.push_back(auxiliarCube);
		}
		break;
	case ComponentType::PYRAMID:
		aux = new AABB();
		aux1 = new OBB();
		aux->SetNegativeInfinity();
		vertices_aux = pyramid->getVertex();
		for (int i = 0; i < vertices_aux.size(); i++)
		{
			float4 vertex(vertices_aux[i].x, vertices_aux[i].y, vertices_aux[i].z, 1);
			vertex = vertex * transMatrix;
			aabbVertexAux.push_back(vertex);
		}
		for (int i = 0; i < aabbVertexAux.size(); i++)
		{
			float3 vertex(aabbVertexAux[i].x, aabbVertexAux[i].y, aabbVertexAux[i].z);
			aabbVertex.push_back(vertex);
		}
		aux->Enclose((float3*)aabbVertex.data(), (size_t)aabbVertex.size());
		(*aux1) = (*aux);
		aux1->Transform(transMatrix);
		aux->SetNegativeInfinity();
		aux->Enclose(*aux1);
		go->aabb.push_back(aux);
		go->obb.push_back(aux1);
		if (firstTime)
		{
			auxiliarCube = new BoundingBoxes({ 0,0,0 }, scale, aux->maxPoint, aux->minPoint);
			go->boundingBoxes.push_back(auxiliarCube);
		}
		break;
	case ComponentType::SPHERE:
		aux = new AABB();
		aux1 = new OBB();
		aux->SetNegativeInfinity();
		vertices_aux = sphere->getVertex();
		for (int i = 0; i < vertices_aux.size(); i++)
		{
			float4 vertex(vertices_aux[i].x, vertices_aux[i].y, vertices_aux[i].z, 1);
			vertex = vertex * transMatrix;
			aabbVertexAux.push_back(vertex);
		}
		for (int i = 0; i < aabbVertexAux.size(); i++)
		{
			float3 vertex(aabbVertexAux[i].x, aabbVertexAux[i].y, aabbVertexAux[i].z);
			aabbVertex.push_back(vertex);
		}
		aux->Enclose((float3*)aabbVertex.data(), (size_t)aabbVertex.size());
		(*aux1) = (*aux);
		aux1->Transform(transMatrix);
		aux->SetNegativeInfinity();
		aux->Enclose(*aux1);
		go->aabb.push_back(aux);
		go->obb.push_back(aux1);
		if (firstTime)
		{
			auxiliarCube = new BoundingBoxes({ 0,0,0 }, scale, aux->maxPoint, aux->minPoint);
			go->boundingBoxes.push_back(auxiliarCube);
		}
		break;
	case ComponentType::CYLINDER:
		aux = new AABB();
		aux1 = new OBB();
		aux->SetNegativeInfinity();
		vertices_aux = cylinder->getVertex();
		for (int i = 0; i < vertices_aux.size(); i++)
		{
			float4 vertex(vertices_aux[i].x, vertices_aux[i].y, vertices_aux[i].z, 1);
			vertex = vertex * transMatrix;
			aabbVertexAux.push_back(vertex);
		}
		for (int i = 0; i < aabbVertexAux.size(); i++)
		{
			float3 vertex(aabbVertexAux[i].x, aabbVertexAux[i].y, aabbVertexAux[i].z);
			aabbVertex.push_back(vertex);
		}
		aux->Enclose((float3*)aabbVertex.data(), (size_t)aabbVertex.size());
		(*aux1) = (*aux);
		aux1->Transform(transMatrix);
		aux->SetNegativeInfinity();
		aux->Enclose(*aux1);
		go->aabb.push_back(aux);
		go->obb.push_back(aux1);
		if (firstTime)
		{

			auxiliarCube = new BoundingBoxes({ 0,0,0 }, scale, aux->maxPoint, aux->minPoint);
			go->boundingBoxes.push_back(auxiliarCube);
		}
		break;
	case ComponentType::PLANE:
		aux = new AABB();
		aux1 = new OBB();
		aux->SetNegativeInfinity();
		vertices_aux = plane->getVertex();
		for (int i = 0; i < vertices_aux.size(); i++)
		{
			float4 vertex(vertices_aux[i].x, vertices_aux[i].y, vertices_aux[i].z, 1);
			vertex = vertex * transMatrix;
			aabbVertexAux.push_back(vertex);
		}
		for (int i = 0; i < aabbVertexAux.size(); i++)
		{
			float3 vertex(aabbVertexAux[i].x, aabbVertexAux[i].y, aabbVertexAux[i].z);
			aabbVertex.push_back(vertex);
		}

		aux->Enclose((float3*)aabbVertex.data(), (size_t)aabbVertex.size());
		MAX = aux->maxPoint;
		MIN = aux->minPoint;
		(*aux1) = (*aux);
		aux1->Transform(transMatrix);
		aux->SetNegativeInfinity();
		aux->Enclose(*aux1);

		go->aabb.push_back(aux);
		go->obb.push_back(aux1);

		aux->maxPoint = MAX;
		aux->minPoint = MIN;
		if (firstTime)
		{
			auxiliarCube = new BoundingBoxes({ 0,0,0 }, scale, MAX, MIN);

			go->boundingBoxes.push_back(auxiliarCube);
		}
		break;
	default:
		break;
	}
}

Quat Transform2DComponent::FromEulerToQuat(float3 eulerAngles)
{
	eulerAngles.x = math::DegToRad(eulerAngles.x);
	eulerAngles.y = math::DegToRad(eulerAngles.y);
	eulerAngles.z = math::DegToRad(eulerAngles.z);

	Quat q = q.FromEulerXYZ(eulerAngles.x, eulerAngles.y, eulerAngles.z);

	return q;
}

float3 Transform2DComponent::FromQuatToEuler(Quat quatAngles)
{
	float3 angles;

	angles = quatAngles.ToEulerXYZ();

	angles.x = math::RadToDeg(angles.x);
	angles.y = math::RadToDeg(angles.y);
	angles.z = math::RadToDeg(angles.z);
	float3 toReturn(angles.x, angles.y, angles.z);

	return toReturn;
}