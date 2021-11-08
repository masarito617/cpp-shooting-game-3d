#pragma once
#include "Actor.h"
#include "../Commons/Shader.h"

// SkyBoxクラス
// 星のテクスチャを球体の裏側に貼って表現
class SkyBox : public Actor {
public:
    SkyBox(class Game* game, std::string fbxName, float rotSpeed);

    void UpdateActor(float deltaTime) override;
    void ProcessInput(const uint8_t* state, float deltaTime) override;

private:
    float mRotSpeed = 7.0f;

};
