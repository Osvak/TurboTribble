#pragma once

#include "Component.h"
#include "Color.h"

class UIImageComponent : public Component
{
public:

	UIImageComponent(int id, std::string text);
	~UIImageComponent();

	bool Update(float dt) override;
	void Draw() override;
	void OnEditor() override;

private:

	Color color = blue;
	std::string text;
};