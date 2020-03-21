#include <Servo.h>
#include <math.h>

Servo servo_1; // servo controller (multiple can exist)

int servo_pin = 3; // PWM pin for servo control
int joy_pin_x = A0; // pin for x-dir joystick
int joy_pin_y = A1; // pin for y-dir joystick
int offset_x = 0; // subtracting the initial joystick x-location
int offset_y = 0; // subtracting the initial joystick y-location
int pos = 90;    // servo starting position aligned with joystick
int prev_deg = 0; // bound for reducing jitter
int x_prev = 0; // bound for reducing jitter
int y_prev = 0; // reducing jitter

void setup() {
  servo_1.attach(servo_pin); // start servo control
  Serial.begin(9600);
  servo_1.write(pos); // move to center (joystick neutral)
  Serial.println("Positioned at 90 Degrees");  
  offset_x = analogRead(joy_pin_x); // initial joystick x-val
  offset_y = analogRead(joy_pin_y); // initial joystick y-val
}

void loop() {
  int x_val = analogRead(joy_pin_x)-offset_x; // relative joystick x
  int y_val = analogRead(joy_pin_y)-offset_y; // relative joystick y
  if (abs(x_prev-x_val)<10 and abs(y_prev-y_val)<10){
    // reduce jitter
  } else {
    x_prev = x_val;
    y_prev = y_val;
    float deg = 180-(int(atan2(x_val,y_val)*(180.0/PI))+90); // angle calc
    if (abs(deg-prev_deg)>2 and deg>0 and deg<180){
      servo_1.write(deg); // move servo to joystick location
      delay(abs(deg-prev_deg)*(10.0/6.0));
      prev_deg = deg;
      Serial.println(deg); // print out degree
    }
  }
}
