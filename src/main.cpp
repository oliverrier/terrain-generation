#include <memory>

#include <engine/game/Game.h>
#include <engine/graphics/camera/Camera.h>

#include "scenes/SceneEnum.h"
#include "scenes/MainScene.h"

int main()
{
    const sf::ContextSettings settings(24, 8, 4, 4, 6);

    engine::Game* game = engine::GameInstance::GetInstance();
    game->addScenes(new MainScene());
    game->setCurrentScene(0);
    game->run(sf::VideoMode(1280, 720), "ProceduralGeneration", sf::Style::Default, ScenesEnum::MAIN_SCENE);
    return 0;
}