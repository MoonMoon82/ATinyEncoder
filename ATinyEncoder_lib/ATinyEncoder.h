#include <Arduino.h>

struct Info{
  int8_t rotationCounter;
  bool pushed;
};

class ATinyEnocder {
    private:
    HardwareSerial* SerialPort;
    boolean called = false;

    public:
    int avail=0;
    Info RecPacket;
    boolean newInfo = false;
    ATinyEnocder (HardwareSerial* targetPort){
        SerialPort = targetPort;
        SerialPort->begin(9600);
    }
    boolean handle(){
        char ok = 90;
        newInfo = false;
        if ( called == false ){
            SerialPort->write(ok);
            called = true;
        }
        avail = SerialPort->available();
        if (avail >= 2) {
            SerialPort->readBytes((uint8_t*)(&RecPacket),2);
            if ( Serial1.available() == 0 ) { called = false; }
            newInfo = true;
            return true;
        }
    return false;
    }
    void reset(){
        RecPacket.rotationCounter = 0;
    }
};

