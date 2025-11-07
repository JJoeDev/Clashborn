#ifndef ARKADE_AABBCOLLISION_H
#define ARKADE_AABBCOLLISION_H

#include <raylib.h>

#include "Component.h"

namespace ark::comp {
    struct AABBShape : public Component {
        bool Enabled{true};
        Rectangle Shape;

        void DebugDraw() const {
            DrawRectangleLinesEx(Shape, 1.0f, GREEN);
        }
    };
}

#endif //ARKADE_AABBCOLLISION_H