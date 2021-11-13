#pragma once
#include <vector>
#include "../Commons/Math.h"

// アクタクラス
// *各アクタはこのクラスを継承する
class Actor
{
public:
    enum State
    {
        EActive, // アクティブ
        EDead    // 死亡
    };

    Actor(class Game* game);
    virtual ~Actor();

    void Update(float deltaTime);                  // 更新処理
    void UpdateComponents(float deltaTime);        // コンポーネント更新処理
    virtual void UpdateActor(float deltaTime);     // アクタ更新処理
    virtual void LateUpdateActor(float deltaTime); // アクタ更新後処理（移動後の結果等を使用する場合）
    virtual void ProcessInput(const uint8_t *state, float deltaTime); // キー入力処理

    void AddComponent(class Component* component);    // コンポーネント追加処理
    void RemoveComponent(class Component* component); // コンポーネント削除処理

    void CalculateWouldTransform(); // ワールド座標計算処理

    Vector3 GetForward() const; // 前方ベクトルの取得
    Vector3 GetRight() const;   // 右方ベクトルの取得

    const Quaternion GetRotationQuaternion() const; // クォータニオン取得

private:
    State mState;         // 状態
    Vector3 mPosition;    // 位置
    Vector3 mScale;       // 大きさ
    Vector3 mRotation;    // 回転
    Matrix4 mWorldTransform;         // ワールド変換座標
    bool mRecalculateWorldTransform; // 再計算フラグ

    std::vector<class Component*> mComponents; // 保有するコンポーネント
    class Game* mGame; // ゲームクラス

public:
    // Getter, Setter
    State GetState() const { return mState; }
    void SetState(const State state) { mState = state; }
    class Game* GetGame() const { return mGame; }
    // 座標の設定は再計算させる
    const Vector3& GetPosition() const { return mPosition; }
    void SetPosition(const Vector3& pos) { mPosition = pos; mRecalculateWorldTransform = true; }
    const Vector3& GetScale() const { return mScale; }
    void SetScale(const Vector3& scale) { mScale = scale; mRecalculateWorldTransform = true; }
    const Vector3& GetRotation() const { return mRotation; }
    void SetRotation(const Vector3& rotation) { mRotation = rotation; mRecalculateWorldTransform = true; }
    const Matrix4& GetWorldTransform() const { return mWorldTransform; }

};
