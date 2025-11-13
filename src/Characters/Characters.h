#ifndef ARKADE_CHARACTERS_H
#define ARKADE_CHARACTERS_H

#include <string>
#include <raylib.h>

namespace ark::characters {
    enum class CHARACTERS {
        BigBuffChad = 0,
        BigBlueAlien,
        EggGoblin,
        MissKill,
        COUNT, // The amount of characters there are
    };

    struct Character {
        ~Character() = default;

        float movespeed;
        float health;
        float jumpHeight;
        float attackDamage;
        float attackCooldown;
        float groundPoundDamage;
        Texture2D sprite;
    };

    struct Chad : Character {
        Chad() : Character() {
            movespeed = 450.0f;
            health = 200.0f;
            jumpHeight = -600.0f;
            attackDamage = 50.0f;
            attackCooldown = 2.0f;
            groundPoundDamage = 10.0f;
            sprite = LoadTexture(std::string(ASSETS_PATH + std::string("BigBuffChad.png")).c_str());
        }
    };

    struct Alien : Character {
        Alien() : Character() {
            movespeed = 500.0f;
            health = 100.0f;
            jumpHeight = -650.0f;
            attackDamage = 25.0f;
            attackCooldown = 0.5f;
            groundPoundDamage = 10.0f;
            sprite = LoadTexture(std::string(ASSETS_PATH + std::string("BigBlueAlien.png")).c_str());
        }
    };

    struct EggGoblin : Character {
        EggGoblin() : Character() {
            movespeed = 500.0f;
            health = 100.0f;
            jumpHeight = -650.0f;
            attackDamage = 25.0f;
            attackCooldown = 0.5f;
            groundPoundDamage = 10.0f;
            sprite = LoadTexture(std::string(ASSETS_PATH + std::string("EggGoblin.png")).c_str());
        }
    };

    struct MissKill : Character {
        MissKill() : Character() {
            movespeed = 500.0f;
            health = 100.0f;
            jumpHeight = -650.0f;
            attackDamage = 25.0f;
            attackCooldown = 0.5f;
            groundPoundDamage = 10.0f;
            sprite = LoadTexture(std::string(ASSETS_PATH + std::string("MissKill.png")).c_str());
        }
    };

    inline Character GetCharacter(const CHARACTERS c) noexcept {
        switch (c) {
        case CHARACTERS::BigBuffChad:
            return Chad();
            break;
        case CHARACTERS::BigBlueAlien:
            return Alien();
            break;
        case CHARACTERS::EggGoblin:
            return EggGoblin();
            break;
        case CHARACTERS::MissKill:
            return MissKill();
            break;
        default:
            break;
        }
    }
}

#endif //ARKADE_CHARACTERS_H