#include "SkyBox.h"
#include "../Game.h"
#include "../Commons/Mesh.h"
#include "../Components/MeshComponent.h"

SkyBox::SkyBox(class Game *game)
:Actor(game)
{
    // バック側の背景
    bgBack = new Actor(game);
    bgBack->SetScale(Vector3(1.5f, 1.5f, 1.5f));
    auto* bgBackMeshComp = new MeshComponent(bgBack);
    auto* bgBackMesh = game->GetRenderer()->GetMesh(game->GetAssetsPath() + "bg_back.fbx");
    bgBackMeshComp->SetMesh(bgBackMesh);
    auto* bgBackShader = game->GetRenderer()->GetShader(Shader::ShaderType::SPRITE);
    bgBackMeshComp->SetShader(bgBackShader);

    // フロント側の背景
    bgFront = new Actor(game);
    bgFront->SetScale(Vector3(1.0f, 1.0f, 1.0f));
    auto* bgFrontMeshComp = new MeshComponent(bgFront);
    auto* bgFrontMesh = game->GetRenderer()->GetMesh(game->GetAssetsPath() + "bg_front.fbx");
    bgFrontMeshComp->SetMesh(bgFrontMesh);
    auto* bgFrontShader = game->GetRenderer()->GetShader(Shader::ShaderType::SPRITE);
    bgFrontMeshComp->SetShader(bgFrontShader);
}

void SkyBox::UpdateActor(float deltaTime)
{
    Actor::UpdateActor(deltaTime);

    // 回転させる
    bgBack->SetRotationY(Math::ToRadians(backRotSpeed * deltaTime));
    bgFront->SetRotationY(Math::ToRadians(frontRotSpeed * deltaTime));
}

void SkyBox::ProcessInput(const uint8_t *state, float deltaTime)
{
    Actor::ProcessInput(state, deltaTime);
}
