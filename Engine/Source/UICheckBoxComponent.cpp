#include "Application.h"
#include "SDL.h"
#include "UICheckboxComponent.h"

UICheckBoxComponent::UICheckBoxComponent(int id, std::string _text)
{
	type = ComponentType::UI_CHECKBOX;
	checked = false;
	checkboxText.setText(_text, 5, 5, 0.5, { 255,255,255 });
}

UICheckBoxComponent::~UICheckBoxComponent()
{

}

bool UICheckBoxComponent::Update(float dt)
{
	
}

void UICheckBoxComponent::Draw()
{
	
}

void UICheckBoxComponent::OnEditor()
{
	
}