#include "BoxColliderComponent.h"
#include "../Actors/Actor.h"

BoxColliderComponent::BoxColliderComponent(class Actor *owner, int updateOrder)
: Component(owner, updateOrder)
, mObjectAABB(Math::VEC3_ZERO, Math::VEC3_ZERO)
, mWorldAABB(Math::VEC3_ZERO, Math::VEC3_ZERO)
{}

BoxColliderComponent::~BoxColliderComponent()
{}

// Actorの更新に合わせてワールド座標変換する
void BoxColliderComponent::OnUpdateWorldTransform()
{
    // オブジェクト座標でリセット
    mWorldAABB = mObjectAABB;
    // scale
    Vector3 scale = mActor->GetScale();
    mWorldAABB.mMin = Vector3(mWorldAABB.mMin.x*scale.x, mWorldAABB.mMin.y*scale.y, mWorldAABB.mMin.z*scale.z);
    mWorldAABB.mMax = Vector3(mWorldAABB.mMax.x*scale.x, mWorldAABB.mMax.y*scale.y, mWorldAABB.mMax.z*scale.z);
    // rotation
    mWorldAABB.Rotate(mActor->GetRotation());
    // position
    mWorldAABB.mMin += mActor->GetPosition();
    mWorldAABB.mMax += mActor->GetPosition();
}
