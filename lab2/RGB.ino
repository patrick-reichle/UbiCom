#include <SoftwareSerial.h>

SoftwareSerial mySerial(1, 0);
int red_light_pin= 9;
int green_light_pin = 10;
int blue_light_pin = 11;

void setup() {
  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);
  mySerial.begin(9600);
  mySerial.println("Enter y:yellow, v:violet, w:white, b:rainbow blink, o:off");
}
void loop() {
  if (mySerial.available()) {
    char inChar = mySerial.read();
    if (inChar == 'y') {
      RGB_color(255, 255, 0); // Yellow
    } else if (inChar == 'v') {
      RGB_color(148, 0, 211); // Violet
    } else if (inChar == 'w') {
      RGB_color(255, 255, 255); // White
    } else if (inChar == 'b') {
      RGB_rainbow();
    } else if (inChar == 'o') {
      RGB_color(0, 0, 0); // off
    } else {
      mySerial.println();
      mySerial.println("Wrong command!");
    }
    
    mySerial.println("Enter new command: ");
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
