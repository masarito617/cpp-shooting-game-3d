#include "ReadyScene.h"
#include "../Actors/Ship.h"

ReadyScene::ReadyScene(class Game *game)
:Scene(game)
{}

ReadyScene::~ReadyScene()
{}

void ReadyScene::Start()
{
    // 宇宙船の作成
    auto* ship = new Ship(mGame);
    ship->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
}

void ReadyScene::Update(float deltaTime)
{}

void ReadyScene::ProcessInput(const Uint8 *state)
{}

std::string const ReadyScene::GetSceneName()
{
    return "READY";
}
