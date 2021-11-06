#pragma once
#include "Actor.h"
#include "../Commons/Shader.h"

class Ship : public Actor {
public:
    Ship(class Game* game);

    void UpdateActor(float deltaTime) override;
    void ProcessInput(const uint8_t* state) override;

private:
    float mRotSpeed = 1.0f; // 回転速度
    float mTorTilt = 30.0f; // 回転中の船の傾き

    // 回転中かどうかの判定で使用
    bool mIsRotLeft = false;
    bool mIsRotLeftBefore = false;
    bool mIsRotRight = false;
    bool mIsRotRightBefore = false;

};
