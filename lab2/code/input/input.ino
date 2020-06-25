#include <Wire.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(1, 0);


void setup() {
  Wire.begin();
  mySerial.begin(9600);
  mySerial.println("Enter y:yellow, v:violet, w:white, b:rainbow blink, o:off");
}
void loop() {
  if (mySerial.available()) {
    char inChar = mySerial.read();
    if (inChar == 'y') {
      sendCommand('y');
    } else if (inChar == 'v') {
      sendCommand('v');
    } else if (inChar == 'w') {
      sendCommand('w');
    } else if (inChar == 'b') {
      sendCommand('b');
    } else if (inChar == 'o') {
      sendCommand('o');
    } else {
      mySerial.println("Wrong command!");
    }
    
    mySerial.println("Enter new command: ");
  }
}




byte encodeCommand(char cmd) {
  if (cmd == 'y') {
    return B00000001;
  } else if (cmd == 'v'){
    return B00000011;
  } else if (cmd == 'w'){
    return B00000111;
  } else if (cmd == 'b'){
    return B00001111;
  } else if (cmd == 'o'){
    return B00011111;
  }
  return B00000000;
}

byte CRC8(const byte *data, byte len) {
  byte crc = 0x00;
  while (len--) {
    byte extract = *data++;
    for (byte tempI = 8; tempI; tempI--) {
      byte sum = (crc ^ extract) & 0x01;
      crc >>= 1;
      if (sum) {
        crc ^= 0x8C;
      }
      extract >>= 1;
    }
  }
  return crc;
}

void sendCommand(char cmd) {
 byte enc = encodeCommand(cmd);
 mySerial.println(enc, BIN);
 byte crc = CRC8(enc,1);
 mySerial.println(crc, BIN);
 Wire.beginTransmission(9); // transmit to device #9
 Wire.write(enc);
 Wire.endTransmission(); 
}
