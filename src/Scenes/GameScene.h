#pragma once
#include "Scene.h"

class GameScene : public Scene {
public:
    GameScene(class Game* game);
    ~GameScene();
    void Start() override;
    void Update(float deltaTime) override;
    void ProcessInput(const Uint8* state, float deltaTime) override;
    std::string const GetSceneName() override;

};
