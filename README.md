# ATinyEncoder

A dedicated ATTiny85 as Rotary Encoder Interface based on:

https://github.com/RalphBacon/226-Better-Rotary-Encoder---no-switch-bounce

https://www.pinteric.com/rotary.html

His code has got high hitrate for accurate reading of rotary encoders. But there is also a big flaw, if there are other time consuming tasks in your project which lead to a delayed call of the checkRotaryEncoder() routine. A delay in this case leads to a significant false estimation of the rotary encoder state.
To run his code on a dedicated ATTiny85 get's rid of this issue. The ATTiny85 is sending the relative iterations and state of the push button in a 2 byte structure over software-serial defined gpio pins.

The byte structure:

1. byte int_8 - Relative iterations of the rotary encoder since the last request
2. byte uint_8 - Change of the pushbutton state


There's also a small and simple library for arduino framework based microcontrollers provided to communicate with the ATTiny controller.

Youtube Tutorial - How to mount a ATTiny directly to a std. Rotary Encoder:

[![Everything Is AWESOME](https://user-images.githubusercontent.com/41437842/174894199-6547f58c-7040-40b9-93c9-520fb75cf1d7.png)](https://www.youtube.com/watch?v=cieDlKowjJk "Everything Is AWESOME")
