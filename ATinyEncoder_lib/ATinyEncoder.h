// Library for easy usage of ATinyEncoder:
// https://github.com/MoonMoon82/ATinyEncoder
#include <Arduino.h>

//Data structure to receive
struct Info{
  int8_t rotation;
  bool pushed;
};

//A simple class for easy usage of the ATinyEncoder
class ATinyEncoder {
    private:
        HardwareSerial* SerialPort; //Target Serial port to communicate with the ATTiny
        bool called = false;     //Remember if a request was sent

    public:
        Info status;             //Status of the Encoder 
        ATinyEncoder (HardwareSerial* targetPort){ //Initialize ATinyEncoder with Target Serial port
            SerialPort = targetPort;
            SerialPort->begin(9600);    //idk 9600baut works quite ok for me
        }

    bool handle(){
        status.rotation = 0;        //reset saved rotation
        if ( called == false ){
            char RequestByte = 90;              //request byte 80 (idk should I chose another byte?)
            SerialPort->write(RequestByte);     //send request to the ATTiny
            called = true;                      //remember that the request was sent
        }

        //if there are more than 2 bytes available in the serial port buffer, write it into the status structure
        if (SerialPort->available() >= 2) {
            SerialPort->readBytes((uint8_t*)(&status),2);
            if ( Serial1.available() == 0 ) { called = false; }
            return true;    //return true to show that new data has arrived
        }
    return false; //return false to show that no new data was received
    }
};
