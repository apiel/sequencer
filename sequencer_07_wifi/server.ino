#include "index.html.h"

AsyncWebServer server(80);
// AsyncWebSocket ws("/ws");

// void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client,
//                AwsEventType type, void *arg, uint8_t *data, size_t len) {
//     if (type == WS_EVT_CONNECT) {
//         Serial.println("Websocket client connection received");
//         client->text("Hello from ESP32 Server");

//     } else if (type == WS_EVT_DISCONNECT) {
//         Serial.println("Client disconnected");
//     }
// }

void handleIndex(AsyncWebServerRequest *request) {
    request->send(200, "text/html", (const char*)index_html);
}

void handleNotFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}

void setupServer() {
    // ws.onEvent(onWsEvent);
    // server.addHandler(&ws);

    server.on("/", HTTP_GET, handleIndex);
    server.onNotFound(handleNotFound);

    server.begin();
}
