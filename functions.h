void connect_wifi();
void disconnect_wifi();
void activate_access_point();
bool check_if_client_connected();

void activate_bluetooth();
void disable_bluetooth();
bool check_bluetooth_activated();
void read_message_bluetooth();
void send_not_connected_bluetooth();

void check_amg8833();
float* read_pixels();

void init_servos();
void move_servo(int servo_id, int angle);

String get_memory_ssid();
String get_memory_password();
void store_ssid(String ssid);
void store_password(String password);
bool check_credentials_exist();
void delete_credentials();
void process_message_bluetooth(String message);

String urlencode(String str);
String urldecode(String str);
