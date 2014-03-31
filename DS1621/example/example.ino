#include "DS1621.h"
#include "Wire.h"
#define ONE_SHOT B00000001
DS1621 ds1621;
float temperatura;
void setup() {
  ds1621.setup(0x49);
  ds1621.setMode(ONE_SHOT);
  Serial.begin(9600);
}

void loop() {
   ds1621.startConv();
   if(ds1621.available()){
    temperatura=ds1621.getHrTemp();
    Serial.println(temperatura); 
     } 
  }
