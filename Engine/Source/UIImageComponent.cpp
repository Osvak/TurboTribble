#include "Application.h"
#include "SDL.h"
#include "UIImageComponent.h"

UIImageComponent::UIImageComponent(int id, std::string text)
{
	name = "Image Component";
	type = ComponentType::UI_IMAGE;
	this->text = "Image Component";
	state = State::NORMAL;
	color = White;
	UIid = id;
}

UIImageComponent::~UIImageComponent()
{
	text.clear();
}

bool UIImageComponent::Update(float dt)
{
	return true;
}

void UIImageComponent::Draw()
{
	MyPlane* planeToDraw = nullptr;
	int auxId = owner->id;

	for (int i = 0; i < App->editor->planes.size(); i++)
		if (App->editor->planes[i]->id == auxId) planeToDraw = App->editor->planes[i];

	glAlphaFunc(GL_GREATER, 0.5);
	glEnable(GL_ALPHA_TEST);

	glColor4f(color.r, color.g, color.b, color.a);

	planeToDraw->DrawPlane2D();

	glDisable(GL_ALPHA_TEST);
	glColor3f(255, 255, 255);
}

void UIImageComponent::OnEditor()
{
	// Manage if colors are being edited or not
	static bool normalEditable = false;

	ImGui::Checkbox("Active", &active);

	ImGui::Text("Image Color"); ImGui::SameLine();
	if (ImGui::ColorButton("Image Color", ImVec4(color.r, color.g, color.b, color.a)))
		normalEditable = !normalEditable;

	if (normalEditable)
	{
		ImGui::ColorPicker3("Image Color", &color);
	}
}