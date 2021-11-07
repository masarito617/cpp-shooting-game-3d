#include "Missile.h"
#include "../Game.h"
#include "../Commons/Mesh.h"
#include "../Components/MeshComponent.h"

Missile::Missile(class Game *game)
: Actor(game)
{
    auto* meshComp = new MeshComponent(this);
    auto* mesh = game->GetRenderer()->GetMesh(game->GetAssetsPath() + "missile.fbx");
    meshComp->SetMesh(mesh);
    auto* shader = game->GetRenderer()->GetShader(Shader::ShaderType::SPRITE);
    meshComp->SetShader(shader);
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

void Missile::ProcessInput(const uint8_t *state, float deltaTime)
{
    Actor::ProcessInput(state, deltaTime);
}
