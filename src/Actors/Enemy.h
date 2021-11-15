#pragma once
#include "Actor.h"
#include "../Commons/Shader.h"

class Enemy : public Actor {
public:
    Enemy(class Game* game);
    ~Enemy();

    void UpdateActor(float deltaTime) override;
    void ProcessInput(const uint8_t* state, float deltaTime) override;
    void SetInitPositionByDegree(float degree);

private:
    class BoxColliderComponent* mCollider;

    float mSpeed;          // 移動速度
    Vector2 mShakeWidth;   // 揺れる幅
    Vector3 mInitPosition; // 初期位置
    float mTimeCount;      // 経過時間
    float mWaitTime;       // 待機時間

    float mHappyRotSpeed = 1200.0f; // 喜びの舞
    float mAppearDistance = 150.0f; // 出現時の距離(100あたりから見えるようになる)

    float mTotalMove = 0.0f; // 合計移動距離

    class EnemyMarker* mMarker; // マーカー

public:
    class BoxColliderComponent* GetCollider() const { return mCollider; }
    void SetSpeed(const float speed) { mSpeed = speed; }
    void SetShakeWidth(const Vector2 width) { mShakeWidth = width; }
    void SetWaitTime(const float time) { mWaitTime = time; }

};
