#ifndef ARKADE_INPUTMAPS_H
#define ARKADE_INPUTMAPS_H

#include <raylib.h>

namespace ark::input {
    struct InputMap {
        InputMap(unsigned short left, unsigned short right, unsigned short jump) : LEFT(left), RIGHT(right), JUMP(jump){}

        const unsigned short LEFT;
        const unsigned short RIGHT;
        const unsigned short JUMP;
    };

    struct PlayerOneIMap : public InputMap {
        PlayerOneIMap() : InputMap(KEY_A, KEY_D, KEY_W){}
    };

    struct PlayerTwoIMap : public InputMap {
        PlayerTwoIMap() : InputMap(KEY_LEFT, KEY_RIGHT, KEY_UP){}
    };
}

#endif //ARKADE_INPUTMAPS_H