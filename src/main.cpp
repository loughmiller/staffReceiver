#include <VirtualWire.h>

const uint_fast8_t led_pin = 13;
const uint_fast8_t receive_pin = 12;
const byte authByteStart = 117;
const byte authByteEnd = 115;

void setup()
{
    while(!Serial && millis() < 10000);
    Serial.println("setup");

    // Initialise the IO and ISR
    vw_set_rx_pin(receive_pin);
    vw_setup(2000);	 // Bits per sec

    vw_rx_start();       // Start the receiver PLL running
    pinMode(led_pin, OUTPUT);
}

uint_fast8_t lastMessageID = 255;

void loop()
{
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;

    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
        uint_fast8_t messageID = buf[1];

        // Serial.print(lastMessageID);
        // Serial.print("\t");
        // Serial.print(messageID);
        // Serial.println("");

        if (messageID == lastMessageID) {
            return;
        }

        lastMessageID = messageID;

        Serial.print("Got: ");

        for (uint_fast8_t i = 0; i < buflen; i++)
        {
            Serial.print(buf[i]);
            Serial.print(' ');
        }

        Serial.println();
        digitalWrite(led_pin, LOW);
    }
}
