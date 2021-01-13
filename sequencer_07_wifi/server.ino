#include "index.html.h"
#include "index.js.h"

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

byte c2nb(char c) { return c - 48; }

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
        if (data[0] == '#') {
            byte key = c2nb(data[1]) * 10 + c2nb(data[2]);
            int sign = data[3] == '-' ? -1 : 1;
            int val = sign * (c2nb(data[4]) * 1000 + c2nb(data[5]) * 100 +
                              c2nb(data[6]) * 10 + c2nb(data[7]));

            Serial.print("ws key: ");
            Serial.print(key);
            Serial.print(" val: ");
            Serial.print(val);
            Serial.println();

            callFn(key, val);
        }
    }
}

void handleIndexHtml(AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", (const uint8_t *)index_html,
                    index_html_len);
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
