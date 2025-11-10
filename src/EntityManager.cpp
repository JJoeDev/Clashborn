#include "EntityManager.h"

namespace ark {
    const std::vector<Entity*> EntityManager::TryFindEntitiesWithTag(const std::string& tag) const {
        std::vector<Entity*> entities;
        for (const auto& e : m_entities) {
            if (e->GetEntityTag() == tag) entities.push_back(e.get());
        }

        return entities;
    }

    void EntityManager::ClearEntities() {
        for (auto& e : m_entities) {
            e.reset();
        }

        m_entities.clear();
    }

    void EntityManager::Update(const float dt) {
        for (const auto& e : m_entities) {
            e->Update(dt);
        }
    }

    void EntityManager::Draw() const {
        for (const auto& e : m_entities) {
            e->Draw();
        }
    }
}