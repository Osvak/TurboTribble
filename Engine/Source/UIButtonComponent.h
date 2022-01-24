#pragma once

#include "Component.h"
#include "Text.h"
#include "Color.h"
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

	Text buttonText;
	std::string text = "Button";

	Color textColor = white;
	Color disabledColor = white;
	Color pressedColor = red;
	Color focusedColor = blue;
	Color normalColor = green;
	Color selectedColor = black;

	bool active = true;
	UIState buttonState = UIState::ENABLED;
};