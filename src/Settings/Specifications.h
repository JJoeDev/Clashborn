#ifndef ARKADE_SPECIFICATIONS_H
#define ARKADE_SPECIFICATIONS_H

#include <string>

namespace ark::settings {
    struct Specs final {
        bool fullscreen{false}; // Override width and height params for windowed full screen
        int width;
        int height;
        std::string title;
    };
}

#endif //ARKADE_SPECIFICATIONS_H