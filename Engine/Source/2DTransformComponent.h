#pragma once

#include "Globals.h"
#include "Module.h"
#include "glmath.h"
#include <vector>

#include "assimp/cimport.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postProcess.h"
#include "GameObject.h"

class Component;

class Transform2DComponent : public Component
{
public:

	Transform2DComponent(GameObject* theObject, float3 pos, float3 sca, float3 rot);
	Transform2DComponent(float3 pos, float3 sca, float3 rot);
	~Transform2DComponent();


	void Enable() override;
	void Update(bool releaseMouse);
	void Disable() override;
	void OnEditor() override;
	bool OnLoad(JsonParsing& node) override;
	bool OnSave(JsonParsing& node, JSON_Array* array) override;


	Quat FromEulerToQuat(float3 eulerAngles);
	float3 FromQuatToEuler(Quat quatAngles);
	std::vector<float3> verticesAux;
	float4x4 transMatrix;

	void SetAABB(ComponentType type, GameObject* go, bool firstTime);
	void SetLast();

	float buttonWidth;
	float buttonHeight;

	float3 rotationEuler;
};