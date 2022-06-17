//Example file for a ESP32 microcontroller using ATinyEncoder
//https://github.com/MoonMoon82/ATinyEncoder
#include "Arduino.h"
#include "ATinyEncoder_lib.h"

ATinyEncoder MyEncoder(&Serial2); //Serial2 on ESP32 default pins are GPIO 16(RX) and 17(TX)
int rotations = 0; //Saved rotations of the Rotary Encoder

void setup() {
  Serial.begin(115200);
}

void loop(){
  //if new Encoder data has arrived show it on default serial port
  if (MyEncoder.handle()) {
    rotations += MyEncoder.status.rotation; //Add new rotations to the saved rotations
    
    Serial.print("rotation=");
    Serial.print(rotations);
    Serial.print("  pushed=");
    Serial.println(MyEncoder.status.pushed);
  }
}
