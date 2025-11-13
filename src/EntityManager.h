#ifndef ARKADE_ENTITYMANAGER_H
#define ARKADE_ENTITYMANAGER_H

#include <memory>
#include <optional>
#include <vector>

#include "Entity.h"

namespace ark {
    class EntityManager {
    public:
        template<typename TEntity, typename... Args>
        TEntity* CreateEntity(Args&&... args) {
            static_assert(std::is_base_of_v<Entity, TEntity>, "TEntity must derive from Entity");

            auto entity = std::make_unique<TEntity>(std::forward<Args>(args)...);
            TEntity* ptr = entity.get();
            m_entities.push_back(std::move(entity));
            return ptr;
        }

        // Loops through all stored entities, returns pointer if tags match else returns nullptr
        [[nodiscard]] std::optional<std::vector<Entity*>> TryFindEntitiesWithTag(const std::string& tag) const;

        template<typename TComponent>
        [[nodiscard]] std::vector<Entity*> GetEntitiesWithComponent() const {
            std::vector<Entity*> result;
            for (auto& entity : m_entities) {
                if (entity->HasComponent<TComponent>()) {
                    result.push_back(entity.get());
                }
            }

            return result;
        }

        void ClearEntities();

        void Update(const float dt);
        void Draw() const;

    private:
        std::vector<std::unique_ptr<Entity>> m_entities{};
    };
}

#endif //ARKADE_ENTITYMANAGER_H