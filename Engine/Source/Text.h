#pragma once

#include "MathGeoLib/src/MathGeoLib.h"

#include <string>

class Text
{
public :
	void SetText(std::string text, float2 pos, float size, float4 color)
	{
		this->text = text;
		this->pos = pos;
		this->size = size;
		this->color = color;
	}

	void ChangeText(std::string text)
	{
		this->text = text;
	}
		
	void ChangePos(float2 pos)
	{
		this->pos = pos;
	}
		
	void ChangeSize(float size)
	{
		this->size = size;
	}
			
	void ChangeColor(float4 color)
	{
		this->color = color;
	}

private:
	std::string text;
	float2 pos = { .0f,.0f };
	float size = .0f;
	float4 color = { 1.0f,1.0f,1.0f,1.0f };
};