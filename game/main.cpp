#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(640, 480), "ImGui + SFML = <3");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    sf::CircleShape shape2(100.f);
    shape2.setFillColor(sf::Color::Red);

    sf::Clock deltaClock;
    bool button1 = false;
    bool button2 = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::ShowDemoWindow();

        ImGui::Begin("Hello, world!");
        // change font size
        ImGui::SetWindowFontScale(2.0);
        // on click, change the shape
        if(ImGui::Button("button1"))
            button1 = !button1;
        ImGui::End();
        ImGui::Begin("Hello, world! 2");
        // change font size
        ImGui::SetWindowFontScale(2.0);
        ImGui::Button("Look at this pretty button");
        ImGui::End();

        // debug window
        ImGui::Begin("Debug");
        // change font size
        ImGui::SetWindowFontScale(2.0);
        ImGui::Text("button1: %d", button1);
        ImGui::Text("button2: %d", button2);
        ImGui::End();

        window.clear();
        if (button1)
            window.draw(shape2);
        else
            window.draw(shape);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
}
