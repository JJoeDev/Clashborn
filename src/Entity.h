#ifndef ARKADE_ENTITY_H
#define ARKADE_ENTITY_H

#include <string>
#include <typeindex>
#include <unordered_map>
#include <memory>

#include "Components/Transform.h"

namespace ark {
    class EntityManager;

    class Entity {
    public:
        virtual ~Entity() = default;

        void SetEntityTag(const std::string& tag) { m_tag = tag; }
        const std::string& GetEntityTag() { return m_tag; }

        const comp::Transform& GetTransform() const { return m_transform; }

        virtual void Update(const float dt) = 0;
        virtual void Draw() const = 0;

        template<typename T, typename... Args>
        void AddComponent(Args&&... args) {
            static_assert(!std::is_same_v<comp::Component, T>, "TComponent must derive from Component");
            m_components[typeid(T)] = std::make_unique<T>(std::forward<Args>(args)...);
        }

        template<typename T>
        T* GetComponent() {
            auto it = m_components.find(typeid(T));
            if (it != m_components.end()) {
                return static_cast<T*>(it->second.get());
            }

            return nullptr;
        }

        template<typename T>
        bool HasComponent() const {
            return m_components.contains(typeid(T));
        }

    protected:
        const EntityManager* m_entityManager{nullptr};

        std::string m_tag{};

        comp::Transform m_transform{};

        Texture2D m_sprite{};

    private:
        std::unordered_map<std::type_index, std::unique_ptr<comp::Component>> m_components;
    };
}

#endif //ARKADE_ENTITY_H