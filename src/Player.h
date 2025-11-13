#ifndef ARKADE_PLAYER_H
#define ARKADE_PLAYER_H

#include "Entity.h"
#include "Settings/Specifications.h"
#include "InputMaps/InputMaps.h"
#include "Characters/Characters.h"
#include "AttackBox.h"
#include "Components/AABBCollision.h"
#include "Components/Health.h"
#include "Components/Velocity.h"

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
        const settings::Specs* m_specs{nullptr};
        const input::InputMap m_inputs;

        comp::AABBShape* m_aabb{nullptr};
        comp::Health* m_health{nullptr};
        comp::Velocity* m_velocity{nullptr};

        std::unique_ptr<AttackBox> m_attackBox;

        const characters::Character m_characterStats;
        math::Vec2f m_lastPosition{};

        int m_xFacingDir{};
        bool m_grounded{};
        float m_baseSpeed{};
        float m_jumpForce{};
        float m_attackCooldown{};
        const float m_groundPoundForce{-400.0f};
        const float m_groundPoundArea{200.0f};
        bool m_didGroundPound{};
        bool m_airJump{};

        float m_deadTime{3.0f};
    };
}

#endif //ARKADE_PLAYER_H
