#include "RfidManager.h"

#include <iostream>

namespace ark {
    RfidManager::RfidManager() {
        m_simpleSerial = std::unique_ptr<SimpleSerial, std::function<void(SimpleSerial*)>>(
            new SimpleSerial(R"(\\\\.\\COM8)", CBR_9600),
            [](SimpleSerial* ptr) {
                ptr->CloseSerialPort();
                delete ptr;
            }
        );

        m_connected = m_simpleSerial->IsConnected();
    }

    void RfidManager::Update() {
        std::string read = m_simpleSerial->ReadSerialPort(10, "json");
        std::cout << "ARDUINO SERIAL: " << read << '\n';
    }
}
