#ifndef ARKADE_PLAYER_H
#define ARKADE_PLAYER_H

#include "Entity.h"
#include "Settings/Specifications.h"

namespace ark {
    class Player final : public Entity {
    public:
        Player(const EntityManager* eManager, const math::Vec2f& startPos);
        ~Player();

        void Update(const float dt) override;
        void Draw() const override;

    private:
        const settings::Specs* m_specs;

        bool m_grounded{};
        const float m_baseSpeed{200.0f};
        const float m_jumpForce{-750.0f};
    };
}

#endif //ARKADE_PLAYER_H
