# staffReceiver
This is the remote control receiver for the larger [Wizard Staff Project](https://github.com/loughmiller/wizardStaff/).

Unfortunately, I couldn't get the main Teensy 3.6 to be able to run FastLED, FFTs for audio, and the virtualWire receiver code all at the same time successfully.  I think there's an issue specifically with the FastLED interrupts stepping on the virtualWire interrupts.  My workaround was to add another Teensy to the staff for the specific function of receiving messages from the remote and then passing them via I2C to the main Teesy 3.6.  I used a Teensy LC for minimal power consumption.
