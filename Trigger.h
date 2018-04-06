

#ifndef Trigger_h
#define Trigger_h

#include <Arduino.h>
#include <pins_arduino.h>

class Trigger {
public:
	Trigger(float _TripValue, int _OutputPin, int _NumVals, int _Polarity = 1, int _PulseLength = 1000);
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
	void initOutput();
	void triggerOutput(bool Status);
	void pulse(int Pin, int Period);
};

#endif