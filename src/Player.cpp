#include "Player.h"

#include "Application.h"
#include "Settings/Misc.h"

namespace ark {
    Player::Player(const EntityManager* eManager, const input::InputMap& imap, const math::Vec2f& startPos) : m_inputs(imap) {
        m_specs = Application::Get().GetAppSpecs();

        m_entityManager = eManager;
        m_transform.Position = startPos;
        m_transform.Scale = {30, 60};

        m_aabbShape = {
            m_transform.Position.x,
            m_transform.Position.y,
            m_transform.Scale.x,
            m_transform.Scale.y
        };
    }

    Player::~Player() {
        m_entityManager = nullptr;
        m_specs = nullptr;
    }

    void Player::Update(const float dt) {
        math::Vec2f dir{};

        if (m_transform.Position.y + m_transform.Scale.y >= static_cast<float>(m_specs->height) - 5.0f) {
            m_grounded = true;
            m_velocity.y = 0.0f;
        }
        else {
            m_grounded = false;
            m_velocity.y += settings::GRAVITY_Y;
        }

        dir.x = IsKeyDown(m_inputs.RIGHT) - IsKeyDown(m_inputs.LEFT);

        if (IsKeyPressed(m_inputs.JUMP) && m_grounded) {
            m_velocity.y = m_jumpForce;
            m_grounded = false;
        }

        m_velocity.x = dir.x * m_baseSpeed;

        m_transform.Position += m_velocity * dt;
        m_aabbShape.Shape.x = m_transform.Position.x;
        m_aabbShape.Shape.y = m_transform.Position.y;
    }

    void Player::Draw() const {
        DrawRectangle(m_transform.Position.x, m_transform.Position.y, m_transform.Scale.x, m_transform.Scale.y, RED);
        DrawRectangleLinesEx(m_aabbShape.Shape, 1.0f, GREEN);
    }
}
