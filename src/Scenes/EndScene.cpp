#include "EndScene.h"
#include "ReadyScene.h"
#include "../Actors/Actor.h"
#include "../Actors/Camera.h"
#include "../Actors/Enemy.h"
#include "../Actors/Ship.h"
#include "../Game.h"
#include "../Components/SpriteComponent.h"

EndScene::EndScene(class Game *game)
:Scene(game)
{}

EndScene::~EndScene()
{}

void EndScene::Start()
{
    Scene::Start();

    // 終了メッセージの作成
    mEndMsg = new Actor(mGame);
    mEndMsg->SetPosition(Math::VEC3_ZERO);
    auto* startMsgSprite = new SpriteComponent(mEndMsg, 200);
    startMsgSprite->SetTexture(
            mGame->GetRenderer()->GetTexture(mGame->GetAssetsPath() + (mGame->GetGameClear() ? "msg_clear.png" : "msg_over.png")));
}

void EndScene::Update(float deltaTime)
{
    Scene::Update(deltaTime);
}

void EndScene::ProcessInput(const Uint8 *state, float deltaTime)
{
    Scene::ProcessInput(state, deltaTime);

    // スペースかエンター押下で開始シーンに遷移
    if (state[SDL_SCANCODE_SPACE] || state[SDL_SCANCODE_RETURN])
    {
        mGame->SetNextScene(new ReadyScene(mGame));
        mEndMsg->SetState(Actor::EDead);
        // カメラターゲット破棄
        mGame->GetRenderer()->GetCamera()->GetTargetActor()->SetState(Actor::EDead);
        mGame->GetRenderer()->GetCamera()->SetTargetActor(nullptr);
        // エネミー破棄
        for (auto enemy : mGame->GetEnemies())
        {
            enemy->SetState(Actor::EDead);
        }
    }
}

std::string const EndScene::GetSceneName()
{
    return "END";
}
