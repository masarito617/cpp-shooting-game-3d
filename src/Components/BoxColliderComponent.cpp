#include "BoxColliderComponent.h"
#include "../Actors/Actor.h"
#include <algorithm>
#include <array>

BoxColliderComponent::BoxColliderComponent(class Actor *owner, int updateOrder)
: Component(owner, updateOrder)
, mObjectAABB(Math::VEC3_ZERO, Math::VEC3_ZERO)
, mWorldAABB(Math::VEC3_ZERO, Math::VEC3_ZERO)
, mIsRotate(true)
{}

BoxColliderComponent::~BoxColliderComponent() noexcept
{}

// Actorに合わせてワールド座標変換する
void BoxColliderComponent::OnUpdateWorldTransform()
{
    // オブジェクト座標でリセット
    mWorldAABB = mObjectAABB;
    // position
    mWorldAABB.mMin += mActor->GetPosition();
    mWorldAABB.mMax += mActor->GetPosition();
    // rotation
    if (mIsRotate)
    {
        mWorldAABB.Rotate(mActor->GetRotation());
    }
    // scale
    Vector3 scale = mActor->GetScale();
    mWorldAABB.mMin = Vector3(mWorldAABB.mMin.x*scale.x, mWorldAABB.mMin.y*scale.y, mWorldAABB.mMin.z*scale.z);
    mWorldAABB.mMax = Vector3(mWorldAABB.mMax.x*scale.x, mWorldAABB.mMax.y*scale.y, mWorldAABB.mMax.z*scale.z);
}

BoxColliderComponent::AABB::AABB(const Vector3 &min, const Vector3 &max)
: mMin(min)
, mMax(max)
{}

// AABBのMin、Max頂点を更新する
void BoxColliderComponent::AABB::UpdatePointMinMax(const Vector3 &point)
{
    mMin.x = std::min(mMin.x, point.x);
    mMin.y = std::min(mMin.y, point.y);
    mMin.z = std::min(mMin.z, point.z);
    mMax.x = std::max(mMax.x, point.x);
    mMax.y = std::max(mMax.y, point.y);
    mMax.z = std::max(mMax.z, point.z);
}

// 頂点の回転
void BoxColliderComponent::AABB::Rotate(const Quaternion& q)
{
    // AABBの8点を設定
    std::array<Vector3, 8> points;
    points[0] = mMin;
    points[1] = Vector3(mMax.x, mMin.y, mMin.z);
    points[2] = Vector3(mMin.x, mMax.y, mMin.z);
    points[3] = Vector3(mMin.x, mMin.y, mMax.z);
    points[4] = Vector3(mMin.x, mMax.y, mMax.z);
    points[5] = Vector3(mMax.x, mMin.y, mMax.z);
    points[6] = Vector3(mMax.x, mMax.y, mMin.z);
    points[7] = mMax;

    // Min、Max頂点を更新
    Vector3 p = Quaternion::RotateVec(points[0], q);
    mMin = p;
    mMax = p;
    for (int i = 1; i < points.size(); i++)
    {
        p = Quaternion::RotateVec(points[i], q);
        UpdatePointMinMax(p);
    }
}

// 頂点がAABB内に含まれるか？
bool BoxColliderComponent::AABB::Contains(const Vector3 &point) const
{
    bool isOutside =
            point.x < mMin.x ||
            point.y < mMin.y ||
            point.z < mMin.z ||
            point.x > mMax.x ||
            point.y > mMax.y ||
            point.z > mMax.z;
    return !isOutside;
}

// 頂点からAABBまでの最短距離の二乗を返却
float BoxColliderComponent::AABB::MinDistSq(const Vector3 &point) const
{
    float dx = std::max(mMin.x - point.x, 0.0f);
    dx = std::max(dx, point.x - mMax.x);
    float dy = std::max(mMin.y - point.y, 0.0f);
    dy = std::max(dy, point.y - mMax.y);
    float dz = std::max(mMin.z - point.z, 0.0f);
    dz = std::max(dz, point.z - mMax.z);
    return dx*dx + dy*dy + dz*dz;
}

// 衝突しているかどうか？
bool BoxColliderComponent::Intersect(const AABB &a, const AABB &b)
{
    // どれかの辺が重なっているか？
    bool noCollision =
            a.mMax.x < b.mMin.x ||
            a.mMax.y < b.mMin.y ||
            a.mMax.z < b.mMin.z ||
            b.mMax.x < a.mMin.x ||
            b.mMax.y < a.mMin.y ||
            b.mMax.z < a.mMin.z;
    return !noCollision;
}