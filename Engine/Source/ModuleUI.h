#pragma once

#include "Module.h"

#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


struct IVec2 {
    IVec2() = default;
    IVec2(int x, int y) : x(x), y(y) {}

    int x = 0, y = 0;
};

// FreeType Character Info
struct Character {
    unsigned int textureID;
    IVec2  size;
    IVec2  bearing;
    unsigned int advance;
};

class Shader
{
public:
    unsigned int id;

    Shader();
    void Use();
    void Stop();

private:
    // Utility function for checking shader compilation/linking errors.
    void CheckCompileErrors(GLuint shader, std::string type);

};

class ModuleUI : public Module
{
public:

    ModuleUI(Application* app, bool startEnabled = true);
    ~ModuleUI();

    bool Start()override;
    bool PreUpdate(float dt)override;
    bool Update(float dt)override;
    bool PostUpdate()override;

    bool CleanUp();
    void RenderText(std::string text, float x, float y, float scale, float3 color);
    void DeleteUIGameObjects();

public:

    std::map<char, Character> charMap;
    Shader* shader { nullptr };
    uint vao = 0, vbo = 0;

    std::vector<GameObject*> UIGameObjects;
    std::vector<GameObject*> hitObjs;
    GameObject* UIGameObjectSelected;
    GameObject* UIGameObjectFocused;
    uint nextUIGameObject = 1;

    std::string defaultText = "Default";
    float3 color = { 255,255,255 };

    float2 mousePos;
};