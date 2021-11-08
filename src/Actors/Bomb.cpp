#include "Bomb.h"
#include "../Game.h"
#include "../Actors/Camera.h"
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

    // 最初は大きさ0にする
    SetScale(Vector3(0.0f, 0.0f, 1.0f));
}

void Bomb::UpdateActor(float deltaTime)
{
    Actor::UpdateActor(deltaTime);

    // 徐々に大きくする
    float changeScale = mTimeCount / DisplayTime * 5.0f;
    if (changeScale > MaxScale) changeScale = MaxScale;
    SetScale(Vector3(changeScale, changeScale, 1.0f));
    // 表示時間を過ぎたら破棄
    mTimeCount += deltaTime;
    if (mTimeCount >= DisplayTime)
    {
        SetState(EDead);
    }
}

void Bomb::ProcessInput(const uint8_t *state, float deltaTime)
{
    Actor::ProcessInput(state, deltaTime);
}
