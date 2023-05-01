#include <SFML/Graphics.hpp>
#include <functional>
#include <string>
#include <iostream>
#include <imgui.h>
#include <imgui-SFML.h>

#include "engine/ImGUI/ImGUIManager.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "ImGui + SFML = <3");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    bool buttonValue = false;
    MyImGUI::Callback callback = [&buttonValue]() {
        buttonValue = !buttonValue;
        std::cout << "Button pressed lolilol" << std::endl;
    };
    std::string buttonText = "My Button";
    // uniq ptr of input
    std::unique_ptr<MyImGUI::ImguiButton> button = std::make_unique<MyImGUI::ImguiButton>(buttonText, callback);
    MyImGUI::ImguiWindow window1("My Window");
    window1.addInput(std::move(button));



    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        window1.update();

        window.clear();
        window.draw(shape);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
}
