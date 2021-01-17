AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client,
               AwsEventType type, void *arg, uint8_t *data, size_t len) {
    if (type == WS_EVT_CONNECT) {
        Serial.println("Websocket client connection received");
        client->text("Hello from ESP32 Server");

    } else if (type == WS_EVT_DISCONNECT) {
        Serial.println("Client disconnected");
    } else if (type == WS_EVT_DATA) {
        // Serial.println("Data received: ");
        // for (int i = 0; i < len; i++) {
        //     Serial.print(data[i]);
        //     Serial.print("|");
        // }
        if (data[0] == ':') {
            handleMidi(data[2], data[3], data[4]);
        }
    }
}

void handleNotFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}

void setupServer() {
    ws.onEvent(onWsEvent);
    server.addHandler(&ws);

    server.onNotFound(handleNotFound);

    server.begin();
}
