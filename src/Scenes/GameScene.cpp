#include "GameScene.h"
#include "EndScene.h"
#include "../Game.h"
#include "../Actors/Enemy.h"

GameScene::GameScene(class Game *game)
:Scene(game)
{}

GameScene::~GameScene()
{}

void GameScene::Start()
{
    Scene::Start();

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

void GameScene::Update(float deltaTime)
{
    Scene::Update(deltaTime);

    // エネミーを全部撃破したらゲームクリア
    if (mGame->GetEnemies().empty())
    {
        mGame->SetGameClear(true);
        mGame->SetNextScene(new EndScene(mGame));
    }
}

void GameScene::ProcessInput(const Uint8 *state, float deltaTime)
{
    Scene::ProcessInput(state, deltaTime);
}

std::string const GameScene::GetSceneName()
{
    return "GAME";
}
