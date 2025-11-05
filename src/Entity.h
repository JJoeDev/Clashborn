#ifndef ARKADE_ENTITY_H
#define ARKADE_ENTITY_H

#include <string>

#include "math/Vectors.h"
#include "Components/Transform.h"

namespace ark {
    class EntityManager;

    class Entity {
    public:
        virtual ~Entity() = default;

        void SetEntityTag(const std::string& tag) { m_tag = tag; }
        const std::string& GetEntityTag() { return m_tag; }

        virtual void Update(const float dt) = 0;
        virtual void Draw() const = 0;

    protected:
        const EntityManager* m_entityManager{nullptr};

        std::string m_tag{};

        comp::Transform m_transform{};
    };
}

#endif //ARKADE_ENTITY_H