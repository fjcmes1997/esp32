#include <Wire.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <Adafruit_AMG88xx.h>
#include "functions.h"


const char* API_URL = "http://ejemplo.com/api/lecturas";
const char* API_KEY = "tu_clave_api";

void setup() {
  Serial.begin(9600);
  // Create a wireless access point
  activate_access_point();
  // Active the servos
  init_servos();
  // Check if thermal sensor is active
  //check_amg8833();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED && get_memory_ssid() != "" && check_if_client_connected() == false) {
    connect_wifi();
    delay(1000);
  }
  
  //float* pixels = read_pixels();
  //for (int i=0; i<64; i++) {
    //Serial.print(pixels[i]);
    //Serial.print(" ");
  //}
  //Serial.println();
}
