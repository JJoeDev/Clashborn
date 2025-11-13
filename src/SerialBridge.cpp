#include "SerialBridge.h"

#include <iostream>
#include <queue>
#include <thread>

#include "simple-serial-port/SimpleSerial.h"

struct SerialContext {
    SimpleSerial serial;
    std::thread readThread;
    std::mutex queueMutex;
    std::queue<std::string> messageQueue;
    std::atomic<bool> running;

    SerialContext(const char* comPort, unsigned long cbr) : serial(comPort, cbr), running(false){}
    ~SerialContext() {
        Stop();
    }

    void Start() {
        if (!serial.IsConnected()) {
            std::cerr << "COULD NOT CONNECT SERIAL PORT\n";
            return;
        }

        running = true;

        readThread = std::thread([this]() {
            while (running) {
                std::cout << "SERIAL LOOP\n";
                std::string msg = serial.ReadSerialPort(1, "json");
                if (!msg.empty()) {
                    std::lock_guard<std::mutex> lock(queueMutex);
                    messageQueue.push(std::move(msg));
                }

                std::this_thread::sleep_for(std::chrono::milliseconds(30));
            }
        });
    }

    void Stop() {
        running = false;
        if (readThread.joinable()) readThread.join();
        serial.CloseSerialPort();
    }

    bool GetMessage(std::string& outMsg) {
        std::lock_guard<std::mutex> lock(queueMutex);
        if (messageQueue.empty()) return false;
        outMsg = std::move(messageQueue.front());
        messageQueue.pop();
        return true;
    }

    [[nodiscard]] bool IsConnected() const {
        return serial.IsConnected();
    }
};

static SerialContext* ToContext(void* ctx) {
    return static_cast<SerialContext*>(ctx);
}

namespace ark {
    void* OpenSerialPort() {
        std::cout << "CONNECTING TO SERIAL PORT\n";
        auto* ctx = new SerialContext(R"(\\.\COM8)", CBR_9600);
        if (ctx->IsConnected()) {
            std::cout << "SERIAL CONNECTED!\n";
            ctx->Start();
            return ctx;
        }

        std::cout << "SERIAL FAILED CONNECTION!\n";
        delete ctx;
        return nullptr;
    }

    void CloseSerialPort(void* ctx) {
        if (!ctx) return;
        ToContext(ctx)->Stop();
        delete ToContext(ctx);
        std::cout << "SERIAL CONNECTION CLOSED\n";
    }

    std::string GetArduinoSerialMessage(void* ctx) {
        if (!ctx) return "";

        std::string msg;
        if (ToContext(ctx)->GetMessage(msg)) {
            std::cout << "SERIAL MESSAGE: " << msg << '\n';
            return msg;
        }

        std::cout << "NO NEW MESSAGE\n";

        return "";
    }

    bool IsSerialConnected(void* ctx) {
        if (!ctx) return false;
        return ToContext(ctx)->IsConnected();
    }

}
