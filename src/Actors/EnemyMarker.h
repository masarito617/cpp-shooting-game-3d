#pragma once
#include "Actor.h"

// エネミー位置のマーカー
class EnemyMarker : public Actor {
public:
    EnemyMarker(class Game* game);
    ~EnemyMarker();

    void UpdateActor(float deltaTime) override;
    void ProcessInput(const uint8_t* state, float deltaTime) override;

private:
    class Enemy* mTarget; // ターゲット

public:
    void SetTarget(class Enemy* target) { mTarget = target; }

};
