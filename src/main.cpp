#include <Arduino.h>
#include <WebServer.h>
#include "esp_camera.h"


#define LED 4
const char* ssid = "Glide_Resident";
const char* password = "BringFlintPhoto";
// Create a web server on port 80
WebServer server(80);

String ledStatus = "OFF";


void handleRoot() {
  String html = "<html><head><title>ESP32 LED Status</title></head><body>";
  html += "<h1>LED Status: " + ledStatus + "</h1>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  delay(2000); // Give time for Serial to initialize
  Serial.println("Start of setup");

  pinMode(LED, OUTPUT);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  int attempt = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    attempt++;
    if (attempt > 20) {  // Timeout after ~10 seconds
      Serial.println("\nFailed to connect to WiFi.");
      return;
    }
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());

  // Setup web server
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
}
void loop() {
  digitalWrite(LED, HIGH);
  ledStatus = "ON";
  Serial.println("LED is on");
  delay(1000);

  digitalWrite(LED, LOW);
  ledStatus = "OFF";
  Serial.println("LED is off");
  delay(1000);

  server.handleClient();
}