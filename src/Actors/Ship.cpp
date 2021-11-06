#include "Ship.h"
#include "../Game.h"
#include "../Commons/Mesh.h"
#include "../Components/MeshComponent.h"

Ship::Ship(class Game *game)
: Actor(game)
{
    auto* meshComp = new MeshComponent(this);
    auto* mesh = game->GetRenderer()->GetMesh(game->GetAssetsPath() + "ship.fbx");
    meshComp->SetMesh(mesh);
    auto* shader = game->GetRenderer()->GetShader(Shader::ShaderType::PHONG);
    meshComp->SetShader(shader);
}

void Ship::UpdateActor(float deltaTime)
{
    // 回転が変わった場合
    bool isChangeRotLeft  = mIsRotLeft  != mIsRotLeftBefore;
    bool isChangeRotRight = mIsRotRight != mIsRotRightBefore;
    if (isChangeRotLeft || isChangeRotRight)
    {
        // 船の傾きを調整
        // 同時押しされた場合も考慮
        float rot = 0.0f;
        if (isChangeRotLeft)
        {
            rot += mIsRotLeft ? mRotTilt : -mRotTilt;
        }
        if (isChangeRotRight)
        {
            rot += mIsRotRight ? -mRotTilt : mRotTilt;
        }
        Quaternion q = Quaternion(GetForward(), Math::ToRadians(rot));
        SetRotation(Quaternion::Concatenate(GetRotation(), q));
    }
    // 回転中フラグを保持
    mIsRotLeftBefore = mIsRotLeft;
    mIsRotRightBefore = mIsRotRight;
}

void Ship::ProcessInput(const uint8_t *state)
{
    Actor::ProcessInput(state);

    // 押下キー方向に回転する
    mIsRotLeft = false;
    mIsRotRight = false;
    if (state[SDL_SCANCODE_A])
    {
        SetRotationY(Math::ToRadians(-mRotSpeed));
        mIsRotLeft = true;
    }
    if (state[SDL_SCANCODE_D])
    {
        SetRotationY(Math::ToRadians(mRotSpeed));
        mIsRotRight = true;
    }
}
