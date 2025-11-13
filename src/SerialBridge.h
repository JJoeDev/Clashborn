#ifndef ARKADE_RFIDMANAGER_H
#define ARKADE_RFIDMANAGER_H

#include <string>

namespace ark {
    void* OpenSerialPort();
    void CloseSerialPort(void* ctx);
    std::string GetArduinoSerialMessage(void* ctx);
    bool IsSerialConnected(void* ctx);
}

#endif //ARKADE_RFIDMANAGER_H