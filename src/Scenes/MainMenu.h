#ifndef ARKADE_MAINMENU_H
#define ARKADE_MAINMENU_H

#include <string>

#include "Application.h"
#include "BaseScene.h"
#include "../math/Vectors.h"

namespace ark::scene {
    class MainMenu final : public BaseScene {
    public:
        MainMenu();
        ~MainMenu() override;

        void Start() override;
        void Stop() override;

        void Update(const float dt) override;
        void Draw() const override;

    private:
        const settings::Specs* m_specs;

        const std::string m_title{"HOLY FUQ A GAME"};
        const int m_titleFontSize{40};
        math::Vec2i m_titlePos{};

        const std::string m_playStr{"--=== PRESS [ SPACE ] TO PLAY ===--"};
        const int m_playStrFontSize{25};
        math::Vec2i m_playStrPos{};
    };
}

#endif //ARKADE_MAINMENU_H
