/*
  DS1621.h - Arduino library for Maxim DS1621 Digital Thermometer
  this library is free software: you can redistribute it and/or modify
  it. 
  THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION WITHOUT ANY WARRANTIES
  
  Thermostat functions not yet implemented
  
*/
#ifndef	DS1621_H
#define DS1621_H
#include "Arduino.h"
class DS1621{
	
	static const uint8_t Rd_Temp = 0xaa;//Last temperature conversion access command 
	static const uint8_t Acc_TH = 0xa1;//Temperature Higer byte access command 
	static const uint8_t Acc_TL = 0xa2;//Temperature Lower byte access command 
	static const uint8_t Acc_Conf = 0xac;//Config register access command 
	static const uint8_t Rd_Count = 0xa8;//Counter register access command 
	static const uint8_t Rd_Slope = 0xa9;//Slope register access command 
	static const uint8_t Start_Conv = 0xee;//START conversion command
	static const uint8_t Stop_Conv = 0x22;//STOP conversion command
	
	uint8_t readSlope();
	uint8_t readCounter();
	
public:
	#define ONE_SHOT B00000001
	#define CONTINUOUS B00000000
	DS1621();
	void setup(int addr);
	void setMode(uint8_t mode);
	void startConv();
	void stopConv();
	float getTemp();
	float getHrTemp();
	int getLrTemp();
	uint8_t available();
};

#endif