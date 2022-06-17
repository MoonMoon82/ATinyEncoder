//Firmware for ATTiny controller to be used as Rotary Encoder Interface
//https://github.com/MoonMoon82/ATinyEncoder

#include <Arduino.h>
#include <SoftwareSerial.h>

//Pin setup:
#define RX        4 //Serial Receive Pin
#define TX        1 //Serial Transmission Pin

#define PUSH_BTN  3 //Encoder Pushbutton
#define PIN_A     0 //Encoder Rotary switch 1
#define PIN_B     2 //Encoder Rotary switch 2

SoftwareSerial Serial(RX, TX);

boolean FreeToSend = false; //Host tells it is ok to send current encoder data

//Data structure to send
struct Info {
  int8_t rotation;
  bool pushed;
} InfoPacket;

//checkRotaryEncoder() by Ralph Bacon / Marko Pinteric
//https://github.com/RalphBacon/226-Better-Rotary-Encoder---no-switch-bounce
//https://www.pinteric.com/rotary.html

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

void setup() {
    Serial.begin(9600);

    //GPIO Pin Setup
    //INPUT_PULLUP allows it to connect the ATTiny directly to the encoder pins
    pinMode(PIN_A, INPUT_PULLUP);
    pinMode(PIN_B, INPUT_PULLUP);
    pinMode(PUSH_BTN, INPUT_PULLUP);
}

void loop() {

  //Lets analyse the current rotary switch states
  int8_t rotationDelta = checkRotaryEncoder();
  //Add the delta value to the saved rotation value
  InfoPacket.rotation += rotationDelta;

  //Get the push button state - reminder: due to the INPUT_PULLUP the state needs to be inverted
  boolean pushbutton = !digitalRead(PUSH_BTN);
  
  // If it's ok to send the current encoder data, check if something changed, then send it
  if ( FreeToSend ) {
    if ((InfoPacket.rotation != 0) || (InfoPacket.pushed != pushbutton)){
      InfoPacket.pushed = pushbutton;
      Serial.write((char*)(&InfoPacket),2);
      InfoPacket.rotation = 0; //Reset saved rotations count 

      FreeToSend = false; //Reset FreeToSend state
    }
  } else {
    if ( Serial.available() ){
    //Check if the host sends this specific byte to tell it's ok to send the current encoder data
      if ( Serial.read() == 90 ) { //idk ? What byte should I wait for?
        FreeToSend = true;
      }
    }
  }
}
