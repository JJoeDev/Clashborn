#ifndef ARKADE_CHARACTERSELECTION_H
#define ARKADE_CHARACTERSELECTION_H

#include "BaseScene.h"
#include "Settings/Specifications.h"
#include "SerialBridge.h"
#include "raylib.h"

#include <array>
#include <string>
#include <cstdint>

namespace ark::scene {
    class CharacterSelection final : public BaseScene {
    public:
        void Start() override;
        void Stop() override;

        void Update(const float dt) override;
        void Draw() const override;

    private:
        const settings::Specs* m_specs{nullptr};

        const std::array<std::string, 4> m_characterTexPath = {
            "BigBuffChad.png",
            "BigBlueAlien.png",
            "EggGoblin.png",
            "MissKill.png",
        };

        std::array<Texture2D, 4> m_characterPfp{};

        uint16_t m_p1Selection = 0;
        uint16_t m_p2Selection = 0;
        bool m_playerSelectTurn{false};

        void* m_serial{nullptr};
    };

}


#endif //ARKADE_CHARACTERSELECTION_H