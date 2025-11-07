#ifndef ARKADE_PLAYER_H
#define ARKADE_PLAYER_H

#include "Entity.h"
#include "Settings/Specifications.h"
#include "InputMaps/InputMaps.h"
#include "Components/AABBCollision.h"
#include "Components/Health.h"
#include "AttackBox.h"
#include "Characters/Characters.h"

namespace ark {
    class Player final : public Entity {
    public:
        Player(const EntityManager* eManager, const input::InputMap& imap, const math::Vec2f& startPos, const characters::Character);
        ~Player();

        void Update(const float dt) override;
        void Draw() const override;

    private:
        void CollisionUpdate();

    private:
        const settings::Specs* m_specs;
        const input::InputMap m_inputs;

        comp::AABBShape* m_aabb;
        comp::Health* m_health;

        std::unique_ptr<AttackBox> m_attackBox;

        int m_xFacingDir{};
        bool m_grounded{};
        float m_baseSpeed{};
        float m_jumpForce{};

        math::Vec2f m_velocity{};
    };
}

#endif //ARKADE_PLAYER_H
