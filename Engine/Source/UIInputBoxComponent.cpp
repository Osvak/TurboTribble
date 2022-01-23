#include "UIInputBoxComponent.h"
#include "SDL.h"
#include "Application.h"
#include "ModuleCamera3D.h"
#include "CameraComponent.h"

UIInputBoxComponent::UIInputBoxComponent(int id, std::string text)
{
	type = ComponentType::UI_INPUTBOX;
	inputBoxText.SetText(text, float2(5, 5), 0.5f, float4(255, 255, 255, 255));
}

UIInputBoxComponent::~UIInputBoxComponent()
{

}

bool UIInputBoxComponent::Update(float dt)
{
	return true;
}

void UIInputBoxComponent::Draw()
{
	
}