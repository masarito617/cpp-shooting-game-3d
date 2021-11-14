#pragma once
#include "Actor.h"

// カメラアクタ
class Camera : public Actor {
public:
    Camera(class Game* game);

    void UpdateActor(float deltaTime) override;
    void ProcessInput(const uint8_t* state, float deltaTime) override;

    void AnimStart(); // 登場アニメーション開始

private:
    class Actor* mTargetActor;

    // target設定時のOffset値
    const float mOffsetPosForward = 15.0f;
    const float mOffsetPosUp = 8.5f;
    const float mOffsetLookForward = 10.0f;

    float mDeltaAnimTime = 0.0f;
    const float mAnimTime = 3.0f;
    const float mAnimOffsetInitDistance = 10.0f;
    const float mAnimOffsetLookForward = 3.0f;
    const Vector3 mAnimLookVec = Vector3(-1.0f, -1.0f, 1.0f);
    bool mIsAnimFinish =false;

public:
    void SetTargetActor(Actor* actor) { mTargetActor = actor; }
    class Actor* GetTargetActor() const { return mTargetActor; }
    const bool GetIsAnimFinish() const { return mIsAnimFinish; }

};
