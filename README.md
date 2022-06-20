# ATinyEncoder

A dedicated ATTiny85 as Rotary Encoder Interface based on:

https://github.com/RalphBacon/226-Better-Rotary-Encoder---no-switch-bounce

https://www.pinteric.com/rotary.html

His code has got high hitrate for accurate reading of rotary encoders. But it also has got a big flaw, if there are other time consuming tasks in your project which lead to a delayed call of the checkRotaryEncoder() routine. A delay in this case leads to a false estimation of the rotary encoder state.
To run his code on a dedicated ATTiny85 get's rid of this issue. The ATTiny85 is sending the relative iterations and state of the push button in a 2 byte structure over software-serial pins.

The byte structure:

1. byte bool - Pushbutton pressed
2. byte int_8 - Relative iterations of the rotary encoder since the last request


There's also a small and simple library for arduino framework based microcontrollers provided to communicate with the ATTiny controller.

