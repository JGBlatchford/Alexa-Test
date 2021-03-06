/******************************************************************
PatriotSwitch plugin

Features:
- Read and debounce switch input

http://www.github.com/rlisle/Patriot

Written by Ron Lisle

BSD license, check license.txt for more information.
All text above must be included in any redistribution.

Changelog:
2018-01-18: Add type property
2017-10-27: v2.0.0. Change name to command.
2017-05-17: Move to separate library
2017-05-15: Make devices generic
2017-03-24: Rename Patriot
2017-03-05: Convert to v2 particle library
2016-07-29: Refactor to separate switch and switches classes
         Add mapping to an activity
2016-06-21: Photon version
2016-02-3: Initial version
******************************************************************/

#include "PatriotSwitch.h"

extern String publishNameVariable;

#define kDebounceDelay 50

/**
 * Constructor
 * @param pinNum int pin number that is connected to the switch
 * @param name  String name of the event to send when switch changes
 */
Switch::Switch(int pinNum, String name, String command)
        : Device(name, DeviceType::Switch),
        _pin(pinNum),
        _command(command)
{
    _percent = 0;
    pinMode(pinNum, INPUT_PULLUP);
    _lastReadTime = millis();
}


/**
 * loop()
 * This is called repeatedly to allow device to do its work.
 */
void Switch::loop()
{
    if (isTimeToCheckSwitch())
    {
        if (didSwitchChange())
        {
            notify();
        }
    }
}


// Private Helper Methods
/**
 * isTimeToCheckSwitch()
 * @return bool if enough time has elapsed to sample switch again
 */
bool Switch::isTimeToCheckSwitch()
{
    long currentTime = millis();
    if (currentTime < _lastReadTime + kDebounceDelay)
    {
        return false;
    }
    _lastReadTime = currentTime;
    return true;
}


/**
 * didSwitchChange()
 * @return bool if switch has changed since last reading
 */
bool Switch::didSwitchChange()
{
    bool newState = digitalRead(_pin) == 0;
    bool isOn = _percent > 0;
    if (newState == isOn)
    {
        return false;
    }
    _percent = newState ? 100 : 0;
    return true;
}


/**
 * notify()
 * Publish switch state
 */
void Switch::notify()
{
    String pubString = _command + ":" + (_percent > 0 ? "100" : "0");
    Serial.println(pubString);
    //TODO: get event name from IoT instead of hardcoded "patriot"
    //Particle.publish("patriot", pubString, 60, PRIVATE);

    Particle.publish(publishNameVariable, pubString, 60, PRIVATE);
}
