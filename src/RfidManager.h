#ifndef ARKADE_RFIDMANAGER_H
#define ARKADE_RFIDMANAGER_H

#include <functional>
#include <memory>

#include "simple-serial-port/SimpleSerial.h"

namespace ark {
    class RfidManager {
    public:
        RfidManager();
        ~RfidManager() = default;

        void Update();

    private:
        std::unique_ptr<SimpleSerial, std::function<void(SimpleSerial*)>> m_simpleSerial{};

        bool m_connected{false};
    };
}

#endif //ARKADE_RFIDMANAGER_H