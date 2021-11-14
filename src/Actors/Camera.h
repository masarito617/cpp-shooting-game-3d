#pragma once
#include "Actor.h"

// カメラアクタ
class Camera : public Actor {
public:
    Camera(class Game* game);

    void UpdateActor(float deltaTime) override;
    void ProcessInput(const uint8_t* state, float deltaTime) override;

private:
    class Actor* mTargetActor;

    // target設定時のOffset値
    float mOffsetPosForward = 15.0f;
    float mOffsetPosUp = 8.5f;
    float mOffsetTargetForward = 10.0f;

public:
    void SetTargetActor(Actor* actor) { mTargetActor = actor; }
    class Actor* GetTargetActor() const { return mTargetActor; }

};
