#pragma once

#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics.hpp>

#include <string>

using Callback = std::function<void()>;

class ImGuiWidget
{
public:
    ImGuiWidget(std::string name, std::string text)
    {
        this->name = name;
        this->text = text;
    }

    virtual void render() = 0;
    std::string name;
    std::string text;
    Callback callback;

};

class ImGuiButton : public ImGuiWidget
{
public:
    ImGuiButton(std::string name, std::string text, Callback callback) : ImGuiWidget(name, text)
    {
        this->callback = callback;
    }

    void render() override
    {
        if (ImGui::Button(text.c_str()))
        {
            callback();
        }
    }

};

class ImGuiWindow
{
public:
    ImGuiWindow(std::string name)
    {
        this->name = name;
    }

    void render()
    {
        ImGui::Begin(name.c_str());

        for (auto& widget : widgets)
        {
            widget->render();
        }

        ImGui::End();
    }

    void addWidget(ImGuiWidget* widget)
    {
        widgets.push_back(widget);
    }

    std::string name;
    std::vector<ImGuiWidget*> widgets;

};

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

    std::vector<ImGuiWindow*> windows;


};

void ImGuiManager::init(sf::RenderWindow& window)
{
    ImGui::SFML::Init(window);
}

void ImGuiManager::update()
{

}

void ImGuiManager::render()
{
    for (auto& window : windows)
    {
        window->render();
    }
}

// void ImGuiManager::addText(const char* text)
// {
//     ImGui::Text(text);
// }

// TODO : Not tested
