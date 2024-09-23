#include "pch.h"
#include "GameObject.h"

GameObject::GameObject(std::string name)
    : _name(name)
{
}

GameObject::~GameObject()
{
}

void GameObject::RenderUpdate()
{
    if (_bUseDebugPanel)
    {
        ImGui::Begin(_name.c_str());

        ImGui::SliderFloat("position X", &_position.x, -1.0f, 1.0f);
        ImGui::SliderFloat("position Y", &_position.y, -1.0f, 1.0f);
        ImGui::SliderFloat("position Z", &_position.z, -1.0f, 1.0f);

        ImGui::End();
    }
}
