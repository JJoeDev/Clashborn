#ifndef ARKADE_ENTITYMANAGER_H
#define ARKADE_ENTITYMANAGER_H

#include <memory>
#include <vector>

#include "Entity.h"

namespace ark {
    class EntityManager {
    public:
        template<typename TEntity, typename... Args>
        TEntity* CreateEntity(Args&&... args) {
            auto entity = std::make_unique<TEntity>(std::forward<Args>(args)...);
            TEntity* ptr = entity.get();
            m_entities.push_back(std::move(entity));
            return ptr;
        }

        // Loops through all stored entities, returns pointer if tags match else returns nullptr
        const Entity* TryFindEntityWithTag(const std::string& tag) const;

        void ClearEntities();

        void Update(const float dt);
        void Draw() const;

    private:
        std::vector<std::unique_ptr<Entity>> m_entities{};
    };
}

#endif //ARKADE_ENTITYMANAGER_H