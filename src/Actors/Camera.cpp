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
    Vector3 target = GetPosition() + 200.0f*GetForward(); // 200.0f前方がターゲット
    // ターゲットが設定されている場合
    if (mTargetActor)
    {
        // TODO 宇宙船の後方固定となるよう修正する
        target = mTargetActor->GetPosition() - GetPosition();
    }
    Vector3 up = Math::VEC3_UNIT_Y;
    Matrix4 viewMatrix = Matrix4::CreateLookAt(position, target, up);
    GetGame()->GetRenderer()->SetViewMatrix(viewMatrix);
}

void Camera::ProcessInput(const uint8_t *state)
{
    Actor::ProcessInput(state);
}
