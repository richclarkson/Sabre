/*
SaberButton.cpp - A library to read the button for the Saber music lighting product
Created by Steve Faletti, 2017-09-30
Proprietary to Richard Clarkson Studio
*/

#include "Arduino.h"
#include "SaberButton.h"

SaberButton::SaberButton(int pin)
{
	pinMode(pin, INPUT);
	_pin = pin;
	_prevMillis = 0;
	_pressMillis = 0;
	_pressType = 0; // 0:no press, 1: tap, 2: press
	tapThreshold = 50;
	tapLength = 300;
	pressThreshold = 500;
	pressLength = 1000;
}

// This function should be called repeatedly in the main loop. It assumes a debounced button, though in actual application it will just wait until the button has settled before beginning to count, which won't be noticed by most users.
void SaberButton::check()
{
	if (digitalRead(_pin) == HIGH)
	{
		_pressMillis += _getPressMillis();
		if (_pressMillis > pressThreshold)
		{
			_pressType = 2;
		}
	}
	else // _pin is LOW
	{
		// too short for a tap (bouncing), or between a tap and press
		if (_pressMillis <= tapThreshold || (_pressMillis > tapLength + tapThreshold && _pressMillis <= pressThreshold))
		{
			_pressType = 0; // no press recorded
		}
		// tap recorded
		else if (_pressMillis > tapThreshold && _pressMillis <= tapLength)
		{
			_pressType = 1; // tap press type recorded
		}
	}
}

char SaberButton::getPressType()
{
	char pressTypeHolder = _pressType;
	_pressType = 0;
	return pressTypeHolder;
}

unsigned long SaberButton::getPressLength() {
	unsigned long pressMillisHolder = _pressMillis;
	_pressMillis = 0;
	return pressMillisHolder;	
}

void SaberButton::_clearPrevMillis()
{
	_prevMillis = 0;
}

unsigned long SaberButton::_getPressMillis()
{
	unsigned long currentMillis = millis();
	unsigned long returnMillis = 0;
	// Check that some time has passed
	if (currentMillis > _prevMillis)
	{
		returnMillis = currentMillis - _prevMillis;
		_prevMillis = currentMillis;
	}
	else
	{
		// in the unlikely case of a millis() overflow this will wait for the counter to restart. This will likely not be noticed in normal use.
	}
	return returnMillis;
}
