#include "CharacterSelection.h"

#include <iostream>

#include "Application.h"
#include "SerialBridge.h"

namespace ark::scene {
    void CharacterSelection::Start() {
        m_specs = Application::Get().GetAppSpecs();

        m_p1Selection = static_cast<uint16_t>(Application::Get().m_playerOne);
        m_p2Selection = static_cast<uint16_t>(Application::Get().m_playerTwo);

        for (size_t i = 0; i < m_characterTexPath.size(); ++i) {
            m_characterPfp[i] = LoadTexture(std::string(ASSETS_PATH + m_characterTexPath[i]).c_str());
        }

        m_serial = OpenSerialPort();
    }

    void CharacterSelection::Stop() {
        CloseSerialPort(m_serial);

        for (const auto& tex : m_characterPfp) {
            UnloadTexture(tex);
        }
    }

    void CharacterSelection::Update(const float dt) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 pos = GetMousePosition();

            for (size_t i = 0; i < m_characterPfp.size(); ++i) {
                const auto& tex = m_characterPfp[i];

                const float left = 200.0f + tex.width * i * 4;
                const float right = left + tex.width * 4;

                if (pos.x > left && pos.x <= right) {
                    if (m_playerSelectTurn && i != m_p2Selection) {
                        m_p1Selection = i;
                        m_playerSelectTurn = !m_playerSelectTurn;
                    }
                    else if (!m_playerSelectTurn && i != m_p1Selection) {
                        m_p2Selection = i;
                        m_playerSelectTurn = !m_playerSelectTurn;
                    }
                }
            }
        }

        if (IsKeyPressed(KEY_SPACE)) {
            auto& app = Application::Get();
            app.m_playerOne = static_cast<characters::CHARACTERS>(m_p1Selection);
            app.m_playerTwo = static_cast<characters::CHARACTERS>(m_p2Selection);

            app.SwitchScene(app.GetCurrentSceneIndex() + 1);
        }

        if (IsKeyPressed(KEY_R)) {
            GetArduinoSerialMessage(m_serial);
        }
    }

    void CharacterSelection::Draw() const {
        DrawText("Character Selection", m_specs->width / 2 - MeasureText("Character Selection", 30) / 2, 50, 30, RED);
        DrawText("Press R to read RFID cards", m_specs->width / 2 - MeasureText("Press R to read RFID cards", 20) / 2, 100, 20, RED);

        for (size_t i = 0; i < m_characterPfp.size(); ++i) {
            const Texture2D& tex = m_characterPfp[i];
            DrawRectangleRounded({200.0f + tex.width * i * 4, 450.0f, 300.0f, 500.0f}, 0.25f, 12, {40, 39, 38, 255});
            DrawTextureEx(tex, {250.0f + tex.width * i * 4, 500.0f}, 0.0f, 2.0f, WHITE);

            if (i == m_p1Selection)
                DrawRectangleRoundedLinesEx({200.0f + tex.width * i * 4, 450.0f, 300.0f, 500.0f}, 0.25, 12, 3, RED);
            else if (i == m_p2Selection)
                DrawRectangleRoundedLinesEx({200.0f + tex.width * i * 4, 450.0f, 300.0f, 500.0f}, 0.25, 12, 3, BLUE);
        }
    }
}
