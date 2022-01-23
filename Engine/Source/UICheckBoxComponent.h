#pragma once

#include "Component.h"
#include "Color.h"
#include "Text.h"

class UICheckBoxComponent : public Component
{
public:

	UICheckBoxComponent(int id, std::string text);
	virtual ~UICheckBoxComponent();

	bool Update(float dt) override;
	void Draw() override;
	void OnEditor() override;
	void OnClick() override;
	float2 GetParentPosition();

public:
	Color disabledColor = White;
	Color pressedColor = Red;
	Color focusedColor = Blue;
	Color normalColor = Green;
	Color selectedColor = Black;

	bool checked;

	Text checkboxText;
	Color textColor = White;
	char text[64] = "V-Sync";
	float fontScale = 0.5;
	bool firstTime;
};