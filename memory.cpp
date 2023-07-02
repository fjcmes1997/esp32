#include <Preferences.h>


Preferences preferences;

String get_memory_ssid() {
  preferences.begin("esp32", false);
  String ssid = preferences.getString("ssid", "");
  return ssid;
}

String get_memory_password() {
  preferences.begin("esp32", false);
  String password = preferences.getString("password", "");
  return password;
}

bool check_credentials_exist() {
  preferences.begin("esp32", false);
  String ssid = preferences.getString("ssid", "");
  if (ssid == "" || ssid == NULL) {
    return false;
  } else {
    return true;
  }
}

void store_ssid(String ssid) {
  preferences.begin("esp32", false);
  preferences.putString("ssid", ssid);
}

void store_password(String password) {
  preferences.begin("esp32", false);
  preferences.putString("password", password);
}

void delete_credentials() {
  preferences.clear();
}
