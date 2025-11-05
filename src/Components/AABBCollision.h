#ifndef ARKADE_AABBCOLLISION_H
#define ARKADE_AABBCOLLISION_H

#include <raylib.h>

#include "Component.h"

namespace ark::comp {
    struct AABBShape : public Component{
        Rectangle Shape;
    };
}

#endif //ARKADE_AABBCOLLISION_H