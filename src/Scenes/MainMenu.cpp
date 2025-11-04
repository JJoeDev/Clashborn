#include "MainMenu.h"

#include <iostream>

#include "raylib.h"

namespace ark::scene {
    MainMenu::~MainMenu() {
        m_specs = nullptr;
    }

    void MainMenu::Start() {
        m_specs = Application::Get().GetAppSpecs();

        m_titlePos = {
            m_specs->width / 2 - MeasureText(m_title.c_str(), m_titleFontSize) / 2,
            200
        };

        m_playStrPos = {
            m_specs->width / 2 - MeasureText(m_playStr.c_str(), m_playStrFontSize) / 2,
            m_specs->height - 100
        };
    }

    void MainMenu::Stop() {
        m_specs = nullptr;
    }

    void MainMenu::Update(const float dt) {
        if (IsKeyPressed(KEY_SPACE)) {
            auto& app = Application::Get();
            app.SwitchScene(app.GetCurrentSceneIndex() + 1);
        }
    }

    void MainMenu::Draw() const {
        DrawText(m_title.c_str(),m_titlePos.x, m_titlePos.y, m_titleFontSize, RED);
        DrawText(m_playStr.c_str(), m_playStrPos.x, m_playStrPos.y, m_playStrFontSize, GREEN);
    }
}
