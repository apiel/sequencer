#include <MyWifiSettings.h>
#include <WiFi.h>

#define MAX_RETRY_WIFI_CHECK 3

unsigned int retryWifiCheck = 0;
unsigned long lastWifiCheck = 0;
const unsigned long intervalWifiCheck = 60UL * 1000UL;  // 1min

void wifiDisconnected() {
    Serial.println("\nDisconnected from Wifi, try to reconnect...");
    wifiReConnect();
}

void wifiCheck() {
    if (!WiFi.isConnected()) {
        Serial.println("Wifi status disconnected (" + String(WiFi.status()) +
                       ")");
        // Serial.println(WiFi.localIP());
        wifiDisconnected();
    }
}

void wifiBegin() {
    Serial.println("Auto reconnect: " + String(WiFi.getAutoReconnect()));
    wifiConnect();
}

void wifiConnect() {
    Serial.println("Connect to wifi.");

    WiFi.disconnect();
    // WiFi.mode(WIFI_OFF);
    // WiFi.mode(WIFI_STA);
    WiFi.begin(MYWIFISSID, MYWIFIPASSWORD);
    if (!wifiWait()) {
        wifiConnect();
    }
}

void wifiReConnect() {
    Serial.println("ReConnect to wifi.");

    WiFi.reconnect();
    if (!wifiWait()) {
        wifiConnect();
    }
}

// could use WiFi.waitForConnectResult() instead
bool wifiWait() {
    // Wait for connection
    int attempt = 0;
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
        if (attempt++ > 100) {
            Serial.println("\nCould not connect to Wifi, reset.");
            return false;
        }
    }
    Serial.println("");
    Serial.print("Station connected, IP: ");
    Serial.println(WiFi.localIP());
    return true;
}