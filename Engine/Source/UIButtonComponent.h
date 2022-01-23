#pragma once

#include "Component.h"
#include <string>

class SDL_Rect;

class UIButtonComponent : public Component
{
public:
	UIButtonComponent(GameObject* own, std::string buttonText);
	~UIButtonComponent();

	bool Update(float dt);
	void Draw();
	void OnEditor();
	bool OnPressed();

private:
	std::string buttonText = "Button";

	bool active = true;


};