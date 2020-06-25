#include <Wire.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(0,1);

int red_light_pin= 9;
int green_light_pin = 10;
int blue_light_pin = 11;


void setup() {
  Wire.begin(9);
  Wire.onReceive(receiveCommand);
  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);
  mySerial.begin(9600);
  mySerial.println("Welcome");
}

void loop() {
}

void receiveCommand(int bytes) {
  char inChar = Wire.read();
  mySerial.println(inChar, BIN);
  if (inChar == B00000001) {
    RGB_color(255, 255, 0); // Yellow
  } else if (inChar == B00000011) {
    RGB_color(148, 0, 211); // Violet
  } else if (inChar == B00000111) {
    RGB_color(255, 255, 255); // White
  } else if (inChar == B00001111) {
    RGB_rainbow();
  } else if (inChar == B00011111) {
    RGB_color(0, 0, 0); // off
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
  RGB_color(0, 0, 0); // off
}
