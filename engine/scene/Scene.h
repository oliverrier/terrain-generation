#pragma once

#include <SFML/Graphics.hpp>

namespace engine {


    class IScene
    {

    public:
        IScene();
        virtual ~IScene();

        virtual const sf::Vector2i getMousePositionScreen();
        virtual const sf::Vector2i getMousePositionWindow();
        virtual const sf::Vector2f getMousePositionView();

        virtual void onBeginPlay();
        virtual void onEndPlay();

        virtual void processInput(sf::Event& inputEvent);
        virtual void update(const float& deltaTime);
        virtual void render();


        sf::RenderWindow& getWindow();



    protected:
        sf::RenderWindow& m_window;

    };


}