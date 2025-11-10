#ifndef ARKADE_VELOCITY_H
#define ARKADE_VELOCITY_H

#include "Component.h"
#include "math/Vectors.h"

namespace ark::comp {
    struct Velocity : Component {
        math::Vec2f dir{};
    };
}

#endif //ARKADE_VELOCITY_H
