#include "Player.h"

#include "Application.h"
#include "Settings/Misc.h"

namespace ark {
    Player::Player(const EntityManager* eManager, const math::Vec2f& startPos) {
        m_specs = Application::Get().GetAppSpecs();
        m_entityManager = eManager;
        m_position = startPos;
    }

    Player::~Player() {
        m_entityManager = nullptr;
        m_specs = nullptr;
    }

    void Player::Update(const float dt) {
        math::Vec2f dir{};

        if (m_position.y + 15.0f >= m_specs->height - 5) {
            m_grounded = true;
            m_velocity.y = 0.0f;
        }
        else {
            m_grounded = false;
            m_velocity.y += settings::GRAVITY_Y;
        }

        dir.x = IsKeyDown(KEY_D) - IsKeyDown(KEY_A);

        if (IsKeyPressed(KEY_SPACE) && m_grounded) {
            m_velocity.y = m_jumpForce;
            m_grounded = false;
        }

        m_velocity.x = dir.x * m_baseSpeed;

        m_position += m_velocity * dt;
    }

    void Player::Draw() const {
        DrawCircleV(m_position, 15.0f, RED);
    }
}
