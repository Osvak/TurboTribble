#pragma once

#include "Module.h"

class ModuleUI : public Module
{
public:
	ModuleUI();
	~ModuleUI();

	bool Start() override;
	bool PreUpdate(float dt) override;
	bool Update(float dt) override;
	bool PostUpdate() override;

	bool CleanUp() override;
};
