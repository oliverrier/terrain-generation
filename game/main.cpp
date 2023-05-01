#include <SFML/Graphics.hpp>
#include <functional>
#include <string>
#include <iostream>

#include "engine/ImGUI/ImGUIManager.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    bool buttonValue = false;

    // [](const MyObjType* o) -> float { return o->opacity; },
    // [](const MyObjType* o, float f) { o->opacity=f; })

    MyImGUI::ImguiButtonOnOff button("Button", buttonValue, [](bool b) { return b; });

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return EXIT_SUCCESS;
}