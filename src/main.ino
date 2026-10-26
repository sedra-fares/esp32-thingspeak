/*
 * ESP32 -> ThingSpeak (DHT22)
 * Name: Sidra Faris
 * University ID: 12325061
 * DHT22 DATA pin: GPIO 15
 */

#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"

#define DHTPIN 15
#define DHTTYPE DHT22

const char* ssid = "Wokwi-GUEST";
const char* password = "";

// Replace with your ThingSpeak Write API Key (never commit the real one)
const char* apiKey = "YOUR_WRITE_API_KEY";
const char* serverName = "http://api.thingspeak.com/update";
const char* universityID = "12325061";

DHT dht(DHTPIN, DHTTYPE);

unsigned long lastSend = 0;
const unsigned long interval = 20000;  // 20 seconds (ThingSpeak minimum is 15 s)

void setup() {
  Serial.begin(115200);
  dht.begin();

  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password, 6);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (millis() - lastSend >= interval || lastSend == 0) {
    lastSend = millis();

    float temp = dht.readTemperature();
    float hum = dht.readHumidity();

    if (isnan(temp) || isnan(hum)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }

    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      String url = String(serverName) + "?api_key=" + apiKey +
                   "&field1=" + String(temp, 1) +
                   "&field2=" + String(hum, 1);
      http.begin(url);
      int code = http.GET();
      String response = http.getString();

      Serial.printf("[ID: %s] Temp: %.1f C | Hum: %.1f %% | HTTP: %d | Entry: %s\n",
                    universityID, temp, hum, code, response.c_str());
      http.end();
    } else {
      Serial.println("WiFi disconnected");
    }
  }
}
