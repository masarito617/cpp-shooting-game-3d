#pragma once
#include "Actor.h"
#include "../Commons/Shader.h"

class Ship : public Actor {
public:
    Ship(class Game* game);

    void UpdateActor(float deltaTime) override;
    void ProcessInput(const uint8_t* state, float deltaTime) override;

private:
    class BoxColliderComponent* mCollider;
    float mRotSpeed = 45.0f; // 回転速度
    float mRotTilt = 30.0f;  // 回転中の船の傾き

    // 回転中かどうかの判定で使用
    bool mIsRotLeft = false;
    bool mIsRotLeftBefore = false;
    bool mIsRotRight = false;
    bool mIsRotRightBefore = false;

    // ミサイルが撃てるかどうかの判定用
    bool mIsCanShot;      // ミサイルを撃てるかどうか？
    float mDeltaShotTime; // ミサイルを撃ってからの時間
    const float CanShotTime = 0.15f; // ミサイルを撃てるようになるまでの間隔

};
