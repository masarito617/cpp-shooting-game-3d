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

    // 登場アニメーション関連
    float mTotalAnimTime = 0.0f;  // アニメーション合計時間
    const float mAnimTime = 3.5f; // アニメーション時間
    const float mAnimOffsetInitDistance = 10.0f; // 初期状態の距離
    const float mAnimOffsetLookForward = 4.5f;   // 注視点オフセット
    const Vector3 mAnimLookVec = Vector3(-0.8f, -1.2f, 0.85f); // 移動方向
    bool mIsAnimFinish =false; // 完了したかどうか？

public:
    void SetTargetActor(Actor* actor) { mTargetActor = actor; }
    class Actor* GetTargetActor() const { return mTargetActor; }
    const bool GetIsAnimFinish() const { return mIsAnimFinish; }

};
