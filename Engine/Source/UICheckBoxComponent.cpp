#include "UICheckboxComponent.h"

#include "Application.h"
#include "SDL.h"

UICheckBoxComponent::UICheckBoxComponent(int id, std::string text)
{
	type = ComponentType::UI_CHECKBOX;
	checked = false;
	checkboxText.SetText(text, float2(5, 5), 0.5f, float4(255, 255, 255, 255));
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