#include "Ship.h"
#include "Bomb.h"
#include "Camera.h"
#include "Enemy.h"
#include "Missile.h"
#include "../Game.h"
#include "../Commons/Mesh.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/MeshComponent.h"
#include "../Scenes/EndScene.h"

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

    // gameクラスに保持
    game->SetShip(this);
}

void Ship::UpdateActor(float deltaTime)
{
    Actor::UpdateActor(deltaTime);

    // 回転が変わった場合
    bool isChangeRotLeft  = mIsRotLeft  != mIsRotLeftBefore;
    bool isChangeRotRight = mIsRotRight != mIsRotRightBefore;
    if (isChangeRotLeft || isChangeRotRight)
    {
        // 船の傾きを調整
        // 同時押しされた場合も考慮
        float rot = 0.0f;
        if (mIsRotLeft)  rot += mRotTilt;
        if (mIsRotRight) rot += -mRotTilt;
        Vector3 rotation = GetRotation();
        rotation.z = rot;
        SetRotation(rotation);
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
            // 爆発エフェクトを生成
            auto* bomb = new Bomb(GetGame());
            Vector3 position = GetPosition();
            position -= 2.0f * GetForward();
            bomb->SetPosition(position);
            // 画面の方を向かせる
            Vector3 rotation = Vector3(-15.0f, GetRotation().y + 180.0f, 0.0f);
            bomb->SetRotation(rotation);
            // ゲーム終了
            GetGame()->SetNextScene(new EndScene(GetGame()));
            break;
        }
    }
}

void Ship::ProcessInput(const uint8_t *state, float deltaTime)
{
    Actor::ProcessInput(state, deltaTime);

    // GameScene以外は操作不能にする
    if (GetGame()->GetScene()->GetSceneName() != "GAME") return;

    // 押下キー方向に回転する
    mIsRotLeft = false;
    mIsRotRight = false;
    if (state[SDL_SCANCODE_A])
    {
        Vector3 rotation = GetRotation();
        rotation.y += -mRotSpeed * deltaTime;
        SetRotation(rotation);
        mIsRotLeft = true;
    }
    if (state[SDL_SCANCODE_D])
    {
        Vector3 rotation = GetRotation();
        rotation.y += mRotSpeed * deltaTime;
        SetRotation(rotation);
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
            Vector3 rotation = GetRotation();
            if (state[SDL_SCANCODE_W])
            {
                rotation.x = -mShotRotVertical;
            }
            if (state[SDL_SCANCODE_S])
            {
                rotation.x = mShotRotVertical;
            }
            missile->SetRotation(rotation);
        }
    }
}
