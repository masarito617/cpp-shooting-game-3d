#pragma once
#include "Actor.h"
#include "../Commons/Shader.h"

class Bomb : public Actor {
public:
    Bomb(class Game* game);

    void UpdateActor(float deltaTime) override;
    void ProcessInput(const uint8_t* state, float deltaTime) override;

private:
    float mTimeCount = 0.0f;        // 経過時間
    const float DisplayTime = 1.0f; // 表示時間
    const float MaxScale = 2.0f;    // 最大サイズ

};
