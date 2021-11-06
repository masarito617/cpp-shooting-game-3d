#include "Bomb.h"
#include "../Game.h"
#include "../Commons/Mesh.h"
#include "../Components/MeshComponent.h"

Bomb::Bomb(class Game *game)
        : Actor(game)
{
    auto* meshComp = new MeshComponent(this);
    auto* mesh = game->GetRenderer()->GetMesh(game->GetAssetsPath() + "bomb.fbx");
    meshComp->SetMesh(mesh);
    auto* shader = game->GetRenderer()->GetShader(Shader::ShaderType::SPRITE);
    meshComp->SetShader(shader);
}

void Bomb::UpdateActor(float deltaTime)
{
    // TODO
}

void Bomb::ProcessInput(const uint8_t *state)
{
    // TODO
}
