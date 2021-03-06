#pragma once
#include <SDL.h>
#include <string>
#include <vector>
#include "Commons/Math.h"
#include "Commons/Renderer.h"

// ゲーム管理クラス
// *ゲーム全体の流れ、アクタ生成、テクスチャ読込を行う
class Game
{
public:
    Game();
    bool Initialize(char* argv[]); // ゲーム初期化
    bool LoadData();   // データロード処理
    void RunLoop();    // ゲームループ処理
    void Shutdown();   // シャットダウン処理

    // アクタ追加・削除
    void AddActor(class Actor* actor);
    void RemoveActor(class Actor* actor);

    // エネミー追加・削除
    void AddEnemy(class Enemy* enemy);
    void RemoveEnemy(class Enemy* enemy);

    constexpr static const float ScreenWidth  = 1024.0f; // スクリーン横幅
    constexpr static const float ScreenHeight = 768.0f;  // スクリーン縦幅

private:
    void Update();                      // シーン更新処理
    void ProcessInput(float deltaTime); // 入力検知
    void GenerateOutput();              // 出力処理

    std::vector<class Actor*> mActors;        // アクタリスト
    std::vector<class Actor*> mPendingActors; // 待機中のアクタリスト

    class Renderer* mRenderer;

    Uint32 mTicksCount; // ゲーム時間
    bool mIsRunning;    // 実行中か否か？
    bool mIsLoopActors; // アクタのループ処理か？
    bool mIsGameClear;  // ゲームクリアしたか？

    class Scene* mScene;     // 現在のシーン
    class Scene* mNextScene; // 遷移するシーン

    class Ship* mShip; // 宇宙船(プレイヤー)
    std::vector<class Enemy*> mEnemies; // エネミー群

    // 絶対パス(argv引数から設定)
    std::string AbsolutePath;
    
    // Mac + CLion環境での相対パス
    const std::string AssetsPath = "../Assets/";      // Assetsパス
    const std::string ShaderPath = "../src/Shaders/"; // シェーダーパス

    // Win + VisualStudio環境での相対パス
    //const std::string AssetsPath = "Assets\\";       // Assetsパス
    //const std::string ShaderPath = "src\\Shaders\\"; // シェーダーパス

public:
    // getter, setter
    Scene* GetScene() const { return mScene; }
    void SetScene(class Scene* scene) { mScene = scene; }
    Scene* GetNextScene() const { return mNextScene; }
    void SetNextScene(class Scene* scene) { mNextScene = scene; }
    std::string GetAssetsPath() const { return AssetsPath; }
    std::string GetShaderPath() const { return ShaderPath; }
    class Renderer* GetRenderer() const { return mRenderer; }
    std::vector<class Enemy*> GetEnemies() { return mEnemies; }
    void SetShip(class Ship* ship) { mShip = ship; }
    Ship* GetShip() const { return mShip; }
    void SetGameClear(const bool isClear) { mIsGameClear = isClear; }
    bool GetGameClear() const { return mIsGameClear; }

    std::string GetAbsolutePath() const { return AbsolutePath; }

};
