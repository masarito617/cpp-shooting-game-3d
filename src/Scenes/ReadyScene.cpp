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
    for (int i = 0; i < 12; i++)
    {
        auto* enemy = new Enemy(mGame);
        enemy->SetInitPositionByDegree(30.0f*i);
        enemy->SetSpeed(35.0f);
        enemy->SetWaitTime(i);
        if (i%3 == 2)
        {
            enemy->SetMoveType(Enemy::SHAKE);
        }
    }
}

void ReadyScene::Update(float deltaTime)
{}

void ReadyScene::ProcessInput(const Uint8 *state)
{}

std::string const ReadyScene::GetSceneName()
{
    return "READY";
}
