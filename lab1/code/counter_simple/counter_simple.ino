#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>

Adafruit_8x16matrix matrix = Adafruit_8x16matrix();
    
void setup() {
  // pass in the address
  matrix.begin(0x70);
}
 
int count = 0; 
void loop() {       
  for (int i = 0; i<= count; i++) {
    int x = i / 16;
    int y = i % 16;
    matrix.drawPixel(x,y, LED_ON);
    matrix.writeDisplay();
    delay(150);
    if (count < 128) {
      count++;
    } else {
      matrix.clear();
      count = 0;
    }
  }
} 
