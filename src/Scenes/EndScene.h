#pragma once
#include "Scene.h"

class EndScene : public Scene {
public:
    EndScene(class Game* game);
    ~EndScene();
    void Start() override;
    void Update(float deltaTime) override;
    void ProcessInput(const Uint8* state, float deltaTime) override;
    std::string const GetSceneName() override;

private:
    class Actor* mEndMsg;

};
