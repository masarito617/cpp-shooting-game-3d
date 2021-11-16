#include "Missile.h"
#include "Bomb.h"
#include "Enemy.h"
#include "../Game.h"
#include "../Commons/Collider.h"
#include "../Commons/Mesh.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/MeshComponent.h"

Missile::Missile(class Game *game)
: Actor(game)
{
    auto* meshComp = new MeshComponent(this);
    auto* mesh = game->GetRenderer()->GetMesh(game->GetAssetsPath() + "missile.fbx");
    meshComp->SetMesh(mesh);
    auto* shader = game->GetRenderer()->GetShader(Shader::ShaderType::SPRITE);
    meshComp->SetShader(shader);
    mCollider = new BoxColliderComponent(this);
    mCollider->SetObjectAABB(mesh->GetBox());
}

void Missile::UpdateActor(float deltaTime)
{
    Actor::UpdateActor(deltaTime);

    // 前方へ進む
    Vector3 pos = GetPosition();
    pos += mSpeed * deltaTime * GetForward();
    SetPosition(pos);

    // 一定距離離れたら破棄
    if (pos.Length() > mDistance)
    {
        SetState(EDead);
    }
}

void Missile::LateUpdateActor(float deltaTime)
{
    // エネミーと衝突したら破壊
    for (auto enemy : GetGame()->GetEnemies())
    {
        if (Intersect(mCollider->GetWorldBox(), enemy->GetCollider()->GetWorldBox()))
        {
            SetState(EDead);
            enemy->SetState(EDead);
            // 爆発エフェクトを生成
            auto* bomb = new Bomb(GetGame());
            bomb->SetPosition(enemy->GetPosition());
            bomb->SetRotation(enemy->GetRotation());
            bomb->SetMaxScale(enemy->GetScale().x * 2.0f);
            break;
        }
    }
}

void Missile::ProcessInput(const uint8_t *state, float deltaTime)
{
    Actor::ProcessInput(state, deltaTime);
}
