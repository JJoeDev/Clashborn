#ifndef ARKADE_PLATFORM_H
#define ARKADE_PLATFORM_H

#include "Entity.h"

namespace ark {
    class Platform : public Entity {
    public:
        Platform(const math::Vec2f& startPos, const math::Vec2f& size);

        void Update(const float dt) override {}
        void Draw() const override;

    private:

    };
}

#endif //ARKADE_PLATFORM_H