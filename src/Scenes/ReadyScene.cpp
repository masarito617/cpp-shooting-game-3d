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
,mMenuMsg(nullptr)
,mTitleMsg(nullptr)
{}

ReadyScene::~ReadyScene()
{}

void ReadyScene::Start()
{
    Scene::Start();

    // クリアフラグを初期化
    mGame->SetGameClear(false);
    // 宇宙船の作成
    auto* ship = new Ship(mGame);
    ship->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
    // カメラターゲットに設定
    mGame->GetRenderer()->GetCamera()->SetTargetActor(ship);
    // タイトルメッセージを表示
    mTitleMsg = new Actor(mGame);
    mTitleMsg->SetPosition(Vector3(-220.0f, 200.0f, 0.0f));
    auto* titleMsgSprite = new SpriteComponent(mTitleMsg, 200);
    titleMsgSprite->SetTexture(mGame->GetRenderer()->GetTexture(mGame->GetAssetsPath() + "msg_title.png"));
    // 見えやすいようにライティング調整
    mGame->GetRenderer()->SetDirLightDirection(Vector3(0.3f, 0.3f, 0.5f));
    // 登場アニメーション開始
    mGame->GetRenderer()->GetCamera()->AnimStart();
}

void ReadyScene::Update(float deltaTime)
{
    Scene::Update(deltaTime);

    // アニメーションが終わった場合
    if (!mStartMsg && mGame->GetRenderer()->GetCamera()->GetIsAnimFinish())
    {
        // タイトルメッセージを破棄
        mTitleMsg->SetState(Actor::EDead);
        // 開始メッセージを表示
        mStartMsg = new Actor(mGame);
        mStartMsg->SetPosition(Math::VEC3_ZERO);
        auto* startMsgSprite = new SpriteComponent(mStartMsg, 200);
        startMsgSprite->SetTexture(mGame->GetRenderer()->GetTexture(mGame->GetAssetsPath() + "msg_start.png"));
        // 操作説明を表示
        mMenuMsg = new Actor(mGame);
        mMenuMsg->SetPosition(Vector3(0.0f, 210.0f, 0.0f));
        auto* menuMsgSprite = new SpriteComponent(mMenuMsg, 200);
        menuMsgSprite->SetTexture(mGame->GetRenderer()->GetTexture(mGame->GetAssetsPath() + "msg_menu.png"));
        // ライティング元に戻す
        mGame->GetRenderer()->SetDirLightDirection(Vector3(0.5f, -0.35f, 0.35f));
    }
}

void ReadyScene::ProcessInput(const Uint8 *state, float deltaTime)
{
    Scene::ProcessInput(state, deltaTime);

    // 開始メッセージが表示されるまで処理しない
    if (!mStartMsg) return;

    // スペースかエンター押下でゲームシーンに遷移
    if (state[SDL_SCANCODE_SPACE] || state[SDL_SCANCODE_RETURN])
    {
        mGame->SetNextScene(new GameScene(mGame));
        mStartMsg->SetState(Actor::EDead);
        mMenuMsg->SetState(Actor::EDead);
    }
}

std::string const ReadyScene::GetSceneName()
{
    return "READY";
}
