#pragma once
#include "Actor.h"
#include "../Commons/Shader.h"

class Enemy : public Actor {
public:
    Enemy(class Game* game);
    ~Enemy();

    void UpdateActor(float deltaTime) override;
    void ProcessInput(const uint8_t* state, float deltaTime) override;

private:
    class BoxColliderComponent* mCollider;

public:
    class BoxColliderComponent* GetCollider() const { return mCollider; }

};
