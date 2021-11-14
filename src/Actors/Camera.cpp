#include "Camera.h"
#include "../Game.h"

Camera::Camera(class Game *game)
: Actor(game)
, mTargetActor(nullptr)
{}

void Camera::UpdateActor(float deltaTime)
{
    Actor::UpdateActor(deltaTime);

    Vector3 position; // カメラ位置
    Vector3 target;   // ターゲット位置
    Vector3 up = Math::VEC3_UNIT_Y; // 上方向ベクトル
    if (!mTargetActor)
    {
        // ターゲットが設定されていない場合
        position = GetPosition();
        target = GetPosition() + mOffsetLookForward * GetForward();
    }
    else
    {
        // 登場アニメーションが完了していない場合
        if (!mIsAnimFinish)
        {
            // カメラ位置を少しずつずらす
            position = GetPosition();
            position += deltaTime * mAnimLookVec;
            SetPosition(position);
            // 注視点をターゲットの前方に設定
            target = mTargetActor->GetPosition();
            target += mAnimOffsetLookForward * mTargetActor->GetForward();
            // アニメーション時間更新
            mTotalAnimTime += deltaTime;
            if (mTotalAnimTime >= mAnimTime)
            {
                mIsAnimFinish = true;
            }
        }
        else
        {
            // カメラ位置をターゲットの後方に設定
            position = mTargetActor->GetPosition();
            position -= mOffsetPosForward * mTargetActor->GetForward();
            position += mOffsetPosUp * Math::VEC3_UNIT_Y;
            SetPosition(position);
            // 注視点をターゲットの前方に設定
            target = mTargetActor->GetPosition();
            target += mOffsetLookForward * mTargetActor->GetForward();
        }
    }
    Matrix4 viewMatrix = Matrix4::CreateLookAt(position, target, up);
    GetGame()->GetRenderer()->SetViewMatrix(viewMatrix);
}

void Camera::ProcessInput(const uint8_t *state, float deltaTime)
{
    Actor::ProcessInput(state, deltaTime);
}

// アニメーション開始
void Camera::AnimStart()
{
    // アニメーションフラグ初期化
    mTotalAnimTime = 0.0f;
    mIsAnimFinish = false;
    // アニメーション初期位置に設定
    SetPosition(mAnimOffsetInitDistance * mAnimLookVec);
}