#include <ESP32Servo.h>


Servo servo1;
Servo servo2;

void init_servos() {
  servo1.attach(4);
  servo2.attach(2);
}

void move_servo(int servo_id, int angle) {
  if (servo_id == 1) {
    servo1.write(angle);
  } else if (servo_id == 2) {
    servo2.write(angle);
  }
}