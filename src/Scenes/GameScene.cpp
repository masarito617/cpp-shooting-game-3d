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
    float tmpDegree = 0.0f;
    for (int i = 0; i < 15; i++)
    {
        auto* enemy = new Enemy(mGame);
        // 前回の出現位置+-60度
        tmpDegree += Math::GetRand(-60.0f, 60.0f);
        enemy->SetInitPositionByDegree(tmpDegree);
        // 速度徐々に速く
        enemy->SetSpeed(Math::GetRand(25.0f, 45.0f) * (1.0f + i*0.02f));
        // 大きさ
        enemy->SetScale(Math::GetRand(1.0f, 3.0f) * Math::VEC3_UNIT);
        // 揺れ幅 基本は横のみ
        enemy->SetShakeWidth(Vector2(Math::GetRand(-7.0f, 7.0f), 0.0f));
        // 数匹ごとに縦揺れも追加
        if (i%3 == 2)
        {
            enemy->SetShakeWidth(Vector2(Math::GetRand(-10.0f, 10.0f), Math::GetRand(-8.5f, 8.5f)));
        }
        // 3匹ずつ出現させる
        enemy->SetWaitTime(i / 3 * Math::GetRand(5.0f, 7.0f));
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
