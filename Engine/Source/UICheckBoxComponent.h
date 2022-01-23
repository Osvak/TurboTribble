#pragma once

#include "Component.h"
#include "Text.h"
#include "Color.h"

class UICheckBoxComponent : public Component
{
public:

	UICheckBoxComponent(int id, std::string text);
	virtual ~UICheckBoxComponent();

	bool Update(float dt) override;
	void Draw() override;
	void OnEditor() override;

public:

	Color textColor = white;
	Color disabledColor = white;
	Color pressedColor = red;
	Color focusedColor = blue;
	Color normalColor = green;
	Color selectedColor = black;

	bool checked;

	Text checkboxText;
	char text[64] = "V-Sync";
};