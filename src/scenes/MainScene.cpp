
#include "GL/glew.h"
#include "SFML/OpenGL.hpp"

#include "MainScene.h"

using Mapf = Map<float>;

MainScene::MainScene()
{
}

MainScene::~MainScene()
{
}

void MainScene::onBeginPlay()
{
	sf::Mouse::setPosition(sf::Vector2i(400, 300), m_window);

	_map = std::make_unique<Mapf>();
}

void MainScene::processInput(sf::Event& inputEvent)
{


    if (inputEvent.key.code == sf::Keyboard::Escape) {
        m_window.close();
    }
    else if (inputEvent.type == sf::Event::MouseMoved) {
        float dx = 400.f - float(inputEvent.mouseMove.x);
        float dy = 300.f - float(inputEvent.mouseMove.y);
        sf::Mouse::setPosition(sf::Vector2i(400, 300), m_window);
        _mainCamera._cameraYaw += 0.001f * dx;
        _mainCamera._cameraPitch -= 0.001f * dy;
    }

    printf("Camera position: %f, %f\n", _mainCamera._cameraYaw, _mainCamera._cameraPitch);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
    {
        _mainCamera._cameraPos.x -= sin(_mainCamera._cameraYaw) * _mainCamera._cameraSpeed;
        _mainCamera._cameraPos.z -= cos(_mainCamera._cameraYaw) * _mainCamera._cameraSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {
        _mainCamera._cameraPos.x -= cos(_mainCamera._cameraYaw) * _mainCamera._cameraSpeed;
        _mainCamera._cameraPos.z += sin(_mainCamera._cameraYaw) * _mainCamera._cameraSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        _mainCamera._cameraPos.x += sin(_mainCamera._cameraYaw) * _mainCamera._cameraSpeed;
        _mainCamera._cameraPos.z += cos(_mainCamera._cameraYaw) * _mainCamera._cameraSpeed;

    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        _mainCamera._cameraPos.x += cos(_mainCamera._cameraYaw) * _mainCamera._cameraSpeed;
        _mainCamera._cameraPos.z -= sin(_mainCamera._cameraYaw) * _mainCamera._cameraSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
    {
        _mainCamera._cameraPos.y += _mainCamera._cameraSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        _mainCamera._cameraPos.y -= _mainCamera._cameraSpeed;
    }


    IScene::processInput(inputEvent);
}

void MainScene::update(const float& deltaTime)
{
    _mainCamera.ViewMatrix = Mat4f::rotationX(-_mainCamera._cameraPitch) * Mat4f::rotationY(-_mainCamera._cameraYaw) * Mat4f::translation(-_mainCamera._cameraPos.x, -_mainCamera._cameraPos.y, -_mainCamera._cameraPos.z);

    _map->update();
}

void MainScene::render()
{
    _map->render(_mainCamera.ViewMatrix, _mainCamera.ProjectionMatrix);
    glFlush();
}

