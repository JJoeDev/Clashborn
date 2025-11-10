#ifndef ARKADE_APPLICATION_H
#define ARKADE_APPLICATION_H

#include <memory>
#include <vector>

#include "Characters/Characters.h"
#include "Settings/Specifications.h"
#include "Scenes/BaseScene.h"

namespace ark {
    class Application final {
    public:
        explicit Application(const settings::Specs& specs);
        ~Application();

        void Run();

        template<typename TScene>
        requires(std::is_base_of_v<scene::BaseScene, TScene>)
        void PushScene() {
            m_sceneStack.push_back(std::make_unique<TScene>());
        }

        void SwitchScene(const int newIndex);
        [[nodiscard]] int GetCurrentSceneIndex() const;

        [[nodiscard]] const settings::Specs* GetAppSpecs() const;

        characters::CHARACTERS m_playerOne = characters::CHARACTERS::BigBuffChad;
        characters::CHARACTERS m_playerTwo = characters::CHARACTERS::BigBlueAlien;

        [[nodiscard]] static Application& Get();

    private:
        settings::Specs m_specs{};

        std::vector<std::unique_ptr<scene::BaseScene>> m_sceneStack{};
        int m_currentSceneIndex{0};
    };
}

#endif //ARKADE_APPLICATION_H