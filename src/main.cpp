#include <VirtualWire.h>

const int led_pin = 13;
const int receive_pin = 12;

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

void loop()
{
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;

    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
	    int i;

        digitalWrite(led_pin, HIGH); // Flash a light to show received good message
        delay(100);                  // leave the LED on long enough to see it
        // Message with a good checksum received, print it.
        Serial.print("Got: ");

        for (i = 0; i < buflen; i++)
        {
            Serial.print(buf[i]);
            Serial.print(' ');
        }

        Serial.println();
        digitalWrite(led_pin, LOW);
    }
}
