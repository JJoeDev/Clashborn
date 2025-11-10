#include "Platform.h"

#include "Components/AABBCollision.h"

namespace ark {
    Platform::Platform(const math::Vec2f& startPos, const math::Vec2f& size) {
        m_transform.Position = startPos;
        m_transform.Scale = size;

        AddComponent<comp::AABBShape>();
        auto aabb = GetComponent<comp::AABBShape>();
        aabb->Shape.x = startPos.x;
        aabb->Shape.y = startPos.y;
        aabb->Shape.width = size.x;
        aabb->Shape.height = size.y;
    }

    void Platform::Draw() const {
        DrawRectangle(m_transform.Position.x, m_transform.Position.y, m_transform.Scale.x, m_transform.Scale.y, BLACK);
    }

}