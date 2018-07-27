/*
  Trigger_HardwareSimulation.ino

  Simulates a trigger pulse signal for testing the various hardware designs
  found in this repo at https://github.com/EnviroDIY/Trigger/tree/master/hardware.
  This sketch does not test the software in this repo.

  Adapted from Blink sketch by Anthony Aufdenkampe (aaufdenkampe@limno.com)

 */


// the setup function runs once when you press reset or power the board
void setup() {
    // initialize digital pins for output.
    pinMode(8, OUTPUT);  // LED
    pinMode(7, OUTPUT);   // Trigger
    pinMode(22, OUTPUT);  // Switching Power
}

// the loop function runs over and over again forever
void loop() {

    digitalWrite(22, HIGH);   // Power ON
    delay(3000);

    digitalWrite(8, HIGH);   // LED ON (HIGH is the voltage level)
    digitalWrite(7, HIGH);   // Trigger ON
    delay(1000);
    digitalWrite(8, LOW);    // turn the LED off by making the voltage LOW
    digitalWrite(7, LOW);    // turn the LED off by making the voltage LOW
    delay(3000);

    digitalWrite(22, LOW);   // Power OFF

    delay(10000);              // wait for 10 seconds
}
