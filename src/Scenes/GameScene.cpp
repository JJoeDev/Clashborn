#include "GameScene.h"

#include "Player.h"
#include "Application.h"

namespace ark::scene {
    void GameScene::Start() {
        auto specs = Application::Get().GetAppSpecs();

        auto plr1 = m_entityManager.CreateEntity<Player>(&m_entityManager, input::PlayerOneIMap{}, math::Vec2f{200, 200});
        plr1->SetEntityTag("Player");

        auto plr2 = m_entityManager.CreateEntity<Player>(&m_entityManager, input::PlayerTwoIMap{}, math::Vec2f{static_cast<float>(specs->width - 200), 200});
        plr2->SetEntityTag("Player");
    }

    void GameScene::Stop() {
        m_entityManager.ClearEntities();
    }

    void GameScene::Update(const float dt) {
        m_entityManager.Update(dt);
    }

    void GameScene::Draw() const {
        m_entityManager.Draw();
        DrawFPS(10, 10);
    }
}
