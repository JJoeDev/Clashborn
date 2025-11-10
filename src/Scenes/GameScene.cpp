#include "GameScene.h"

#include "Player.h"
#include "Application.h"
#include "Platform.h"

namespace ark::scene {
    void GameScene::Start() {
        auto specs = Application::Get().GetAppSpecs();

        if (!IsTextureValid(m_background)) {
            m_background = LoadTexture(std::string(ASSETS_PATH + std::string("Background.png")).c_str());
        }

        auto plr1 = m_entityManager.CreateEntity<Player>(
            &m_entityManager,
            input::PlayerOneIMap{},
            math::Vec2f{200, 200},
            characters::EggGoblin()
            );
        plr1->SetEntityTag("Player");

        auto plr2 = m_entityManager.CreateEntity<Player>(
            &m_entityManager,
            input::PlayerTwoIMap{},
            math::Vec2f{static_cast<float>(specs->width - 200), 200},
            characters::MissKill()
            );
        plr2->SetEntityTag("Player");

        /// Create the level of entities with colliders
        m_entityManager.CreateEntity<Platform>(math::Vec2f{50.0f, 800.0f}, math::Vec2f{400.0f, 15.0f});
    }

    void GameScene::Stop() {
        m_entityManager.ClearEntities();
    }

    void GameScene::Update(const float dt) {
        DrawTexture(m_background, 0, 0, GRAY); // Draw because I fucked the attack sprite up

        m_entityManager.Update(dt);
    }

    void GameScene::Draw() const {
        m_entityManager.Draw();
    }
}
