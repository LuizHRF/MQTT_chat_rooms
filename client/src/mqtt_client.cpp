#include "../include/mqtt_client.hpp"
#include "../include/utils.hpp"

MqttClient::MqttClient(const std::string& server, const std::string& username)
    : serverAddress(server), username_(username), client(server, username)
{
    connOpts.set_clean_session(false);
    client.set_callback(cb);
}


bool MqttClient::connect(const std::string& user, const std::string& pass) {
    try {
        connOpts.set_user_name(user);
        connOpts.set_password(pass);

        std::cout << "Conectando ao broker em " << serverAddress << "..." << std::endl;
        auto tok = client.connect(connOpts);
        tok->wait();
        std::cout << "✅ Conectado com sucesso!" << std::endl;
        return true;
    }
    catch (const mqtt::exception& exc) {
        std::cerr << "❌ Erro ao conectar: " << exc.what() << std::endl;
        return false;
    }
}

bool MqttClient::publish(const std::string& topic, const std::string& message, int qos) {
    try {
        nlohmann::json msg;
        msg["sender"] = username_;
        msg["timestamp"] = getCurrentTimestamp();
        msg["text"] = message;

        auto payload = msg.dump();  // serializa para string
        mqtt::message_ptr pubmsg = mqtt::make_message(topic, payload);
        pubmsg->set_qos(qos);
        client.publish(pubmsg);
        return true;
    }
    catch (const mqtt::exception& exc) {
        std::cerr << "❌ Erro ao publicar: " << exc.what() << std::endl;
        return false;
    }
}

bool MqttClient::subscribe(const std::string& topic, int qos) {
    try {
        client.subscribe(topic, qos)->wait();
        std::cout << "Inscrito no tópico: " << topic << std::endl;
        return true;
    }
    catch (const mqtt::exception& exc) {
        std::cerr << "❌ Erro ao inscrever-se: " << exc.what() << std::endl;
        return false;
    }
}

void MqttClient::disconnect() {
    try {
        client.disconnect()->wait();
        std::cout << "🔌 Desconectado do broker." << std::endl;
    }
    catch (const mqtt::exception& exc) {
        std::cerr << "❌ Erro ao desconectar: " << exc.what() << std::endl;
    }
}
