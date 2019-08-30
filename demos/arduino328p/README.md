# Microsound demo for Arduino based on ATmega168/328p

Minimalistic example of using microsound on Arduino based on ATmega168/328p.

# Characteristics

- MCU: ATmega168/328p
- CPU frequency: 16MHz
- Sound quality: 16bits, 31250Hz
- Output: PWM on pin PB1/D9 and PB2/D10
- Channels: 5 wavetable + 1 noise

Number of channels can be increased up to 8.

# Circuit

```
+5V    
 ^   ATmega328p
 |   +--------+
 +---+VCC     |    R1
     |  PB1/D9+---/\/\--+-----> OUT
     |        |         |
     |        |    R2   |
     | PB2/D10+---/\/\--+
     |        |         |
 +---+GND     |        === C1
 |   +--------+         |
 |                      |
--- Grnd               --- Grnd
```

Example uses 2 output pins. 
Pin PB1/D9 corresponds to higher byte of 16bits output.
Pin PB2/D10 corresponds to lower byte of 16bits output. 
Outputs should be mixed in this proportion: R2 = 256 * R1.

Resistor R2 can be omit. In this case output will be 8bits. 
If 8bits mode is used then it's recommended to use 8bits driver `atmega328Ptimer1.h` to free up pin PB2/D10 and some CPU and memory resources.

# Build

1. Copy `microsound.ino` to the root of microsound library.
2. Open sketch in Arduino IDE.
3. Upload to Arduino.

Sketch was tested on a clone of Arduino Nano. It may not work on other clones.