#include "UIButtonComponent.h"

#include "Application.h"
#include "ModuleInput.h"
#include "Primitive.h"

#include "glew/include/GL/glew.h"

UIButtonComponent::UIButtonComponent(GameObject* own, std::string buttonText)
{
	type = ComponentType::UI_BUTTON;
	owner = own;
}

UIButtonComponent::~UIButtonComponent()
{

}

bool UIButtonComponent::Update(float dt)
{
	if (app->input->GetMouseButton(SDL_BUTTON_LEFT) == KeyState::KEY_DOWN)
	{
		OnPressed();
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
		ImGui::InputText("Text", &buttonText[0], 20);
	}

	ImGui::PopID();
}

bool UIButtonComponent::OnPressed()
{


	return true;
}