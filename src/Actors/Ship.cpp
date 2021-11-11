#include "Ship.h"
#include "Bomb.h"
#include "Camera.h"
#include "Enemy.h"
#include "Missile.h"
#include "../Game.h"
#include "../Commons/Mesh.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/MeshComponent.h"

Ship::Ship(class Game *game)
: Actor(game)
{
    auto* meshComp = new MeshComponent(this);
    auto* mesh = game->GetRenderer()->GetMesh(game->GetAssetsPath() + "ship.fbx");
    meshComp->SetMesh(mesh);
    auto* shader = game->GetRenderer()->GetShader(Shader::ShaderType::PHONG);
    meshComp->SetShader(shader);
    mCollider = new BoxColliderComponent(this);
    mCollider->SetObjectAABB(mesh->GetBox());
}

void Ship::UpdateActor(float deltaTime)
{
    Actor::UpdateActor(deltaTime);

    // 回転が変わった場合
    bool isChangeRotLeft  = mIsRotLeft  != mIsRotLeftBefore;
    bool isChangeRotRight = mIsRotRight != mIsRotRightBefore;
    if (isChangeRotLeft || isChangeRotRight)
    {
        // TODO 船の角度を保持する
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

    // ミサイルを撃つ間隔を開ける
    if (!mIsCanShot)
    {
        mDeltaShotTime += deltaTime;
        if (mDeltaShotTime > CanShotTime)
        {
            mIsCanShot = true;
            mDeltaShotTime = 0.0f;
        }
    }
}

void Ship::LateUpdateActor(float deltaTime)
{
    // エネミーと衝突したら破壊
    for (auto enemy : GetGame()->GetEnemies())
    {
        if (Intersect(mCollider->GetWorldBox(), enemy->GetCollider()->GetWorldBox()))
        {
            // プレイヤーが消えるため、ダミーのアクタをカメラターゲットに設定す
            auto* dummy = new Actor(GetGame());
            dummy->SetPosition(GetPosition());
            dummy->SetRotation(GetRotation());
            GetGame()->GetRenderer()->GetCamera()->SetTargetActor(dummy);
            // プレイヤー破棄
            SetState(EDead);
            // TODO 保持している角度を使ってQuaternionを計算する
            // 爆発エフェクトを生成
            auto* bomb = new Bomb(GetGame());
            bomb->SetPosition(GetPosition());
            bomb->SetRotation(GetRotation());
            break;
        }
    }
}

void Ship::ProcessInput(const uint8_t *state, float deltaTime)
{
    Actor::ProcessInput(state, deltaTime);

    // 押下キー方向に回転する
    mIsRotLeft = false;
    mIsRotRight = false;
    if (state[SDL_SCANCODE_A])
    {
        SetRotationY(Math::ToRadians(-mRotSpeed * deltaTime));
        mIsRotLeft = true;
    }
    if (state[SDL_SCANCODE_D])
    {
        SetRotationY(Math::ToRadians(mRotSpeed * deltaTime));
        mIsRotRight = true;
    }
    // ミサイル発射
    if (state[SDL_SCANCODE_K])
    {
        if (mIsCanShot) {
            // 撃つ間隔を開けるためフラグを変更
            mIsCanShot = false;
            mDeltaShotTime = 0.0f;
            // 前方にミサイル生成
            auto* missile = new Missile(GetGame());
            missile->SetPosition(GetPosition() + 3.0f * GetForward());

            // 縦方向の調整
            Quaternion rot = GetRotation();
            if (state[SDL_SCANCODE_W])
            {
                Quaternion q = Quaternion(GetRight(), Math::ToRadians(-mShotRotVertical));
                rot = Quaternion::Concatenate(rot, q);
            }
            if (state[SDL_SCANCODE_S])
            {
                Quaternion q = Quaternion(GetRight(), Math::ToRadians(mShotRotVertical));
                rot = Quaternion::Concatenate(rot, q);
            }
            missile->SetRotation(rot);
        }
    }
}
