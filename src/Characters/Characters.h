#ifndef ARKADE_CHARACTERS_H
#define ARKADE_CHARACTERS_H

#include <string>

namespace ark::characters {
    enum class CHARACTERS {
        BigBuffChad = 0,
        BigBlueAlien,
    };

    struct Character {
        ~Character() = default;

        float movespeed;
        float health;
        float jumpHeight;
        float attackDamage;
        Texture2D sprite;
    };

    struct Chad : Character {
        Chad() : Character() {
            movespeed = 450.0f;
            health = 200.0f;
            jumpHeight = -500.0f;
            attackDamage = 50.0f;
            sprite = LoadTexture(std::string(ASSETS_PATH + std::string("BigBuffChad.png")).c_str());
        }
    };

    struct Alien : Character {
        Alien() : Character() {
            movespeed = 600.0f;
            health = 100.0f;
            jumpHeight = -750.0f;
            attackDamage = 25.0f;
            sprite = LoadTexture(std::string(ASSETS_PATH + std::string("BigBlueAlien.png")).c_str());
        }
    };

    inline Character GetCharacterStats(const CHARACTERS character) {
        switch (character) {
        case CHARACTERS::BigBuffChad:
            return Chad();
            break;
        case CHARACTERS::BigBlueAlien:
            return Alien();
            break;
        default:
            break;
        }
    }
}

#endif //ARKADE_CHARACTERS_H