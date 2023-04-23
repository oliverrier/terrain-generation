#pragma once

#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics.hpp>

#include <string>


// with singleton pattern
class ImGuiManager
{
public:
    static ImGuiManager& getInstance()
    {
        static ImGuiManager instance;
        return instance;
    }

    ImGuiManager(ImGuiManager const&) = delete;
    void operator=(ImGuiManager const&) = delete;

    void init(sf::RenderWindow& window);
    void update();
    void render();

    // new text
    void addText(std::string name, const char* text);


private:
    ImGuiManager() = default;
    ~ImGuiManager() = default;

    std::vector<std::pair<std::string, const char*>> textList;



};

void ImGuiManager::init(sf::RenderWindow& window)
{
    ImGui::SFML::Init(window);
}

void ImGuiManager::update()
{
    ImGui::SFML::Update();
}

void ImGuiManager::render()
{
    ImGui::SFML::Render();
}

void ImGuiManager::addText(const char* text)
{
    ImGui::Text(text);
}

