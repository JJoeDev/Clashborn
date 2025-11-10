#ifndef ARKADE_HEALTH_H
#define ARKADE_HEALTH_H

#include "Component.h"

namespace ark::comp {
    struct Health final : public Component {
        float maxHealthAmount{};
        float healthAmount{};
        bool dead{false};

        void TakeDamage(float amount) {
            healthAmount -= amount;
            if (healthAmount <= 0.0f) dead = true;
        }
    };
}

#endif //ARKADE_HEALTH_H
