#include "Enemy.h"
#include "../Game.h"
#include "../Commons/Mesh.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/MeshComponent.h"

Enemy::Enemy(class Game *game)
        : Actor(game)
{
    auto* meshComp = new MeshComponent(this);
    auto* mesh = game->GetRenderer()->GetMesh(game->GetAssetsPath() + "enemy.fbx");
    meshComp->SetMesh(mesh);
    auto* shader = game->GetRenderer()->GetShader(Shader::ShaderType::PHONG);
    meshComp->SetShader(shader);
    mCollider = new BoxColliderComponent(this);
    mCollider->SetObjectAABB(mesh->GetBox());

    // エネミー追加
    game->AddEnemy(this);
}

Enemy::~Enemy()
{
    // エネミー削除
    GetGame()->RemoveEnemy(this);
}

void Enemy::UpdateActor(float deltaTime)
{
    Actor::UpdateActor(deltaTime);
}

void Enemy::ProcessInput(const uint8_t *state, float deltaTime)
{
    Actor::ProcessInput(state, deltaTime);
}
