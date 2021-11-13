#include "SkyBox.h"
#include "../Game.h"
#include "../Commons/Mesh.h"
#include "../Components/MeshComponent.h"

SkyBox::SkyBox(class Game *game, std::string fbxName, float rotSpeed)
:Actor(game)
{
    auto* bgBackMeshComp = new MeshComponent(this);
    auto* bgBackMesh = game->GetRenderer()->GetMesh(game->GetAssetsPath() + fbxName);
    bgBackMeshComp->SetMesh(bgBackMesh);
    auto* bgBackShader = game->GetRenderer()->GetShader(Shader::ShaderType::SPRITE);
    bgBackMeshComp->SetShader(bgBackShader);

    // 回転速度を設定
    mRotSpeed = rotSpeed;
}

void SkyBox::UpdateActor(float deltaTime)
{
    Actor::UpdateActor(deltaTime);

    // 回転させる
    Vector3 rotation = GetRotation();
    rotation.y += mRotSpeed * deltaTime;
    SetRotation(rotation);
}

void SkyBox::ProcessInput(const uint8_t *state, float deltaTime)
{
    Actor::ProcessInput(state, deltaTime);
}
