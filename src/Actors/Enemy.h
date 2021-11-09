#pragma once
#include "Actor.h"
#include "../Commons/Shader.h"

class Enemy : public Actor {
public:
    Enemy(class Game* game);
    ~Enemy();

    void UpdateActor(float deltaTime) override;
    void ProcessInput(const uint8_t* state, float deltaTime) override;
    void SetInitPosition(const Vector3& pos);

    enum MoveType
    {
        STRAIGHT, // 直線移動
        SHAKE,    // 揺れながら移動
    };

private:
    class BoxColliderComponent* mCollider;

    MoveType mMoveType;     // 移動タイプ
    float mSpeed;           // 移動速度
    float mShakeWidth;      // 揺れる幅
    Vector3* mInitPosition; // 初期位置
    float mTimeCount;       // 経過時間
    float mWaitTime;        // 待機時間

    float mHappyRotSpeed = 3.5f; // 喜びの舞

public:
    class BoxColliderComponent* GetCollider() const { return mCollider; }
    void SetMoveType(const MoveType moveType) { mMoveType = moveType; }
    void SetSpeed(const float speed) { mSpeed = speed; }
    void SetShakeWidth(const float width) { mShakeWidth = width; }
    void SetWaitTime(const float time) { mWaitTime = time; }

};
