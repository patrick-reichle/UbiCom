#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>

Adafruit_8x16matrix matrix = Adafruit_8x16matrix();
    
void setup() {
  // pass in the address
  matrix.begin(0x70);
  matrix.setTextColor(LED_ON);
  matrix.setTextSize(1);
  matrix.setRotation(1);
}
 
int count = 0; 
void loop() {
  matrix.clear();
  matrix.setCursor(0,0);       
  matrix.print(count);
  matrix.writeDisplay();
  delay(150);
  if (count < 128) {
    count++;
  } else {
    count = 0;
  }
} 
