#ifndef ARKADE_BASESCENE_H
#define ARKADE_BASESCENE_H

namespace ark::scene {
    class BaseScene {
    public:
        virtual ~BaseScene() = default;

        virtual void Start() = 0;
        virtual void Stop() = 0;

        virtual void Update(const float dt) = 0;
        virtual void Draw() const = 0;
    };
}

#endif //ARKADE_BASESCENE_H