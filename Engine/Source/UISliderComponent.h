#pragma once

#include "Component.h"
#include "Color.h"
#include "Text.h"

class SDL_Rect;
class SDL_Color;
class SDL_Texture;

class UISliderComponent : public Component
{
public:

	UISliderComponent(int id, std::string text);
	virtual ~UISliderComponent();

	bool Update(float dt) override;
	void Draw() override;

	float value;
	float minValue;
	float maxValue;

public:

	Color disabledColor = white;
	Color pressedColor = red;
	Color focusedColor = blue;
	Color normalColor = green;
	Color selectedColor = black;
	Color textColor = white;

	Text sliderText;
	char text[64] = "FOV";
};