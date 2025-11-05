#ifndef ARKADE_PLAYER_H
#define ARKADE_PLAYER_H

#include "Entity.h"
#include "Settings/Specifications.h"
#include "InputMaps/InputMaps.h"
#include "Components/AABBCollision.h"

namespace ark {
    class Player final : public Entity {
    public:
        Player(const EntityManager* eManager, const input::InputMap& imap, const math::Vec2f& startPos);
        ~Player();

        void Update(const float dt) override;
        void Draw() const override;

    private:
        const settings::Specs* m_specs;
        const input::InputMap m_inputs;

        comp::AABBShape m_aabbShape;

        bool m_grounded{};
        const float m_baseSpeed{200.0f};
        const float m_jumpForce{-750.0f};

        math::Vec2f m_velocity{};
    };
}

#endif //ARKADE_PLAYER_H
