#ifndef CHAT_APP_HPP
#define CHAT_APP_HPP

#include <string>
#include <memory>

class MqttClient;

class ChatApp {
public:
    ChatApp() = default;
    void run();
};

#endif // CHAT_APP_HPP

