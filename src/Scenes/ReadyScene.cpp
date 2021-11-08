#include "ReadyScene.h"
#include "../Game.h"
#include "../Actors/Camera.h"
#include "../Actors/Enemy.h"
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
    // カメラターゲットに設定
    mGame->GetRenderer()->GetCamera()->SetTargetActor(ship);

    // エネミー生成
    auto* enemy = new Enemy(mGame);
    enemy->SetPosition(Vector3(0.0f, 0.0f, 20.0f));
    enemy->SetRotationY(Math::ToRadians(180.0f));
    auto* enemy2 = new Enemy(mGame);
    enemy2->SetPosition(Vector3(5.0f, 0.0f, 20.0f));
    enemy2->SetRotationY(Math::ToRadians(180.0f));
    auto* enemy3 = new Enemy(mGame);
    enemy3->SetPosition(Vector3(-5.0f, 0.0f, 20.0f));
    enemy3->SetRotationY(Math::ToRadians(180.0f));
    auto* enemy4 = new Enemy(mGame);
    enemy4->SetPosition(Vector3(5.0f, 0.0f, 40.0f));
    enemy4->SetRotationY(Math::ToRadians(180.0f));
    auto* enemy5 = new Enemy(mGame);
    enemy5->SetPosition(Vector3(-5.0f, 0.0f, 40.0f));
    enemy5->SetRotationY(Math::ToRadians(180.0f));
}

void ReadyScene::Update(float deltaTime)
{}

void ReadyScene::ProcessInput(const Uint8 *state)
{}

std::string const ReadyScene::GetSceneName()
{
    return "READY";
}
