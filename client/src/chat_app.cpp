#include "../include/chat_app.hpp"
#include "../include/utils.hpp"
#include "../include/mqtt_client.hpp"
#include <iostream>
#include <cstdlib>
#include <memory>

void ChatApp::run() {
    std::string input;
    std::unique_ptr<MqttClient> client = nullptr;
    std::string currentTopic = "chat/global";

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);
        std::cout << "\33[1A\33[2K\r";  
        std::cout.flush();

        if (input.rfind("/register", 0) == 0) {
            // Exemplo: /register luiz senha123
            auto [user, pass] = parseRegister(input);
            std::string cmd = "mosquitto_passwd -b broker/users.db " + user + " " + pass;
            int ret = std::system(cmd.c_str());
            std::cout << (ret == 0 ? "✅ Usuário cadastrado!\n" : "❌ Erro ao cadastrar.\n");
        }
        else if (input.rfind("/login", 0) == 0) {
            auto [user, pass] = parseLogin(input);
            client = std::make_unique<MqttClient>("tcp://localhost:1883", user);
            if (client->connect(user, pass)) {
                system("clear");
                std::cout << "✅ Login bem-sucedido!\n";
                client->subscribe(currentTopic); // entra na sala global por padrão
            } else {
                std::cout << "❌ Erro de login.\n";
            }
        }
        else if (input.rfind("/join", 0) == 0) {
            if (client) {
                std::string topic = input.substr(6);
                if (topic.empty()) topic = "chat/global";
                currentTopic = "chat/" + topic;
                client->subscribe(currentTopic);
                system("clear");
                std::cout << "Entrou na sala: " << currentTopic << "\n";
            } else {
                std::cout << "⚠️ Você precisa estar logado primeiro.\n";
            }
        }
        else if (input == "/help") {
            help();
        }
        else if (input == "/exit") {
            if (client) {
                client->disconnect();
                client.reset();
            }
            std::cout << "👋 Saindo do chat...\n";
            break;
        }
        else {
            if (client) {
                client->publish(currentTopic, input);
            } else {
                std::cout << "⚠️ Você precisa estar logado para enviar mensagens.\n";
            }
        }
    }
}
