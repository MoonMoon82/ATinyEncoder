#include <Arduino.h>
#include <SoftwareSerial.h>

#define RX        4
#define TX        1
#define PUSH_BTN  3
#define PIN_A     0
#define PIN_B     2

SoftwareSerial Serial(RX, TX);
// A turn counter for the rotary encoder (negative = anti-clockwise)

struct Info{
  int8_t rotationCounter;
  bool pushed;
};

union Packet1{
  char buffer[sizeof(Info)];
  Info EncoderInfo;
} SendPacket;


//int8_t rotationCounter = 0;

int8_t checkRotaryEncoder() {
    // Reset the flag that brought us here (from ISR)
    //rotaryEncoder = false;

    static uint8_t lrmem = 3;
    static int lrsum = 0;
    static int8_t TRANS[] = {0, -1, 1, 14, 1, 0, 14, -1, -1, 14, 0, 1, 14, 1, -1, 0};

    // Read BOTH pin states to deterimine validity of rotation (ie not just switch bounce)
    int8_t l = digitalRead(PIN_A);
    int8_t r = digitalRead(PIN_B);

    // Move previous value 2 bits to the left and add in our new values
    lrmem = ((lrmem & 0x03) << 2) + 2 * l + r;

    // Convert the bit pattern to a movement indicator (14 = impossible, ie switch bounce)
    lrsum += TRANS[lrmem];

    /* encoder not in the neutral (detent) state */
    if (lrsum % 4 != 0) {
        return 0;
    }

    /* encoder in the neutral state - clockwise rotation*/
    if (lrsum == 4) {
        lrsum = 0;
        return 1;
    }

    /* encoder in the neutral state - anti-clockwise rotation*/
    if (lrsum == -4) {
        lrsum = 0;
        return -1;
    }

    // An impossible rotation has been detected - ignore the movement
    lrsum = 0;
    return 0;
}

void setup()
{
    Serial.begin(9600);
    pinMode(PIN_A, INPUT_PULLUP);
    pinMode(PIN_B, INPUT_PULLUP);
    pinMode(PUSH_BTN, INPUT_PULLUP);
}

void loop()
{
  int8_t rotationValue = checkRotaryEncoder();
  if ( !digitalRead(PUSH_BTN) ) { SendPacket.EncoderInfo.pushed = true; }
  SendPacket.EncoderInfo.rotationCounter += rotationValue;
  
  if ((SendPacket.EncoderInfo.rotationCounter != 0) || (SendPacket.EncoderInfo.pushed)){
    if ( Serial.available() ){
      Serial.write(SendPacket.buffer,2);
      char c = Serial.read();
      SendPacket.EncoderInfo.rotationCounter = 0;
      SendPacket.EncoderInfo.pushed = false;
    }
  }
}
