#include <Arduino.h>

struct Info{
  int8_t rotationCounter;
  bool pushed;
};

union Packet1{
  char buffer[sizeof(Info)];
  Info EncoderInfo;
} RecPacket;



void setup()
{
    Serial.begin(115200);
    Serial1.begin(9600);
    delay(3500);
    Serial.println("Setup completed");
}
char ok = 80;
bool called = false;
void loop() {
    //Serial.print(".");
    if ( called == false ){
        Serial1.write(ok);
        called = true;
    }
    int avail = Serial1.available();
    if (avail >= 2) {
        Serial.print("avail=");
        Serial.print(avail);
        Serial.print("  ");
        Serial1.readBytes(RecPacket.buffer,2);
        //if ( ci != 0) {
            Serial.print("Pushed=");
            Serial.print(RecPacket.EncoderInfo.pushed);
            Serial.print("    Counter=");
            Serial.println(RecPacket.EncoderInfo.rotationCounter);
        //}
        if ( Serial1.available() == 0 ) { called = false; }
    }
    
    delay(50);

}
