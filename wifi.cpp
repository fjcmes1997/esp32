#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebSrv.h>
#include <AsyncWebSocket.h>
#include "functions.h"


// PYUR 09CEB
// nAZ5b7zV7E3b

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

void connect_wifi() {
  String ssid = get_memory_ssid();
  Serial.print("Current ssid: ");
  Serial.println(ssid);
  String password = get_memory_password();
  Serial.print("Current password: ");
  Serial.println(password);
  Serial.print("Trying to connect to ");
  Serial.print(ssid);
  WiFi.begin(ssid.c_str(), password.c_str());
  int counter = 0;
  while (WiFi.status() != WL_CONNECTED && counter < 10) {
    Serial.print(".");
    counter += 1;
    delay(1000);
  }
  Serial.println("");
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Could not connect to the Wi-Fi.");
  } else {
    Serial.print("Connected to ");
    Serial.println(ssid);
  }
}

void handleRoot(AsyncWebServerRequest *request) {
  bool connected = false;
  String ssid = get_memory_ssid();
  String password = get_memory_password();
  if (WiFi.status() == WL_CONNECTED) {
    connected = true;
  }
  request->send(200, "text/plain", "Connected: " + String(connected) + "\n" + "SSID: " + ssid + "\n" + "Password: " + password);
}

void handleSave(AsyncWebServerRequest *request) {
  if (request->hasParam("ssid") && request->hasParam("password")) {
    String raw_ssid = request->getParam("ssid")->value();
    String raw_password = request->getParam("password")->value();
    String ssid = urldecode(raw_ssid);
    String password = urldecode(raw_password);
    store_ssid(ssid);
    store_password(password);
    request->send(200, "text/plain", "Credentials saved");
  } else {
    request->send(400, "text/plain", "Invalid request, missing parameters");
  }
}

void handleServo(AsyncWebServerRequest *request) {
  if (request->hasParam("id") && request->hasParam("angle")) {
    String servo_id = request->getParam("id")->value();
    String angle = request->getParam("angle")->value();
    move_servo(servo_id.toInt(), angle.toInt());
    request->send(200, "text/plain", "Servo moved.");
  } else {
    request->send(400, "text/plain", "Invalid request, missing parameters");
  }
}

void handleDelete(AsyncWebServerRequest *request) {
  delete_credentials();
  request->send(200, "text/plain", "Credentials deleted");
}

void handleRestart(AsyncWebServerRequest *request) {
  ESP.restart();
}

void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
  if(type == WS_EVT_DISCONNECT) {
    Serial.println("WebSocket client disconnected");
    ESP.restart();
  }
}

void activate_access_point() {
  String mac = WiFi.macAddress();
  String name_ap = "ESP32-" + mac.substring(12);
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP(name_ap.c_str(), "11131719");
  IPAddress IP(10, 10, 254, 1);
  IPAddress subnet(255, 255, 255, 0);
  WiFi.softAPConfig(IP, IP, subnet);
  server.on("/", HTTP_GET, handleRoot);
  server.on("/save", HTTP_GET, handleSave);
  server.on("/delete", HTTP_GET, handleDelete);
  server.on("/servo", HTTP_GET, handleServo);
  server.on("/restart", HTTP_GET, handleRestart);
  ws.onEvent(onWsEvent);
  server.addHandler(&ws);
  server.begin();
  Serial.println("Server is now active");
}

bool check_if_client_connected() {
  if (WiFi.softAPgetStationNum() > 0) {
    server.begin();
    return true;
  } else {
    return false;
  }
}