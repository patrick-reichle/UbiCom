#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>

Adafruit_8x16matrix matrix = Adafruit_8x16matrix();

static const uint8_t PROGMEM
  smile_bmp[] =
  { B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10100101,
    B10011001,
    B01000010,
    B00111100 },
  neutral_bmp[] =
  { B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10111101,
    B10000001,
    B01000010,
    B00111100 },
  frown_bmp[] =
  { B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10011001,
    B10100101,
    B01000010,
    B00111100 };
    
bool smile;
void setup() {
  // put your setup code here, to run once:
  pinMode(4, INPUT_PULLUP); 
  matrix.begin(0x70);
  matrix.setRotation(1);
  matrix.drawBitmap(0, 0, smile_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
  smile = true;
}
void loop() {
  // put your main code here, to run repeatedly:  matrix.clear();
  if (digitalRead(4)==LOW) {
    smile = !smile;
    matrix.clear();
    if (smile) {
      matrix.drawBitmap(0, 0, smile_bmp, 8, 8, LED_ON);
  
    } else {
      matrix.drawBitmap(0, 0, frown_bmp, 8, 8, LED_ON);
    }
    matrix.writeDisplay();
    delay(500);
  }
}
