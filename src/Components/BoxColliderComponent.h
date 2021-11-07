#pragma once
#include "Component.h"
#include "../Commons/Collider.h"
#include "../Commons/Math.h"

// AABBを使用したColliderクラス
class BoxColliderComponent : public Component {
public:
    BoxColliderComponent(class Actor* owner, int updateOrder = 100);
    ~BoxColliderComponent();

    void OnUpdateWorldTransform() override;

private:
    AABB mObjectAABB;
    AABB mWorldAABB;

public:
    void SetObjectAABB(const AABB& model) { mObjectAABB = model; }
    const AABB& GetWorldBox() const { return mWorldAABB; }

};
