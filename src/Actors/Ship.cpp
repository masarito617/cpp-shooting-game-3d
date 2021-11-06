#include "Ship.h"
#include "Camera.h"
#include "../Game.h"
#include "../Commons/Mesh.h"
#include "../Components/MeshComponent.h"

Ship::Ship(class Game *game)
: Actor(game)
{
    auto* meshComp = new MeshComponent(this);
    auto* mesh = game->GetRenderer()->GetMesh(game->GetAssetsPath() + "ship.fbx");
    meshComp->SetMesh(mesh);
    auto* shader = game->GetRenderer()->GetShader(Shader::ShaderType::PHONG);
    meshComp->SetShader(shader);

    game->GetRenderer()->GetCamera()->SetTargetActor(this);
}

void Ship::UpdateActor(float deltaTime)
{
    // TODO
}

void Ship::ProcessInput(const uint8_t *state)
{
    Actor::ProcessInput(state);

    // TODO 回転処理と傾きを追加する
    float moveSpeed = 10.0f;
    Vector3 pos = GetPosition();
    if (state[SDL_SCANCODE_A])
    {
        pos.x -= moveSpeed;
    }
    if (state[SDL_SCANCODE_D])
    {
        pos.x += moveSpeed;
    }
    if (state[SDL_SCANCODE_W])
    {
        pos.y += moveSpeed;
    }
    if (state[SDL_SCANCODE_S])
    {
        pos.y -= moveSpeed;
    }
    SetPosition(pos);
}
