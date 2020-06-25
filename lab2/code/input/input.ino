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
      mySerial.println("Invalid command!");
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

void sendCommand(char cmd) {
 byte enc = encodeCommand(cmd);
 byte encArr[] = {enc};
 byte crc = CRC8(encArr, 1);
 byte data[] = {enc, crc};
 Wire.beginTransmission(9); // transmit to device #9
 Wire.write(data, 2);
 Wire.endTransmission(); 
}
