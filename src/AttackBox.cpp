#include "AttackBox.h"

#include <iostream>

#include "EntityManager.h"
#include "Components/AABBCollision.h"
#include "Components/Health.h"

namespace ark {
    AttackBox::AttackBox(const EntityManager* eManager, const Entity* parent, const Rectangle& size) : m_parent(parent), m_aabbOffsets(size) {
        m_entityManager = eManager;

        AddComponent<comp::AABBShape>();
        m_aabb = GetComponent<comp::AABBShape>();

        m_aabb->Shape = size;
        m_aabb->Enabled = false;

        m_sprite = LoadTexture(std::string(ASSETS_PATH + std::string("Attack.png")).c_str());
    }

    void AttackBox::Update(const float dt) {
        if (m_lifetime > 0.0f) {
            if (!m_visible) m_visible = true;

            m_lifetime -= dt;
        }
        else if (m_visible) {
            m_visible = false;
        }
    }

    void AttackBox::Draw() const {
        if (!m_visible) return;
        float width = m_sprite.width;
        float height = m_sprite.height;

        Rectangle src = {0.0f, 0.0f, width * m_xDirection, height};
        Vector2 dst = {m_aabb->Shape.x, m_aabb->Shape.y};

        DrawTextureRec(m_sprite, src, dst, {255, 255, 255, static_cast<uint8_t>(255 * (m_lifetime / m_maxLifetime))});

        m_aabb->DebugDraw();
    }

    void AttackBox::RunAttack(int xDirection) {
        m_xDirection = xDirection;
        m_aabb->Enabled = true;

        m_lifetime = m_maxLifetime;

        const auto& parentT = m_parent->GetTransform();
        m_aabb->Shape = {
            m_aabbOffsets.x * xDirection + parentT.Position.x,
            m_aabbOffsets.y + parentT.Position.y,
            m_aabb->Shape.width,
            m_aabb->Shape.height
        };

        std::vector<Entity*> others = m_entityManager->GetEntitiesWithComponent<comp::AABBShape>();
        for (auto& e : others) {
            if (e == this || e == m_parent) continue;

            if (CheckCollisionRecs(m_aabb->Shape, e->GetComponent<comp::AABBShape>()->Shape)) {
                if (auto h = e->GetComponent<comp::Health>()) {
                    h->TakeDamage(m_damageAmount);
                }
            }
        }

        m_aabb->Enabled = false;
    }
}
