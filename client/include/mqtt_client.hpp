#pragma once
#include "mqtt/async_client.h"
#include <string>
#include <memory>
#include <iostream>
#include <nlohmann/json.hpp>

// Classe de callback personalizada para lidar com eventos MQTT
class ChatCallback : public virtual mqtt::callback
{
public:
    void connected(const std::string& cause) override {
        std::cout << "Conectado ao broker. " << cause << std::endl;
    }

    void connection_lost(const std::string& cause) override {
        std::cout << "⚠️ Conexão perdida. Causa: " << cause << std::endl;
    }

    void message_arrived(mqtt::const_message_ptr msg) override {
        try {
            auto j = nlohmann::json::parse(msg->get_payload());

            std::string sender = j.value("sender", "unknown");
            std::string time   = j.value("timestamp", "unknown");
            std::string text   = j.value("text", msg->get_payload());

            std::cout << "[" << time << "] " << sender << ": " << text << std::endl;
        }
        catch (...) {
            // fallback se não for JSON
            std::cout << msg->get_payload() << std::endl;
       }
    }

    void delivery_complete(mqtt::delivery_token_ptr token) override {
    }
};

class MqttClient {
private:
    std::string serverAddress;
    std::string clientId;
    std::string username_;
    mqtt::async_client client;
    mqtt::connect_options connOpts;
    ChatCallback cb;

public:
    MqttClient(const std::string& server, const std::string& username);

    bool connect(const std::string& user, const std::string& pass);
    bool publish(const std::string& topic, const std::string& message, int qos = 1);
    bool subscribe(const std::string& topic, int qos = 1);
    void disconnect();
};
