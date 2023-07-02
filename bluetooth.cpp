#include <BluetoothSerial.h>
#include "functions.h"


BluetoothSerial SerialBT;

void activate_bluetooth() {
  SerialBT.begin("ESP32-" + String((uint32_t)ESP.getEfuseMac() & 0xFFFF, HEX));
  Serial.println("Bluetooth started");
}

void disable_bluetooth() {
  SerialBT.end();
  ESP.restart();
}

bool check_bluetooth_activated() {
  return SerialBT.hasClient();
}

void read_message_bluetooth() {
  String bt_message = "";
  while (true) {
    if (SerialBT.available()) {
      if (check_credentials_exist() == true) {
          Serial.println("exiting...");
          break;
      }
      char incomingChar = SerialBT.read();
      Serial.print(incomingChar);
      if (incomingChar != '\n') {
        bt_message += String(incomingChar);
      } else {
        process_message_bluetooth(bt_message);
        bt_message = "";
      }
    } 
  }
}

void send_not_connected_bluetooth() {
  if (SerialBT.available()) {
    SerialBT.println("Could not connect to the Wi-Fi");
  } else {
    Serial.println("Bluetooth not available");
  }
}
