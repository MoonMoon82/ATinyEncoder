#include <Arduino.h>

struct Info{
  int8_t rotationCounter;
  bool pushed;
};

class ATinyEnocder {
    private:
    HardwareSerial* SerialPort;
    boolean called = false;
    int available=0;

    public:
    Info RecPacket;
    ATinyEnocder (HardwareSerial* targetPort){
        SerialPort = targetPort;
        SerialPort->begin(9600);
    }
    boolean handle(){
        char ok = 90;
        if ( called == false ){
            SerialPort->write(ok);
            called = true;
        }
        available = SerialPort->available();
        if (available >= 2) {
            SerialPort->readBytes((uint8_t*)(&RecPacket),2);
            if ( Serial1.available() == 0 ) { called = false; }
            return true;
        }
    return false;
    }
    void reset(){
        RecPacket.rotationCounter = 0;
    }
};

