#include "Player.h"

#include <iostream>

#include "Application.h"
#include "EntityManager.h"
#include "Components/Health.h"
#include "Components/Velocity.h"
#include "Settings/Misc.h"

namespace ark {
    Player::Player(const EntityManager* eManager, const input::InputMap& imap, const math::Vec2f& startPos, const characters::Character chara) : m_inputs(imap), m_characterStats(chara) {
        m_specs = Application::Get().GetAppSpecs();

        m_entityManager = eManager;
        m_transform.Position = startPos;
        m_transform.Scale = {100, 200};

        AddComponent<comp::AABBShape>();
        AddComponent<comp::Health>();
        AddComponent<comp::Velocity>();

        m_health = GetComponent<comp::Health>();
        m_velocity = GetComponent<comp::Velocity>();
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
        m_health->maxHealthAmount = chara.health;
        m_attackBox->SetDamageAmount(chara.attackDamage);
    }

    Player::~Player() {
        UnloadTexture(m_sprite);

        m_entityManager = nullptr;
        m_specs = nullptr;
    }

    void Player::Update(const float dt) {
        if (m_health->dead) return;

        m_lastPosition = m_transform.Position;

        math::Vec2f dir{};
        dir.x = IsKeyDown(m_inputs.RIGHT) - IsKeyDown(m_inputs.LEFT);
        if (dir.x != 0.0f) m_xFacingDir = dir.x;

        if (m_grounded) {
            if (IsKeyPressed(m_inputs.JUMP)) {
                m_velocity->dir.y = m_jumpForce;
                m_grounded = false;
            }

            if (m_didGroundPound) {
                m_didGroundPound = false;

                std::vector<Entity*> entities = m_entityManager->TryFindEntitiesWithTag("Player");
                for (auto& e : entities) {
                    if (e == this) continue;

                    math::Vec2f dist = e->GetTransform().Position - m_transform.Position;
                    if (dist.Magnitude() <= m_groundPoundArea) {
                        e->GetComponent<comp::Velocity>()->dir.y = m_groundPoundForce;
                        e->GetComponent<comp::Health>()->TakeDamage(m_characterStats.groundPoundDamage);
                    }
                }
            }

            m_airJump = true;
        }
        else {
            m_velocity->dir.y += settings::GRAVITY_Y;

            if (m_airJump && IsKeyPressed(m_inputs.JUMP)) {
                m_velocity->dir.y += m_jumpForce;
                m_airJump = false;
            }

            if (IsKeyPressed(m_inputs.DUCK)) {
                m_velocity->dir.y = 0.0f;
                m_velocity->dir.y -= m_jumpForce * 4;
                m_didGroundPound = true;
            }
        }

        if (IsKeyPressed(m_inputs.ATTACK) && m_attackCooldown <= 0.0f) {
            m_attackCooldown = m_characterStats.attackCooldown;
            m_attackBox->RunAttack(m_xFacingDir);
        }

        if (m_attackCooldown > 0.0f) m_attackCooldown -= dt;

        m_velocity->dir.x = dir.x * m_baseSpeed;

        m_transform.Position += m_velocity->dir * dt;

        m_aabb->Shape.x = m_transform.Position.x;
        m_aabb->Shape.y = m_transform.Position.y;

        CollisionUpdate();

        m_attackBox->Update(dt);
    }

    void Player::Draw() const {
        if (m_health->dead) return;

        DrawTexture(m_sprite, m_transform.Position.x, m_transform.Position.y, WHITE);

        // Health bar                                     height | buffer
        DrawRectangle(m_aabb->Shape.x, m_aabb->Shape.y - 15 - 15, 100, 15, {16, 15, 15, 255});
        DrawRectangle(m_aabb->Shape.x, m_aabb->Shape.y - 15 - 15, 100 * (m_health->healthAmount / m_health->maxHealthAmount), 15, RED);

        // Cooldown bar
        if (m_attackCooldown > 0.0f)
            DrawRectangle(m_aabb->Shape.x, m_aabb->Shape.y - 35 - 15, 100 * (m_attackCooldown / m_characterStats.attackCooldown), 15, {0, 0, 255, 255});

        m_attackBox->Draw();
    }

    // PRIVATES
    void Player::CollisionUpdate() {
        // Ground check
        if (m_transform.Position.y + m_aabb->Shape.height >= m_specs->height - 5.0f) {
            m_transform.Position.y = m_specs->height - 5.0f - m_aabb->Shape.height;
            m_grounded = true;
            m_velocity->dir.y = 0.0f;
        }
        else {
            m_grounded = false;
        }

        // Collider checks
        std::vector<Entity*> colliders = m_entityManager->GetEntitiesWithComponent<comp::AABBShape>();
        for (auto& e : colliders) {
            if (e->GetEntityTag() == "Player") continue;

            comp::AABBShape* other = e->GetComponent<comp::AABBShape>();
            if (CheckCollisionRecs(other->Shape, m_aabb->Shape)) {
                if (m_velocity->dir.y > 0.0f && m_lastPosition.y + m_transform.Scale.y <= other->Shape.y) {
                    m_transform.Position.y = other->Shape.y - m_aabb->Shape.height;
                    m_velocity->dir.y = 0.0f;
                    m_grounded = true;
                }
            }
        }

        m_aabb->Shape.x = m_transform.Position.x;
        m_aabb->Shape.y = m_transform.Position.y;
    }
}
