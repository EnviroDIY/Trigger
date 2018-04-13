/*
 *Tigger.h
 *This file is part of the EnviroDIY modular sensors library for Arduino
 *
 *Initial library developement done by Bobby Schulz (schu3119@umn.edu)
 *
 *This library is used to setup and external trigger function, based on the values of a sensor, an output pin can be
 triggered to either flip high/low, or simply trigger a pulse whenever that value condition is triggered
 The library is made to operate on highly volitile signals, it requires n number of readings to be above or below the trigger
 value before it trips, thus reducing the posibility of a erronious triggering event 
*/

#ifndef Trigger_h
#define Trigger_h

#include <Arduino.h>
#include <pins_arduino.h>

class Trigger {
public:
	Trigger(float _TripValue, int _OutputPin, int _NumVals, int _Polarity = 1, char _Mode = '>', int _PulseLength = 1000);
	void begin();
	bool test(float Val);
	bool test(int Val);
	
private:
	float TripValue;
	int OutputPin;
	int NumVals;
	int Polarity;
	int TriggeredValue = HIGH;
	int IdleValue = LOW;
	int PulseLength; 
	char Mode; 
	void initOutput();
	void triggerOutput(bool Status);
	void pulse(int Pin, int Period);
};

#endif