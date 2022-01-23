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
	void OnClick() override;
	float2 GetParentPosition();

public:
	Text aux;

	Color disabledColor = White;
	Color pressedColor = Red;
	Color focusedColor = Blue;
	Color normalColor = Green;
	Color selectedColor = Black;

	Color color = normalColor;
	Color textColor = White;
	Color prevColor = normalColor;

	char text[64] = "Introduce your name...";
	float fontScale = 1;
	bool drawRect;
	bool textEditable = false;
};