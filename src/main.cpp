#include <VirtualWire.h>
#include <RH_ASK.h>
#include <SPI.h>
#include <i2c_t3.h>

const uint_fast8_t receive_pin = 12;
const byte authByteStart = 117;
const byte authByteEnd = 115;

RH_ASK driver(2000, receive_pin);

void setup() {
  while(!Serial && millis() < 10000);
  Serial.println("setup");


  // Initialise radiohead
  if (!driver.init()) {
    Serial.println("init failed");
  }

  Wire.begin(); // join i2c bus (address optional for master)
}

uint_fast8_t lastMessageID = 255;

void loop() {
  uint8_t buf[20];
  uint8_t buflen = sizeof(buf);

  if (driver.recv(buf, &buflen)) {
    if ((buf[0] != authByteStart) || (buf[buflen - 1] != authByteEnd)) {
      Serial.println("bad message");
      return;
    }

    uint_fast8_t messageID = buf[1];

    if (messageID == lastMessageID) {
      return;
    }

    lastMessageID = messageID;

    Wire.beginTransmission(4); // transmit to device #4

    // skip the auth & messageID bytes
    for (uint8_t i = 2; i < buflen - 1; i++) {
      Wire.write(buf[i]);
    }
    Wire.endTransmission();    // stop transmitting

    Serial.print("Got: ");

    for (uint_fast8_t i = 0; i < buflen; i++) {
      Serial.print(buf[i]);
      Serial.print(' ');
    }

    Serial.println();
  }
}
