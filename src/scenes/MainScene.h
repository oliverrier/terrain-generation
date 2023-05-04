#pragma once
#include <engine/Scene/Scene.h>
#include <engine/graphics/camera/Camera.h>

#include <engine/graphics/shapes/Map.h>

using Mapf = Map<float>;

class MainScene : public engine::IScene
{
public:
    

    MainScene();
    ~MainScene();

    void onBeginPlay() override;

    void processInput(sf::Event& inputEvent) override;
    void update(const float& deltaTime) override;
    void render() override;

    Camera _mainCamera;
    std::unique_ptr<Mapf> _map;
private:
};