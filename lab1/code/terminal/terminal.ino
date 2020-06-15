#include <SoftwareSerial.h>

#include <Wire.h>

#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>

Adafruit_8x16matrix matrix = Adafruit_8x16matrix();
    
void setup() {
  // pass in the address
  matrix.begin(0x70);
  matrix.setRotation(1);
  Serial.begin(9600);
  Serial.println("Type something!");
}
 
 
void loop() {     
  if(Serial.available()) {
    char input = Serial.read();
    matrix.clear();
    matrix.setTextColor(LED_ON);
    matrix.setCursor(0,0);
    matrix.print(input);
    matrix.writeDisplay();
  } 
}      
