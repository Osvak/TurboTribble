#pragma once

#include "SDL.h"
#include "Component.h"
#include "Color.h"
#include "Text.h"

class UIInputBoxComponent : public Component
{
public:

	UIInputBoxComponent(int id, std::string text);
	virtual ~UIInputBoxComponent();

	bool Update(float dt) override;
	void Draw() override;
	void OnEditor() override;

public:

	Color disabledColor = white;
	Color pressedColor = red;
	Color focusedColor = blue;
	Color normalColor = green;
	Color selectedColor = black;
	Color textColor = white;

	Text text;
	char text[64] = "Enter name";
};