/*
  DS1621.cpp - Arduino library for Maxim DS1621 Digital Thermometer
  this library is free software: you can redistribute it and/or modify
  it. 
  THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION WITHOUT ANY WARRANTIES
  
  Thermostat functions not yet implemented
 
  
*/
#include "DS1621.h"
#include <Wire.h>

int _addr;
DS1621::DS1621(){
}
void DS1621::setup(int addr){//Initialize Arduino Wire and get device i2c address
	Wire.begin();
	_addr=addr;
}

void DS1621::setMode(uint8_t mode){ // ONE_SHOT or CONTINUOUS
	
	Wire.beginTransmission(_addr);
	Wire.write(Acc_Conf);
	Wire.write(mode);
	Wire.endTransmission();
	delay(50);
}
float DS1621::getTemp(){//Returns temperature with 0.5°C resolution
	uint8_t _TL;
	uint8_t _TH;
	int _temp;
	float temp;
	Wire.beginTransmission(_addr);
	Wire.write(Rd_Temp);
	Wire.endTransmission();
	Wire.requestFrom(_addr, 2);
	_TH=Wire.read();
	_TL=Wire.read();
	_temp=(_TH<<1)|(_TL>>7);
	if(_TH>=B10000000){
		_temp=_temp|0xFE00;
	}
	temp=_temp*0.5;
	return(temp);

}
int DS1621::getLrTemp(){//Returns temperature with 1°C resolution
	uint8_t _TH;
	int temp;
	Wire.beginTransmission(_addr);
	Wire.write(Rd_Temp);
	Wire.endTransmission();
	Wire.requestFrom(_addr,1 );
	_TH=Wire.read();
	if(_TH>=B10000000){
		temp=_TH|0xFF00;
	}
	return(temp);
}
float DS1621::getHrTemp(){//Returns temperature with 0.01°C resolution
	float _hr_temp;
	float _storage;
	int temp_read=getLrTemp();
	delay(10);
	uint8_t count_remain=readCounter();
	delay(10);
	uint8_t count_per_c=readSlope();
	_storage=(float)(count_per_c-count_remain)/(float)count_per_c;
	_hr_temp=temp_read-0.25+_storage;
	return _hr_temp;
}
uint8_t DS1621::readSlope(){
	uint8_t _slope;
	Wire.beginTransmission(_addr);
	Wire.write(Rd_Slope);
	Wire.endTransmission();
	Wire.requestFrom(_addr,1);
	_slope=Wire.read();
	return(_slope);
}
uint8_t DS1621::readCounter(){
	uint8_t _counter;
	Wire.beginTransmission(_addr);
	Wire.write(Rd_Count);
	Wire.endTransmission();
	Wire.requestFrom(_addr,1);
	_counter=Wire.read();
	return(_counter);
}

void DS1621::startConv(){//Begin temperature Conversion
	Wire.beginTransmission(_addr);
	Wire.write(Start_Conv);
	Wire.endTransmission();
}
void DS1621::stopConv(){//STOP temerature conversion
	Wire.beginTransmission(_addr);
	Wire.write(Stop_Conv);
	Wire.endTransmission();
}
uint8_t DS1621::available(){//returns 1 last converted temperature is available 0 otherwise
	uint8_t _available;
	Wire.beginTransmission(_addr);
	Wire.write(Acc_Conf);
	Wire.endTransmission();
	Wire.requestFrom(_addr,1);
	_available=Wire.read();
	_available>>=7;
	return(_available);
}