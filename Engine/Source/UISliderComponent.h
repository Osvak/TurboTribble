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
	void OnEditor() override;
	float2 GetParentPosition();

	float value;
	float minValue;
	float maxValue;
	MyPlane* thePlane;
	bool completed;
	float barProgres;
public:
	Color disabledColor = White;
	Color pressedColor = Red;
	Color focusedColor = Blue;
	Color normalColor = Green;
	Color selectedColor = Black;

	bool drawRect;

	Text sliderText;
	Color textColor = White;
	char text[64] = "Camera FOV";
	float fontScale = 0.5;
};