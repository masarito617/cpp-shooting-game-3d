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

    // エネミーのクリップ座標を求める
    Matrix4 world = mTarget->GetWorldTransform();
    Matrix4 view = GetGame()->GetRenderer()->GetViewMatrix();
    Matrix4 projection = GetGame()->GetRenderer()->GetProjectionMatrix();
    Vector3 position = projection * view * world * Vector3(1.0f, 1.0f, 1.0f);
    // TODO カメラの後ろのエネミーにもマーカー付ける
    // 画面に映っていないエネミーにマーカーを付ける
    SetScale(Math::VEC3_ZERO);
    if (position.x < -1.0f || position.x > 1.0f || position.y < -1.0f || position.y > 1.0f)
    {
        SetScale(Vector3(1.0f, 1.0f, 1.0f));
        if (position.x < -1.0f) position.x = -1.0f;
        if (position.x > 1.0f)  position.x =  1.0f;
        if (position.y < -1.0f) position.y = -1.0f;
        if (position.y > 1.0f)  position.y =  1.0f;
        position.x *= GetGame()->ScreenWidth*0.5f;
        position.y *= GetGame()->ScreenHeight*0.5f;
        SetPosition(position);
    }
}

void EnemyMarker::ProcessInput(const uint8_t *state, float deltaTime)
{
    Actor::ProcessInput(state, deltaTime);
}
