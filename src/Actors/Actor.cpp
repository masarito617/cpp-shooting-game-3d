#include "Actor.h"
#include <vector>
#include "../Game.h"
#include "../Components/Component.h"
#include "../Components/SpriteComponent.h"

Actor::Actor(Game* game)
:mState(EActive)
,mPosition(Math::VEC3_ZERO)
,mScale(Math::VEC3_UNIT)
,mRotation(Math::VEC3_ZERO)
,mGame(game)
,mRecalculateWorldTransform(true)
{
    // アクタ追加
    mGame->AddActor(this);
}

Actor::~Actor()
{
    // アクタ削除
    mGame->RemoveActor(this);
    // コンポーネント削除
    while (!mComponents.empty())
    {
        delete mComponents.back();
    }
}

// 更新処理
void Actor::Update(float deltaTime)
{
    if (mState == EActive)
    {
        CalculateWouldTransform();
        UpdateComponents(deltaTime);
        UpdateActor(deltaTime);
    }
}

// コンポーネント更新処理
void Actor::UpdateComponents(float deltaTime)
{
    for (auto component : mComponents)
    {
        component->Update(deltaTime);
    }
}

// アクタ更新処理
void Actor::UpdateActor(float deltaTime)
{
}

// アクタ更新後処理
void Actor::LateUpdateActor(float deltaTime)
{
}

// キー入力処理
void Actor::ProcessInput(const uint8_t *state,  float deltaTime)
{
}

// コンポーネント追加
void Actor::AddComponent(Component* component)
{
    // 設定された更新順となるようソートする
    int myOrder = component->GetUpdateOrder();
    auto iter = mComponents.begin();
    for (; iter != mComponents.end(); ++iter)
    {
        if (myOrder < (*iter)->GetUpdateOrder())
        {
            break;
        }
    }
    mComponents.insert(iter, component);
}

// コンポーネント削除
void Actor::RemoveComponent(Component* component)
{
    auto iter = std::find(mComponents.begin(), mComponents.end(), component);
    if (iter != mComponents.end())
    {
        mComponents.erase(iter);
    }
}

// ワールド変換座標計算処理
void Actor::CalculateWouldTransform()
{
    // ワールド変換座標を再計算する
    if (mRecalculateWorldTransform)
    {
        // 拡大縮小 -> 回転 -> 平行移動
        // を逆の順番で乗算する。
        mRecalculateWorldTransform = false;
        mWorldTransform = Matrix4::CreateTranslation(mPosition.x, mPosition.y, mPosition.z);
        mWorldTransform *= Matrix4::CreateQuaternion(GetRotationQuaternion());
        mWorldTransform *= Matrix4::CreateScale(mScale.x, mScale.y, mScale.z);

        // Componentのワールド座標を更新
        for (auto comp : mComponents)
        {
            comp->OnUpdateWorldTransform();
        }
    }
}

// 前方ベクトルを取得する
Vector3 Actor::GetForward() const
{
    // Z方向の単位ベクトルとクォータニオンから計算
    return Quaternion::RotateVec(Math::VEC3_UNIT_Z, GetRotationQuaternion());
}

// 右方ベクトルを取得する
Vector3 Actor::GetRight() const
{
    // X方向の単位ベクトルとクォータニオンから計算
    return Quaternion::RotateVec(Math::VEC3_UNIT_X, GetRotationQuaternion());
}

const Quaternion Actor::GetRotationQuaternion() const
{
    Quaternion q = Quaternion();
    // rotate X
    Vector3 right = Quaternion::RotateVec(Math::VEC3_UNIT_X, q);
    q = Quaternion::Concatenate(q, Quaternion(right, Math::ToRadians(mRotation.x)));
    // rotate Y
    Vector3 up = Quaternion::RotateVec(Math::VEC3_UNIT_Y, q);
    q = Quaternion::Concatenate(q, Quaternion(up, Math::ToRadians(mRotation.y)));
    // rotate Z
    Vector3 forward = Quaternion::RotateVec(Math::VEC3_UNIT_Z, q);
    q = Quaternion::Concatenate(q, Quaternion(forward, Math::ToRadians(mRotation.z)));
    return q;
}
