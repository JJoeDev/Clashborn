#include "Player.h"

#include <iostream>

#include "Application.h"
#include "EntityManager.h"
#include "Settings/Misc.h"

namespace ark {
    Player::Player(const EntityManager* eManager, const input::InputMap& imap, const math::Vec2f& startPos) : m_inputs(imap) {
        m_specs = Application::Get().GetAppSpecs();

        m_entityManager = eManager;
        m_transform.Position = startPos;
        m_transform.Scale = {30, 60};

        AddComponent<comp::AABBShape>();

        m_aabb = GetComponent<comp::AABBShape>();
        m_aabb->Shape = {
            startPos.x,
            startPos.y,
            m_transform.Scale.x,
            m_transform.Scale.y,
        };
    }

    Player::~Player() {
        m_entityManager = nullptr;
        m_specs = nullptr;
    }

    void Player::Update(const float dt) {
        math::Vec2f lastPosition = m_transform.Position;

        math::Vec2f dir{};
        dir.x = IsKeyDown(m_inputs.RIGHT) - IsKeyDown(m_inputs.LEFT);

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

        m_velocity.x = dir.x * m_baseSpeed;

        m_transform.Position += m_velocity * dt;

        m_aabb->Shape.x = m_transform.Position.x;
        m_aabb->Shape.y = m_transform.Position.y;

        m_grounded = false;
        std::vector<Entity*> colliders = m_entityManager->GetEntitiesWithComponent<comp::AABBShape>();
        for (auto& e : colliders) {
            if (e == this) continue;

            auto* otherAABB = e->GetComponent<comp::AABBShape>();
            if (CheckCollisionRecs(otherAABB->Shape, m_aabb->Shape)) {
                float xMove = m_transform.Position.x - lastPosition.x;
                float yMove = m_transform.Position.y - lastPosition.y;

                if (std::abs(yMove) > std::abs(xMove)) {
                    // Vertical response
                    if (yMove > 0.0f) { // Moving Down, landed on something
                        m_transform.Position.y = otherAABB->Shape.y - m_aabb->Shape.height;
                        m_velocity.y = 0.0f;
                        m_grounded = true;
                    }
                    else if (yMove < 0.0f) { // Moving up, hit head on something
                        m_transform.Position.y = otherAABB->Shape.y + otherAABB->Shape.height;
                        m_velocity.y = 0.0f;
                    }
                }
                else if (xMove != 0) {
                    if (xMove > 0) {
                        m_transform.Position.x = otherAABB->Shape.x - m_aabb->Shape.width;
                    }
                    else {
                        m_transform.Position.x = otherAABB->Shape.x + otherAABB->Shape.width;
                    }

                    m_velocity.x = 0.0f;
                }
            }
        }

        if (m_transform.Position.y + m_aabb->Shape.height >= m_specs->height - 5.0f) {
            m_transform.Position.y = m_specs->height - 5.0f - m_aabb->Shape.height;
            m_grounded = true;
            m_velocity.y = 0.0f;
        }

        m_aabb->Shape.x = m_transform.Position.x;
        m_aabb->Shape.y = m_transform.Position.y;
    }

    void Player::Draw() const {
        DrawRectangle(m_transform.Position.x, m_transform.Position.y, m_transform.Scale.x, m_transform.Scale.y, RED);
        DrawRectangleLinesEx(m_aabb->Shape, 1.0f, GREEN);
    }
}
