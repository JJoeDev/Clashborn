#ifndef ARKADE_SPECIFICATIONS_H
#define ARKADE_SPECIFICATIONS_H

#include <string>

namespace ark::settings {
    struct Specs final {
        int width;
        int height;
        std::string title;
    };
}

#endif //ARKADE_SPECIFICATIONS_H