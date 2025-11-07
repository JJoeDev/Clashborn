#include "Player.h"

#include "Application.h"
#include "EntityManager.h"
#include "Components/Health.h"
#include "Settings/Misc.h"

namespace ark {
    Player::Player(const EntityManager* eManager, const input::InputMap& imap, const math::Vec2f& startPos, const characters::Character chara) : m_inputs(imap) {
        m_specs = Application::Get().GetAppSpecs();

        m_entityManager = eManager;
        m_transform.Position = startPos;
        m_transform.Scale = {100, 200};

        AddComponent<comp::AABBShape>();
        AddComponent<comp::Health>();

        m_health = GetComponent<comp::Health>();
        m_aabb = GetComponent<comp::AABBShape>();
        m_aabb->Shape = {
            startPos.x,
            startPos.y,
            m_transform.Scale.x,
            m_transform.Scale.y,
        };

        m_attackBox = std::make_unique<AttackBox>(eManager, this, Rectangle{100, 50, 100, 100});

        m_sprite = chara.sprite;
        m_baseSpeed = chara.movespeed;
        m_jumpForce = chara.jumpHeight;

        m_health->healthAmount = chara.health;
        m_attackBox->SetDamageAmount(chara.attackDamage);
    }

    Player::~Player() {
        UnloadTexture(m_sprite);

        m_entityManager = nullptr;
        m_specs = nullptr;
    }

    void Player::Update(const float dt) {
        if (m_health->dead) return;

        math::Vec2f dir{};
        dir.x = IsKeyDown(m_inputs.RIGHT) - IsKeyDown(m_inputs.LEFT);
        if (dir.x != 0.0f) m_xFacingDir = dir.x;

        if (m_grounded) {
            if (IsKeyPressed(m_inputs.JUMP)) {
                m_velocity.y = m_jumpForce;
                m_grounded = false;
            }
            else {
                m_velocity.y = 0.0f;
            }
        }
        else {
            m_velocity.y += settings::GRAVITY_Y;
        }

        if (IsKeyPressed(m_inputs.ATTACK)) {
            m_attackBox->RunAttack(m_xFacingDir);
        }

        m_velocity.x = dir.x * m_baseSpeed;

        m_transform.Position += m_velocity * dt;

        m_aabb->Shape.x = m_transform.Position.x;
        m_aabb->Shape.y = m_transform.Position.y;

        CollisionUpdate();

        m_attackBox->Update(dt);
    }

    void Player::Draw() const {
        if (m_health->dead) return;
        m_aabb->DebugDraw();

        DrawTexture(m_sprite, m_transform.Position.x, m_transform.Position.y, WHITE);

        m_attackBox->Draw();
    }

    // PRIVATES
    void Player::CollisionUpdate() {
        if (m_transform.Position.y + m_aabb->Shape.height >= m_specs->height - 5.0f) {
            m_transform.Position.y = m_specs->height - 5.0f - m_aabb->Shape.height;
            m_grounded = true;
            m_velocity.y = 0.0f;
        }

        m_aabb->Shape.x = m_transform.Position.x;
        m_aabb->Shape.y = m_transform.Position.y;
    }
}
