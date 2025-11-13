#include "Application.h"

#include "Scenes/CharacterSelection.h"
#include "Scenes/MainMenu.h"
#include "Scenes/GameScene.h"

int main() {
    ark::settings::Specs specs {
        .fullscreen = false,
        .width = 800,
        .height = 800,
        .title = "Arkade spil"
    };

    ark::Application app(specs);

    app.PushScene<ark::scene::MainMenu>();
    app.PushScene<ark::scene::CharacterSelection>();
    app.PushScene<ark::scene::GameScene>();

    app.Run();
}
