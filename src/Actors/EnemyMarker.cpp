#include "EnemyMarker.h"
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

    // ターゲットが設定されていない場合
    if (!mTarget) return;

    // TODO 指定斜角以外のエネミー位置を表示する
}

void EnemyMarker::ProcessInput(const uint8_t *state, float deltaTime)
{
    Actor::ProcessInput(state, deltaTime);
}
