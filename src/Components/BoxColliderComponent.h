#pragma once
#include "Component.h"
#include "../Commons/Math.h"

class BoxColliderComponent : public Component {
public:
    BoxColliderComponent(class Actor* owner, int updateOrder = 100);
    ~BoxColliderComponent();

    void OnUpdateWorldTransform();

    struct AABB
    {
        AABB(const Vector3& min, const Vector3& max);

        void UpdatePointMinMax(const Vector3& point);
        void Rotate(const Quaternion& q);
        bool Contains(const Vector3& point) const;
        float MinDistSq(const Vector3& point) const;

        Vector3 mMin;
        Vector3 mMax;
    };
    bool Intersect(const AABB& a, const AABB& b);

private:
    AABB mObjectAABB;
    AABB mWorldAABB;
    bool mIsRotate;

public:
    void SetObjectAABB(const AABB& model) { mObjectAABB = model; }
    const AABB& GetWorldBox() const { return mWorldAABB; }

};
