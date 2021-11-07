#include "Camera.h"
#include "../Game.h"

Camera::Camera(class Game *game)
: Actor(game)
, mTargetActor(nullptr)
{}

void Camera::UpdateActor(float deltaTime)
{
    Actor::UpdateActor(deltaTime);

    // カメラ位置よりビュー変換座標を設定する
    Vector3 position = GetPosition();
    Vector3 target = GetPosition() + 100.0f*GetForward(); // 100.0f前方がターゲット
    // ターゲットが設定されている場合
    if (mTargetActor)
    {
        // カメラ位置をターゲットの後方に更新
        position = mTargetActor->GetPosition();
        position -= mOffsetPosForward * mTargetActor->GetForward();
        position += mOffsetPosUp * Math::VEC3_UNIT_Y;
        SetPosition(position);
        // 注視点をターゲットの前方に設定
        target = mTargetActor->GetPosition();
        target += mOffsetTargetForward * mTargetActor->GetForward();
    }
    Vector3 up = Math::VEC3_UNIT_Y;
    Matrix4 viewMatrix = Matrix4::CreateLookAt(position, target, up);
    GetGame()->GetRenderer()->SetViewMatrix(viewMatrix);
}

void Camera::ProcessInput(const uint8_t *state, float deltaTime)
{
    Actor::ProcessInput(state, deltaTime);
}
