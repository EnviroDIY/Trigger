# Trigger
An Arduino library to trigger an external switch based on a measured variable exceeding a threshold.

The trigger function evaluates the most recent value(s) from an external sensor relative to (greater than or less than) a threshold value to switch an Arduino output pin from high to low, from low to high, or to send a pulse of a fixed time length (i.e. low-high-low).

The library can operate on highly volatile signals because it allows the user to require that multiple readings in a row are above or below the trigger value before it trips, thus reducing the possibility of a erroneous triggering event (i.e. a "trip" of the trigger).

To add a trigger to your Arduino sketch (`*.ino` file), you need to add a "Constructor" block of code above the setup function then add a "Test" block of code in the loop() to test new values versus the threshold value.

### Construct Trigger object above the `setup()` function
Below is example code that can be universally applied to any `*.ino` file, where the constructor accepts the following arguments:

- ***Threshold*** or ***TripValue*** is the value which when crossed, the output pin switches polarity or delivers a pulse.
- ***TriggerPin*** or ***OutputPin*** is the pin number that delivers the switched polarity or pulse.
- ***NumberOfSamples*** or ***NumVals*** is the number of most recent values that are compared to the TripValue.
- ***Polarity*** is the value which should be present when triggered (1 for HIGH, 0 for LOW).
- ***Mode*** (either '<' or '>') sets the comparison operator, to '<' to test for a value less than the threshold, or to '>' to test for a value greater than
- ***PulseLength*** is the number of milliseconds long a pulse should last once the trigger is activated. The default is 1000 ms. Alternately set to 0 for simple toggle to reverse polarity.

```c++
// ==========================================================================
//    External Trigger
// ==========================================================================
#include <Trigger.h>
const int8_t TriggerPin = 7;  // Pin to switch power on and off (-1 if unconnected)
const float TripValue = 50; //The threshold of tripping the system
const int8_t NumberOfSamples = 3; //The number of consecutive samples which must be above or below the trigger level to force a trip
const int Polarity = 1; //sets the polarity of the output value, 1 means active high, 0 is active low
const char Mode = '>'; //Sets the mode of operation to '<' to test for a value less than the threshold, or to '>' to test for a value greater than
const int PulseLength = 3000; //Triggers a pulse with a set length of milliseconds when trigger is activated, default is 1000 ms, set to 0 for simple toggle
Trigger trigger(TripValue, TriggerPin, NumberOfSamples, Polarity, Mode, PulseLength);
```

### Begin Trigger function in the `setup()` function block
Place this line of code somewhere in the `setup()` function block.
```c++
trigger.begin();  //Setup trigger function
```

### Test Trigger function in the `loop()` function block
To test new values versus the threshold value.
This is an example of the most basic requirement.
```c++
trigger.test(triggerTestValue); // Have the trigger function run a test using the input from the last 3 values of `triggerTestValue`

```

This example code is designed for use with the [EnviroDIY ModularSensors](https://github.com/EnviroDIY/ModularSensors) library (examples such as `logging_to_EnviroDIY.ino` or `simple_logging`). For a complete example, see https://github.com/EnviroDIY/Trigger/tree/master/examples/simple_logging.
```c++
// Trigger function: Test if value of selected variable passes threshold
Serial.print(F("Triggering on "));
Serial.print(yTurb->getVarName());
Serial.print(F(", last measured = "));
Serial.print(yTurb->getValue());
Serial.print(F(" "));
Serial.println(yTurb->getVarUnit());

float triggerTestValue = yTurb->getValue(); // Assign and update triggerTestValue

trigger.test(triggerTestValue); // Have the trigger function run a test using the input from the last 3 values of `triggerTestValue`
```
