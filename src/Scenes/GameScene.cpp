#include "GameScene.h"

#include "Player.h"
#include "raylib.h"

namespace ark::scene {
    void GameScene::Start() {
        auto plr1 = m_entityManager.CreateEntity<Player>(&m_entityManager, math::Vec2f{200, 200});
        plr1->SetEntityTag("Player1");
    }

    void GameScene::Stop() {
        m_entityManager.ClearEntities();
    }

    void GameScene::Update(const float dt) {
        m_entityManager.Update(dt);
    }

    void GameScene::Draw() const {
        m_entityManager.Draw();
    }
}
