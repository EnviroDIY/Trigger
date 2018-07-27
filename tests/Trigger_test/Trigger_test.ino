/*****************************************************************************
Trigger_test.ino

Tests the software trigger with an incrementing set of triggerTestValues,
to send a trigger pulse signal.

by Anthony Aufdenkampe (aaufdenkampe@limno.com)

*****************************************************************************/


// ---------------------------------------------------------------------------
//    Configure External Trigger
// ---------------------------------------------------------------------------
#include <Trigger.h>
const int8_t TriggerPin = 7;  // Pin to switch power on and off (-1 if unconnected)
const float TripValue = 50; //The threshold of tripping the system
const int8_t NumberOfSamples = 3; //The number of consecutive samples which must be above or below the trigger level to force a trip
const int Polarity = 1; //sets the polarity of the output value, 1 means active high, 0 is active low
const char Mode = '>'; //Sets the mode of operation to '<' to test for a value less than the threshold, or to '>' to test for a value greater than
const int PulseLength = 3000; //Triggers a pulse with a set length of milliseconds when trigger is activated, default is 1000 ms, set to 0 for simple toggle
Trigger trigger(TripValue, TriggerPin, NumberOfSamples, Polarity, Mode, PulseLength);

// Intialize triggerTestValue
float triggerTestValue = 40.5;

// ---------------------------------------------------------------------------
// Main setup function
// ---------------------------------------------------------------------------
void setup()
{
    // initialize digital pins for output.
    pinMode(8, OUTPUT);  // Green LED to indicate timing of trigger test
    pinMode(22, OUTPUT);  // Switching Power, indicated by red LED in bottom left

    // Set up serial monitor
    Serial.begin(57600);
    Serial.println(F("Trigger_test.ino"));

    // Begin the trigger function
    trigger.begin();  //NOTE: includes  initializing TriggerPin for output
}

// ---------------------------------------------------------------------------
// Main loop function
// ---------------------------------------------------------------------------
void loop()
{
    // Simulate waking station
    digitalWrite(22, HIGH);   // Power ON
    delay(2000);

    // Simulate updating sensor values
    triggerTestValue = triggerTestValue + 2.0;
    digitalWrite(8, HIGH);   // Green LED ON (HIGH is the voltage level)
    Serial.print(F("triggerTestValue = "));
    Serial.println(triggerTestValue);
    delay(1000);

    // Simulate evaluation of trigger
    trigger.test(triggerTestValue); //Have the trigger function run a test
    digitalWrite(8, LOW);    // Green LED OFF
    delay(1000);

    // Simulate putting station to sleep
    digitalWrite(22, LOW);   // Power OFF

    // Simulate station sleep interval
    delay(2000);              // wait for 6 seconds
}
