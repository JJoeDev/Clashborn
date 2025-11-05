#ifndef ARKADE_TRANSFORM_H
#define ARKADE_TRANSFORM_H

#include "Component.h"
#include "math/Vectors.h"

namespace ark::comp {
    struct Transform : public Component{
        math::Vec2f Position;
        math::Vec2f Scale;
        float Rotation;
    };
}

#endif //ARKADE_TRANSFORM_H