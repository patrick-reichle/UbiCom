#include <Wire.h>
#include <SoftwareSerial.h>

// only for debugging purpose
SoftwareSerial mySerial(0,1);
int red_light_pin= 9;
int green_light_pin = 10;
int blue_light_pin = 11;
char command;


void setup() {
  Wire.begin(9);
  Wire.onReceive(receiveCommand);
  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);
  mySerial.begin(9600);
  mySerial.println("Debugging Terminal");
}

void loop() {
  if (command == 'y') {
    RGB_color(255, 255, 0); // Yellow
    delay(1000);
  } else if (command == 'v') {
    RGB_color(148, 0, 211); // Violet
    delay(1000);
  } else if (command == 'w') {
    RGB_color(255, 255, 255); // White
    delay(1000);
  } else if (command == 'b') {
    RGB_rainbow();
    // no delay, function long enough
  } else if (command == 'o') {
    RGB_color(0, 0, 0); // off
    delay(1000);
    // delay could be omitted for higher response
  }
}

// gets called when data is received
void receiveCommand(int bytes) {
  byte enc = Wire.read();
  byte crc = Wire.read();
  byte check[] = {enc,crc};
  byte res = CRC8(check,2);
  if (res != 0) {
    mySerial.println("Received corrupted command!");
  } else {
    mySerial.println("Package valid!");
    mySerial.println("Encoded command received:");
    mySerial.println(enc, BIN);
    mySerial.println("Received Checksum:");
    mySerial.println(crc, BIN);
    
    // decoding section
    if (enc == B00000001) {
      command = 'y'; // Yellow
    } else if (enc == B00000011) {
      command = 'v'; // Violet
    } else if (enc == B00000111) {
      command = 'w'; // White
    } else if (enc == B00001111) {
      command = 'b';
    } else if (enc == B00011111) {
      command = 'o'; // off
    }
  }
}


byte CRC8(byte* bytes, int len) {
  const byte generator = 0x07;
  byte crc = 0; /* start with 0 so first byte can be 'xored' in */

  for (int j = 0; j < len; j++) {
    crc ^= bytes[j]; /* XOR-in the next input byte */

    for (int i = 0; i < 8; i++) {
      if ((crc & 0x80) != 0) {
        crc = (byte)((crc << 1) ^ generator);
      }
      else {
        crc <<= 1;
      }
    }
  }
  return crc;
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
