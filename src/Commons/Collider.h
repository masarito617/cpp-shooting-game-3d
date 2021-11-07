#pragma once
#include "../Commons/Math.h"

// AABB構造体
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

// 衝突判定処理
bool Intersect(const AABB& a, const AABB& b);
