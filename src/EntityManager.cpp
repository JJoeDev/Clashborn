#include "EntityManager.h"

namespace ark {
    const Entity* EntityManager::TryFindEntityWithTag(const std::string& tag) const {
        for (const auto& e : m_entities) {
            if (e->GetEntityTag() == tag) return e.get();
        }

        return nullptr;
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