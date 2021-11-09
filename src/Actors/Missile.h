#pragma once
#include "Actor.h"
#include "../Commons/Shader.h"

class Missile : public Actor {
public:
    Missile(class Game* game);

    void UpdateActor(float deltaTime) override;
    void LateUpdateActor(float deltaTime) override;
    void ProcessInput(const uint8_t* state, float deltaTime) override;

private:
    class BoxColliderComponent* mCollider;
    float mSpeed = 30.0f;    // 速度
    float mDistance = 50.0f; // 射程距離

};
