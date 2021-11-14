#pragma once
#include "Scene.h"

class ReadyScene : public Scene {
public:
    ReadyScene(class Game* game);
    ~ReadyScene();
    void Start() override;
    void Update(float deltaTime) override;
    void ProcessInput(const Uint8* state, float deltaTime) override;
    std::string const GetSceneName() override;

private:
    class Actor* mStartMsg;
    class Actor* mMenuMsg;
    class Actor* mTitleMsg;

};
