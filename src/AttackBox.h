#ifndef ARKADE_ATTACKBOX_H
#define ARKADE_ATTACKBOX_H

#include "Entity.h"
#include "Components/AABBCollision.h"

namespace ark {
    class AttackBox final : public Entity {
    public:
        AttackBox(const EntityManager* eManager, const Entity* parent, const Rectangle& size);

        void Update(const float dt) override;
        void Draw() const override;

        void RunAttack(int xDirection);

        void SetDamageAmount(const float amount) { m_damageAmount = amount; }

    private:
        const Entity* const m_parent;
        comp::AABBShape* m_aabb;
        const Rectangle m_aabbOffsets;

        bool m_visible{};
        const float m_maxLifetime{0.25f};
        float m_lifetime{m_maxLifetime};

        int m_xDirection{};
        float m_damageAmount{};
    };
}

#endif //ARKADE_ATTACKBOX_H