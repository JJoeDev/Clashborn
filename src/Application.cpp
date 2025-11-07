#include "Application.h"

#include <cassert>
#include <iostream>
#include <raylib.h>

namespace ark {
    static Application* s_app = nullptr;

    Application::Application(const settings::Specs& specs) : m_specs(specs) {
        s_app = this;

        SetConfigFlags(FLAG_MSAA_4X_HINT);
        InitWindow(specs.width, specs.height, specs.title.c_str());
        SetTargetFPS(60);

        if (specs.fullscreen) {
            auto currentMonitor = GetCurrentMonitor();
            m_specs.width = GetMonitorWidth(currentMonitor);
            m_specs.height = GetMonitorHeight(currentMonitor);

            SetWindowSize(m_specs.width, m_specs.height);
            SetWindowPosition(0, 0);
            ToggleFullscreen();
        }
    }

    Application::~Application(){
        CloseWindow();

        s_app = nullptr;
    }

    void Application::Run(){
        m_sceneStack[m_currentSceneIndex]->Start();

        while (!WindowShouldClose()) {
            const float deltaTime = GetFrameTime();

            m_sceneStack[m_currentSceneIndex]->Update(deltaTime);

            BeginDrawing();
            ClearBackground({16, 15, 15});

            m_sceneStack[m_currentSceneIndex]->Draw();

            EndDrawing();
        }
    }

    void Application::SwitchScene(const int newIndex) {
        if (m_currentSceneIndex == newIndex) return;
        if (newIndex < 0) return;
        assert(newIndex <= m_sceneStack.size());

        m_sceneStack[m_currentSceneIndex]->Stop();
        m_currentSceneIndex = newIndex;
        m_sceneStack[m_currentSceneIndex]->Start();
    }

    int Application::GetCurrentSceneIndex() const {
        return m_currentSceneIndex;
    }

    const settings::Specs* Application::GetAppSpecs() const {
        return &m_specs;
    }

    Application& Application::Get() {
        assert(s_app);
        return *s_app;
    }

}