#include "Scene.h"

#include "../Game/Game.h"

namespace engine {

	IScene::IScene() : m_window(*GameInstance::GetInstance()->getWindow())
	{
	}

	IScene::~IScene()
	{
	}


	const sf::Vector2i IScene::getMousePositionScreen()
	{
		return sf::Mouse::getPosition();
	}

	const sf::Vector2i IScene::getMousePositionWindow()
	{
		return sf::Mouse::getPosition(m_window);
	}

	const sf::Vector2f IScene::getMousePositionView()
	{
		return m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
	}



	void IScene::onBeginPlay() {
	}


	void IScene::onEndPlay() {
	}


	void IScene::processInput(sf::Event& inputEvent)
	{
	}

	void IScene::update(const float& deltaTime)
	{
	}

	void IScene::render()
	{
	}

	sf::RenderWindow& IScene::getWindow()
	{
		return m_window;
	}
}