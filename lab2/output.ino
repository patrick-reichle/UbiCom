#include <Wire.h>

int red_light_pin= 9;
int green_light_pin = 10;
int blue_light_pin = 11;
char inChar;


void setup() {
  Wire.begin(9);
  Wire.onReceive(receiveCommand);
  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);
}

void receiveCommand(int bytes) {
  inChar = Wire.read();
}

void loop() {
  if (inChar == 'y') {
    RGB_color(255, 255, 0); // Yellow
    delay(1000);
  } else if (inChar == 'v') {
    RGB_color(148, 0, 211); // Violet
    delay(1000);
  } else if (inChar == 'w') {
    RGB_color(255, 255, 255); // White
    delay(1000);
  } else if (inChar == 'b') {
    RGB_rainbow();
    // no delay, function long enough
  } else if (inChar == 'o') {
    RGB_color(0, 0, 0); // off
    delay(1000);
    // delay could be omitted for higher response
  }
}

void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  analogWrite(red_light_pin, red_light_value);
  analogWrite(green_light_pin, green_light_value);
  analogWrite(blue_light_pin, blue_light_value);
}

void RGB_rainbow() {
  RGB_color(255, 0, 0); // Red
  delay(500);
  RGB_color(255, 127, 0); // Orange
  delay(500);
  RGB_color(255, 255, 0); // Yellow
  delay(500);
  RGB_color(0, 255, 0); // Green
  delay(500);
  RGB_color(0, 0, 255); // Blue
  delay(500);
  RGB_color(75, 0, 130); // Indigo
  delay(500);
  RGB_color(148, 0, 211); // Violet
  delay(500);
  // RGB_color(0, 0, 0); // off
  // delay(500);
}
