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
    enemy->SetInitPosition(Vector3(20.0f, 0.0f, 40.0f));
    enemy->SetSpeed(35.0f);
    enemy->SetWaitTime(3.0f);
    auto* enemy2 = new Enemy(mGame);
    enemy2->SetInitPosition(Vector3(-10.0f, 0.0f, 40.0f));
    enemy2->SetMoveType(Enemy::SHAKE);
    enemy2->SetSpeed(45.0f);
    enemy2->SetWaitTime(3.0f);
    auto* enemy3 = new Enemy(mGame);
    enemy3->SetInitPosition(Vector3(-20.0f, 0.0f, 40.0f));
    enemy3->SetMoveType(Enemy::SHAKE);
    enemy3->SetShakeWidth(2.0f);
    enemy3->SetSpeed(25.0f);
    enemy3->SetWaitTime(3.0f);
    auto* enemy4 = new Enemy(mGame);
    enemy4->SetInitPosition(Vector3(5.0f, 0.0f, 40.0f));
    enemy4->SetSpeed(35.0f);
    enemy4->SetWaitTime(3.0f);
}

void ReadyScene::Update(float deltaTime)
{}

void ReadyScene::ProcessInput(const Uint8 *state)
{}

std::string const ReadyScene::GetSceneName()
{
    return "READY";
}
