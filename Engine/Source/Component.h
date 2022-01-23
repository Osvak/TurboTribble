#pragma once

#include "Imgui/imgui.h"
#include "JsonParsing.h"

class GameObject;

enum class ComponentType
{
	NONE = -1,
	TRANSFORM,
	MESH_RENDERER,
	MATERIAL,
	CAMERA,
	UI_2DTRANSFORM,
	UI_BUTTON,
	UI_CHECKBOX,
	UI_IMAGE,
	UI_INPUTBOX,
	UI_SLIDER,
};

class Component
{
public:
	Component() : active(true), type(ComponentType::NONE), owner(nullptr), collapsed(false) {}
	virtual ~Component() {}

	virtual void Enable() {}
	virtual bool Update(float dt) { return true; }
	virtual void Disable() {}
	virtual void Draw() {}
	virtual void DrawOutline() {}

	virtual void OnEditor() {}

	inline void SetOwner(GameObject* own) { owner = own; }

	void Checkbox(Component* component, const char* name, bool& act)
	{
		ImGui::PushID((void*)component);

		ImGui::Checkbox(name, &act);

		ImGui::PopID();
	}

	inline const ComponentType& GetType() const { return type; }
	inline const bool& GetActive() const { return active; }

	virtual bool OnLoad(JsonParsing& node) { return true; }
	virtual bool OnSave(JsonParsing& node, JSON_Array* array) { return true; }

public:

	ComponentType type;
	bool active;
	GameObject* owner;

	float3 lastPosition;
	float3 lastRotation;
	float3 lastScale;
	float3 position;
	float3 rotation;
	float3 scale;

	bool collapsed;
};