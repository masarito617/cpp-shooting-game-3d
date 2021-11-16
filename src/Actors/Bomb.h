#pragma once
#include "Actor.h"
#include "../Commons/Shader.h"

class Bomb : public Actor {
public:
    Bomb(class Game* game);

    void UpdateActor(float deltaTime) override;
    void ProcessInput(const uint8_t* state, float deltaTime) override;

private:
    float mTimeCount = 0.0f;         // 経過時間
    float mMaxScale = 2.0f;          // 最大サイズ
    const float mDisplayTime = 1.0f; // 表示時間

public:
    void SetMaxScale(float scale) { mMaxScale = scale; }

};
