#ifndef ARKADE_INPUTMAPS_H
#define ARKADE_INPUTMAPS_H

#include <raylib.h>

namespace ark::input {
    struct InputMap {
        InputMap(uint16_t left, uint16_t right, uint16_t jump, uint16_t attack)
            : LEFT(left),
            RIGHT(right),
            JUMP(jump),
            ATTACK(attack)
        { }

        const uint16_t LEFT;
        const uint16_t RIGHT;
        const uint16_t JUMP;
        const uint16_t ATTACK;
    };

    struct PlayerOneIMap : public InputMap {
        PlayerOneIMap() : InputMap(KEY_A, KEY_D, KEY_W, KEY_E){}
    };

    struct PlayerTwoIMap : public InputMap {
        PlayerTwoIMap() : InputMap(KEY_LEFT, KEY_RIGHT, KEY_UP, KEY_RIGHT_CONTROL){}
    };
}

#endif //ARKADE_INPUTMAPS_H