#ifndef ARKADE_GAMESCENE_H
#define ARKADE_GAMESCENE_H

#include "BaseScene.h"
#include "EntityManager.h"

namespace ark::scene {
    class GameScene final : public BaseScene {
    public:
        GameScene() = default;
        ~GameScene() override = default;

        void Start() override;
        void Stop() override;

        void Update(const float dt) override;
        void Draw() const override;

    private:
        EntityManager m_entityManager;
    };
}

#endif //ARKADE_GAMESCENE_H