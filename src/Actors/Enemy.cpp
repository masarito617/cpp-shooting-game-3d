#include "Enemy.h"
#include "EnemyMarker.h"
#include "../Game.h"
#include "../Commons/Mesh.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/MeshComponent.h"
#include <cmath>

Enemy::Enemy(class Game *game)
: Actor(game)
, mSpeed(5.0f)
, mShakeWidth(Math::VEC2_ZERO)
, mTimeCount(0.0f)
, mWaitTime(0.0f)
, mMarker(nullptr)
{
    auto* meshComp = new MeshComponent(this);
    auto* mesh = game->GetRenderer()->GetMesh(game->GetAssetsPath() + "enemy.fbx");
    meshComp->SetMesh(mesh);
    auto* shader = game->GetRenderer()->GetShader(Shader::ShaderType::PHONG);
    meshComp->SetShader(shader);
    mCollider = new BoxColliderComponent(this);
    mCollider->SetObjectAABB(mesh->GetBox());

    // マーカー追加
    mMarker = new EnemyMarker(game);
    mMarker->SetTarget(this);

    // エネミー追加
    game->AddEnemy(this);
}

Enemy::~Enemy()
{
    // エネミー削除
    GetGame()->RemoveEnemy(this);
    // マーカー削除
    mMarker->SetState(EDead);
}

void Enemy::UpdateActor(float deltaTime)
{
    Actor::UpdateActor(deltaTime);

    // 待機時間分待つ
    mTimeCount += deltaTime;
    if (mTimeCount < mWaitTime) return;

    // プレイヤー位置(0, 0)まで来た場合
    Vector3 pos = GetPosition();
    if (fabs(pos.x) <= 1.0f && fabs(pos.y) <= 1.0f && fabs(pos.z) <= 1.0f)
    {
        // 喜びの舞い
        Vector3 rotation = GetRotation();
        rotation.y += mHappyRotSpeed * deltaTime;
        SetRotation(rotation);
        return;
    }

    // 真ん中に来るまで進む
    if (mTotalMove < mAppearDistance - 0.0f) {
        mTotalMove += (mSpeed * deltaTime * GetForward()).Length();
    }

    // 幅が設定されている場合は揺らす
    Vector3 rightOffset = Math::VEC3_ZERO + cosf(mTimeCount / 0.2f) * mShakeWidth.x * GetRight(); // 横揺れ
    Vector3 upOffset    = Vector3(0.0f, cosf(mTimeCount / 0.2f) * mShakeWidth.y, 0.0f); // 縦揺れ

    // 位置更新
    Vector3 newPos = mInitPosition + (mTotalMove * GetForward() + rightOffset + upOffset);
    SetPosition(newPos);
}

void Enemy::ProcessInput(const uint8_t *state, float deltaTime)
{
    Actor::ProcessInput(state, deltaTime);
}

// 上から見た時の角度から位置を設定する
// *正面：0度 右斜め前：30度
void Enemy::SetInitPositionByDegree(float degree)
{
    // Y軸の回転クォータニオン
    Quaternion q(Math::VEC3_UNIT_Y, Math::ToRadians(degree));
    // 正面のベクトルを回転した位置を求める
    Vector3 pos = mAppearDistance * Math::VEC3_UNIT_Z;
    pos = Quaternion::RotateVec(pos, q);
    Actor::SetPosition(pos);
    // 初期位置を保持する
    mInitPosition = Vector3(pos.x, pos.y, pos.z);
    // 中央を向かせる(270-θ)
    float radian = atan2(pos.z, pos.x);
    Vector3 rotation = GetRotation();
    rotation.y += Math::ToDegrees(1.5f*Math::Pi - radian);
    SetRotation(rotation);
}