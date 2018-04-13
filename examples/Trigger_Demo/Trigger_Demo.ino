// ==========================================================================
//    External Trigger Demo
// ==========================================================================
#include <Trigger.h>
const int8_t TriggerPin = 5;  // Pin to switch power on and off (-1 if unconnected)
const float Threshold = 512; //The threshold of tripping the system
const int8_t NumberOfSamples = 3; //The number of consecutive samples which must be above or below the trigger level to force a trip
const int Polarity = 1; //sets the polarity of the output value, 1 means active high, 0 is active low
const char Mode = '<'; //Sets the mode of operation to test for a value less than the threshold
const int PulseLength = 1000; //Triggers a pulse with a length of 1000 ms when trigger is activated, set to 0 for simple toggle
Trigger trig(Threshold, TriggerPin, NumberOfSamples, Polarity, Mode, PulseLength);

int AIn = 0; //Read from analog pin 0

void setup()
{
	trig.begin();  //Setup trigger function
}

void loop()
{
	trig.test(analogRead(AIn)); //Have the trigger function run a test using the input from AIn
	delay(1000); //Wait a bit before the next test	
}
