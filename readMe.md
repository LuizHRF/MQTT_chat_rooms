
# MQTT CHAT

Aplicação de bate-papo simples via terminal, utilizando o protocolo MQTT com o broker Mosquitto. 

Permite que múltiplos usuários conversem em salas (tópicos) diferentes, tudo rodando localmente.

## Funcionalidades

- Registro e login de usuários
- Envio e recebimento de mensagens em tempo real
- Criação e entrada em salas de chat (tópicos MQTT)
- Comandos básicos via terminal

## Requisitos

- **Mosquitto** (broker MQTT) instalado e rodando localmente
- **Biblioteca Paho MQTT C++** (`libpaho-mqttpp3`, `libpaho-mqtt3as`) [Disponível aqui](https://github.com/eclipse-paho/paho.mqtt.cpp)
- **g++** (compilador C++)

## Instalação das dependências

No Ubuntu/Debian, execute:

```bash
sudo apt update
sudo apt install mosquitto libpaho-mqttpp3-dev libpaho-mqtt3as-dev g++
```

## Como compilar

Execute o comando abaixo na raiz do projeto:

```bash
g++ client/src/*.cpp -o chat_app.exe -lpaho-mqttpp3 -lpaho-mqtt3as -lpthread
```

## Como executar

1. Inicie o broker Mosquitto localmente:
    ```bash
    mosquitto -c broker/mosquitto.conf
    ```
2. Execute o aplicativo de chat (em diferentes terminais):
    ```bash
    ./chat_app
    ```

## Comandos disponíveis

- `/register <usuario> <senha>` — Registrar novo usuário
- `/login <usuario> <senha>` — Fazer login
- `/join <sala>` — Entrar em uma sala de chat (padrão: global)
- `/exit` — Sair do chat
- Qualquer outra mensagem será enviada para a sala atual

## Observações

- O cadastro de usuários é feito localmente no arquivo `broker/users.db`.
- As mensagens são trocadas via tópicos MQTT, cada sala corresponde a um tópico.
- O aplicativo é apenas para fins de estudo/demonstração.

---