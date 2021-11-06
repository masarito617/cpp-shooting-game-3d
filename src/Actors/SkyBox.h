#pragma once
#include "Actor.h"
#include "../Commons/Shader.h"

// SkyBoxクラス
// 星のテクスチャを球体の裏側に貼って表現
class SkyBox : public Actor {
public:
    SkyBox(class Game* game);

    void UpdateActor(float deltaTime) override;
    void ProcessInput(const uint8_t* state) override;

private:
    Actor* bgFront;
    Actor* bgBack;
    float frontRotSpeed = 7.0f;
    float backRotSpeed = 5.0f;

};
