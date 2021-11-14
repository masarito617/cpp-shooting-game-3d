#include "ReadyScene.h"
#include "GameScene.h"
#include "../Game.h"
#include "../Actors/Actor.h"
#include "../Actors/Camera.h"
#include "../Actors/Ship.h"
#include "../Components/SpriteComponent.h"

ReadyScene::ReadyScene(class Game *game)
:Scene(game)
,mStartMsg(nullptr)
{}

ReadyScene::~ReadyScene()
{}

void ReadyScene::Start()
{
    Scene::Start();
    // クリアフラグを初期化
    mGame->SetGameClear(false);
    // 開始メッセージの作成
    mStartMsg = new Actor(mGame);
    mStartMsg->SetPosition(Math::VEC3_ZERO);
    auto* startMsgSprite = new SpriteComponent(mStartMsg, 200);
    startMsgSprite->SetTexture(mGame->GetRenderer()->GetTexture(mGame->GetAssetsPath() + "msg_start.png"));
    // 宇宙船の作成
    auto* ship = new Ship(mGame);
    ship->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
    // カメラターゲットに設定
    mGame->GetRenderer()->GetCamera()->SetTargetActor(ship);
}

void ReadyScene::Update(float deltaTime)
{
    Scene::Update(deltaTime);
}

void ReadyScene::ProcessInput(const Uint8 *state, float deltaTime)
{
    Scene::ProcessInput(state, deltaTime);

    // スペースかエンター押下でゲームシーンに遷移
    if (state[SDL_SCANCODE_SPACE] || state[SDL_SCANCODE_RETURN])
    {
        mGame->SetNextScene(new GameScene(mGame));
        mStartMsg->SetState(Actor::EDead);
    }
}

std::string const ReadyScene::GetSceneName()
{
    return "READY";
}
