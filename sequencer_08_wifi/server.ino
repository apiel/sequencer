#include "index.html.h"
#include "index.js.h"

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

byte c2nb(char c) { return c - 97; }
byte b2nb(char c) { return c - 48; }

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
            byte key = getKeyFromData(data);
            int val = getValFromData(data);
            callFn(key, val, false);
        } else if (data[0] == '$') {
            byte optionKey = getKeyFromData(data);
            byte note = getNoteFromData(data);
            int val = getValFromData(data);
            setNoteOption(note, optionKey, val);
        } else if (data[0] == '%') {
            byte step = getKeyFromData(data);
            int val = getValFromData(data);
            setStepPattern(step, val);
        } else if (data[0] == ':') {
            Serial.print("midi msg: ");
            Serial.print(data[2]);
            Serial.print(',');
            Serial.print(data[3]);
            Serial.print(',');
            Serial.println(data[4]);
        }
    }
}

byte getKeyFromData(uint8_t *data) {
    return b2nb(data[1]) * 10 + b2nb(data[2]);
}

int getValFromData(uint8_t *data) {
    int sign = data[3] == '-' ? -1 : 1;
    return sign * (b2nb(data[4]) * 1000 + b2nb(data[5]) * 100 +
                   b2nb(data[6]) * 10 + b2nb(data[7]));
}

byte getNoteFromData(uint8_t *data) { return c2nb(data[8]); }

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
