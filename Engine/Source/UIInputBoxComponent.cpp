#include "UIInputBoxComponent.h"
#include "SDL.h"
#include "Application.h"
#include "ModuleCamera3D.h"
#include "CameraComponent.h"

UIInputBoxComponent::UIInputBoxComponent(int id, std::string _text)
{
	type = ComponentType::UI_INPUTBOX;
	text.setText(_text, 5, 5, 0.5, { 255,255,255 });
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