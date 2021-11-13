#include "EnemyMarker.h"
#include "Camera.h"
#include "Enemy.h"
#include "../Game.h"
#include "../Commons/Texture.h"
#include "../Components/SpriteComponent.h"

EnemyMarker::EnemyMarker(class Game* game)
: Actor(game)
, mTarget(nullptr)
{
    auto* sprite = new SpriteComponent(this);
    auto* texture = new Texture();
    texture->Load(game->GetAssetsPath() + "marker.png");
    sprite->SetTexture(texture);

    // 最初は表示しない
    SetScale(Math::VEC3_ZERO);
}

EnemyMarker::~EnemyMarker()
{}

void EnemyMarker::UpdateActor(float deltaTime)
{
    Actor::UpdateActor(deltaTime);
}

void EnemyMarker::LateUpdateActor(float deltaTime)
{
    Actor::LateUpdateActor(deltaTime);

    // ターゲットが設定されていない場合
    if (!mTarget) return;

    // viewProjectionMatrixを首都九
    Matrix4 viewProjection = GetGame()->GetRenderer()->GetProjectionMatrix() * GetGame()->GetRenderer()->GetViewMatrix();
    // エネミーのクリップ座標を求める
    Matrix4 enemyWorld = mTarget->GetWorldTransform();
    Vector3 enemyPos = viewProjection * enemyWorld * Math::VEC3_UNIT;
    // プレイヤーのクリップ座標を求める
    auto* player = GetGame()->GetRenderer()->GetCamera()->GetTargetActor();
    Matrix4 playerWorld = player->GetWorldTransform();
    Vector3 playerPos = viewProjection * playerWorld * Math::VEC3_UNIT;

    // 画面に映っていないエネミーのみマーカーを付ける
    SetScale(Math::VEC3_ZERO);
    if (enemyPos.x < -1.0f || enemyPos.x > 1.0f)
    {
        // 横に範囲がずれているエネミー
        // 見える範囲に調整
        if (enemyPos.x < -1.0f) enemyPos.x = -0.95f;
        if (enemyPos.x > 1.0f)  enemyPos.x =  0.95f;

        enemyPos.x *= GetGame()->ScreenWidth*0.5f;
        enemyPos.y *= GetGame()->ScreenHeight*0.5f;
        SetPosition(enemyPos);
        // 向き調整
        Vector3 distance = enemyPos - playerPos;
        Vector3 rotation = GetRotation();
        rotation.z = Math::ToDegrees(atan2(distance.y, distance.x)-Math::Pi/2.0f);
        SetRotation(rotation);
        // マーカーを表示
        SetScale(Vector3(1.0f, 1.0f, 1.0f));
    }
    else if (enemyPos.z > 1.0f)
    {
        // 後ろ側のエネミー
        // XY値を反転してZを0にする
        enemyPos.x *= -GetGame()->ScreenWidth*0.5f;
        enemyPos.y *= -GetGame()->ScreenHeight*0.5f;
        enemyPos.z = 0.0f;
        SetPosition(enemyPos);
        // 向き調整
        Vector3 distance = enemyPos - playerPos;
        Vector3 rotation = GetRotation();
        rotation.z = Math::ToDegrees(atan2(distance.y, distance.x)-Math::Pi/2.0f);
        SetRotation(rotation);
        // マーカーを表示
        SetScale(Vector3(1.0f, 1.0f, 1.0f));
    }
}

void EnemyMarker::ProcessInput(const uint8_t *state, float deltaTime)
{
    Actor::ProcessInput(state, deltaTime);
}
