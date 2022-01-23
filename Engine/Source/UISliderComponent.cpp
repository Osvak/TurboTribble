#include "Application.h"
#include "SDL.h"
#include "UISliderComponent.h"
#include "ModuleCamera3D.h"
#include "CameraComponent.h"

UISliderComponent::UISliderComponent(int id, std::string _text)
{
	type = ComponentType::UI_SLIDER;
	value = 0;
	minValue = 50;
	maxValue = 100;
	text.setText(_text, 5, 5, 0.5, { 255,255,255 });
}

UISliderComponent::~UISliderComponent()
{

}

bool UISliderComponent::Update(float dt)
{
	return true;
}

void UISliderComponent::Draw()
{
	
}