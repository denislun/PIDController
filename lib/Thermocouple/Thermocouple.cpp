/*----------------------------------------------------------------------*
 * Thermocouple.cpp -- Library for reading thermocouple temperature     *
 * via a MAX6675.                                                       *
 *                                                                      *
 * Jack Christensen 16Feb2011                                           *
 *                                                                      *
 * This work is licensed under the Creative Commons Attribution-        *
 * ShareAlike 3.0 Unported License. To view a copy of this license,     *
 * visit http://creativecommons.org/licenses/by-sa/3.0/ or send a       *
 * letter to Creative Commons, 171 Second Street, Suite 300,            *
 * San Francisco, California, 94105, USA.                               *
 *----------------------------------------------------------------------*/

#include "Thermocouple.h"
#include <SPI.h>

Thermocouple::Thermocouple(int ssPin) {
    _first = true;
    _ssPin = ssPin;
    pinMode(_ssPin, OUTPUT);
    digitalWrite(_ssPin, HIGH);             //Start de-selected
}

void Thermocouple::beginSPITransaction() {
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE1));
}

void Thermocouple::endSPITransaction() {
  SPI.endTransaction();
}

float Thermocouple::readC() {
    unsigned int tcData;
    float temp, avgTemp;

    //read the temperature
    beginSPITransaction();
    digitalWrite(_ssPin, LOW);
    tcData = SPI.transfer(0x00) << 8;
    tcData |= SPI.transfer(0x00);
    digitalWrite(_ssPin, HIGH);
    endSPITransaction();

    if (tcData & 0x0004) {                  //open thermocouple circuit
        return -1.0;
    }
    else {
        temp = (tcData >> 3) / 4.0;         //calculate deg C
        if (_first) {                       //if first time through, fill the readings array
            _first = false;
            for (int i=0; i<6; i++) {
                _temps[i] = temp;
            }
        }
        for (int i=0; i<5; i++) {           //shift prior readings
            _temps[i] = _temps[i+1];
        }
        _temps[5] = temp;                   //put the new reading in at the top end of the array
        avgTemp = 0.0;                      //calculate the average
        for (int i=0; i<6; i++) {
            avgTemp += _temps[i];
        }
        avgTemp /= 6.0;
        return avgTemp;
    }
}

float Thermocouple::readF() {
    float tempC;

    tempC = readC();
    if (tempC < 0.0) {
        return tempC;
    }
    else {
        return tempC * 9.0 / 5.0 + 32.0;
    }
}
