#include "../include/utils.hpp"
#include <sstream>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <ctime>

std::string getCurrentTimestamp() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&now_time);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

std::pair<std::string, std::string> parseRegister(const std::string& input) {
    std::istringstream iss(input);
    std::string cmd, user, pass;
    iss >> cmd >> user >> pass;
    return {user, pass};
}

std::pair<std::string, std::string> parseLogin(const std::string& input) {
    std::istringstream iss(input);
    std::string cmd, user, pass;
    iss >> cmd >> user >> pass;
    return {user, pass};
}

void help() {
    system("clear");
    std::cout << "Comandos disponíveis:\n";
    std::cout << "/register <username> <password> - Registrar um novo usuário\n";
    std::cout << "/login <username> <password>    - Fazer login\n";
    std::cout << "/join <room_name>               - Entrar em uma sala de chat (padrão: global)\n";
    std::cout << "/exit                           - Sair do chat\n";
    std::cout << "Qualquer outra mensagem será enviada para a sala atual.\n";
}