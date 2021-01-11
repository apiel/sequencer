#include "index.html.h"
#include "index.js.h"

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client,
               AwsEventType type, void *arg, uint8_t *data, size_t len) {
    if (type == WS_EVT_CONNECT) {
        Serial.println("Websocket client connection received");
        client->text("Hello from ESP32 Server");

    } else if (type == WS_EVT_DISCONNECT) {
        Serial.println("Client disconnected");
    }
}

void handleIndexHtml(AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", (const uint8_t *)index_html, index_html_len);
}

void handleIndexJs(AsyncWebServerRequest *request) {
    request->send_P(200, "text/js", (const uint8_t *)index_js, index_js_len);
}

void handleNotFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}

void setupServer() {
    ws.onEvent(onWsEvent);
    server.addHandler(&ws);

    server.on("/", HTTP_GET, handleIndexHtml);
    server.on("/index.js", HTTP_GET, handleIndexJs);
    server.onNotFound(handleNotFound);

    server.begin();
}
