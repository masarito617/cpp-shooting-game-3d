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

    // 一旦非表示
    SetScale(Math::VEC3_ZERO);

    // viewProjectionMatrix取得
    Matrix4 viewProjection = GetGame()->GetRenderer()->GetProjectionMatrix() * GetGame()->GetRenderer()->GetViewMatrix();
    // エネミーのクリップ座標を求める
    Matrix4 enemyWorld = mTarget->GetWorldTransform();
    Vector3 enemyViewPos = viewProjection * enemyWorld * Math::VEC3_UNIT;
    // プレイヤー取得
    auto* player = GetGame()->GetRenderer()->GetCamera()->GetTargetActor();
    if (!player) return;
    // プレイヤーのクリップ座標を求める
    Matrix4 playerWorld = player->GetWorldTransform();
    Vector3 playerViewPos = viewProjection * playerWorld * Math::VEC3_UNIT;

    // 画面に映っていないエネミーのみマーカーを付ける
    if (enemyViewPos.x < -1.0f || enemyViewPos.x > 1.0f || enemyViewPos.z > 1.0f)
    {
        // 横に範囲がずれているエネミー
        // 見える範囲に調整
        if (enemyViewPos.x < -1.0f) enemyViewPos.x = -0.95f;
        if (enemyViewPos.x > 1.0f)  enemyViewPos.x =  0.95f;

        enemyViewPos.x *= GetGame()->ScreenWidth*0.5f;
        enemyViewPos.y *= GetGame()->ScreenHeight*0.5f;

        // 後ろ側のエネミー
        // XY値を反転してZを0にする
        if (enemyViewPos.z > 1.0f)
        {
            enemyViewPos.x *= -1.0f;
            enemyViewPos.y *= -1.0f;
            enemyViewPos.z = 0.0f;
        }
        SetPosition(enemyViewPos);

        // 向き調整
        Vector3 distance = enemyViewPos - playerViewPos;
        Vector3 rotation = GetRotation();
        rotation.z = Math::ToDegrees(atan2(distance.y, distance.x)-Math::Pi/2.0f); // atan2-90度
        SetRotation(rotation);

        // マーカー表示
        // 距離によってサイズを変える
        float markerScale = 0.0f;
        float enemyDistance = mTarget->GetPosition().Length();
        if (enemyDistance < 75.0f)
        {
            markerScale = 1.0f;
        }
        else if (enemyDistance < 150.0f)
        {
            markerScale = 2.0f - enemyDistance / 75.0f;
        }
        SetScale(Vector3(markerScale, markerScale, markerScale));
    }
}

void EnemyMarker::ProcessInput(const uint8_t *state, float deltaTime)
{
    Actor::ProcessInput(state, deltaTime);
}
