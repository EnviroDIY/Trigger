/*
 *Trigger.h
 *This file is part of the EnviroDIY modular sensors library for Arduino
 *
 *Initial library developement done by Bobby Schulz (schu3119@umn.edu)
 *							 Anthony Aufdenkampe (aaufdenkampe@limno.com)
 *
 *This library is used to setup an external trigger function, based on the values of a sensor, an output pin can be
 triggered to either flip high/low, or simply trigger a pulse whenever that value condition is triggered
 * The library is made to operate on highly volatile signals, it requires n number of readings to be above or below the trigger
 value before it trips, thus reducing the possibility of a erroneous triggering event
*/

#include "Trigger.h"

//TripValue is value which when exceeded, the pin changes polarity, OutputPin is the pin which is switched,
//NumVals are the number of average samples taken, Polarity is the value which should be present when triggered (1 for HIGH, 0 for LOW)
//
Trigger::Trigger(float _TripValue, int _OutputPin, int _NumVals, int _Polarity, char _Mode, int _PulseLength) {
	TripValue = _TripValue;
	OutputPin = _OutputPin;
	NumVals = _NumVals;
	Polarity = _Polarity;
	TriggeredValue = Polarity;  //Set triggerd value based on polarity
	IdleValue = 1 - Polarity;  //Set idle value to opposite of triggerd value
	PulseLength = _PulseLength; //Copy pulse length
	Mode = _Mode; //Set global mode, either '<' or '>'
}

void Trigger::begin() {
	initOutput();
}

bool Trigger::test(float Val) {
	// static LastStatus = false; //Keep state of the system, if the last value it receved was above or below the trip point
	static bool TripStatus = false; //Used to see if device has been tripped or not
	static int Count = 0;

	if(Val == -9999 || Val == 0) return TripStatus; //If a non valid value is passed, simply break out of test function
	//designed for use with EnviroDIY Modular sensor library convention

	if(Mode == '>') {  //Trigger on greater than
		if(Val > TripValue && TripStatus == false) {  //trip value, device idle
			Count++;  //Increment count of trip values
		}

		else if(Val < TripValue && TripStatus == false) {  //idle value, device idle
			Count = 0;  //Clear count if you get a single bad value before you have been tripped
		}

		else if(Val < TripValue && TripStatus == true) {  //idle value, device tripped
			Count--; //Decrement count if you get a bad value but the device is already tripped
		}

		else if(Val > TripValue && TripStatus == true) {  //trip value, device tripped
			//Do nothing in this call
		}
	}

	if(Mode == '<') {  //Trigger on less than
		if(Val < TripValue && TripStatus == false) {  //trip value, device idle
			Count++;  //Increment count of trip values
		}

		else if(Val > TripValue && TripStatus == false) {  //idle value, device idle
			Count = 0;  //Clear count if you get a single bad value before you have been tripped
		}

		else if(Val > TripValue && TripStatus == true) {  //idle value, device tripped
			Count--; //Decrement count if you get a bad value but the device is already tripped
		}

		else if(Val < TripValue && TripStatus == true) {  //trip value, device tripped
			//Do nothing in this call
		}
	}

	if(Count >= NumVals && TripStatus == false) {
		triggerOutput(true); //If device gets n concecutive trip vals, trip
		TripStatus = true;
	}
	if(Count == 0 && TripStatus == true) {
		triggerOutput(false); //If device gets n concecutive idle vals, idle
		TripStatus = false;
	}
	return TripStatus;
}

bool Trigger::test(int Val) {  //Overload to define test for integer values as well
	return test(float(Val));  //Inneficient coding, but simple to read, FIX later??
}

void Trigger::initOutput() {  //Moddify this function to setup whatever output is desired
	pinMode(OutputPin, OUTPUT);
	digitalWrite(OutputPin, IdleValue); //Set pin to the "off" state
}

void Trigger::triggerOutput(bool Status) {  //Moddify this function to either set or clear output dependent of Status value

	if(Status) {  //Trigger output, place moddified code inside
		if(PulseLength == 0) digitalWrite(OutputPin, TriggeredValue);
		else pulse(OutputPin, PulseLength);
	}
	else {	//Idle output, place moddified code inside
		if(PulseLength == 0) digitalWrite(OutputPin, IdleValue);  //Only do anything for non-pulse
	}
}

void Trigger::pulse(int Pin, int Period) {
	digitalWrite(Pin, TriggeredValue);
	delay(Period);
	digitalWrite(Pin, IdleValue);
}
