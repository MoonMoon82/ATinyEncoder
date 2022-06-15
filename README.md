# ATinyEncoder

A dedicated ATTiny85 as Rotary Encoder Interface based on:

https://github.com/RalphBacon/226-Better-Rotary-Encoder---no-switch-bounce

His code has got high hitrate for accurate reading of rotary encoders. But it also has got a big flaw if you're trying to get a rotary encoder working in your own project: Whatever what's in your code causing a delay of calling the checkRotaryEncoder() leads to a false estimation of the encoder state.
To get rid of the flaw, I decided to get his code running on a dedicated ATTiny85. It is sending the relative iterations and state of the push button in a 2 byte structure over software-serial pins.

The byte structure:

1. byte boolean - Pushbutton pressed
2. byte int_8 - Relative iterations of the rotary encoder since the last request


I also provide a small and simple library for arduino framework based microcontrollers to communicate with the ATTiny controller.
