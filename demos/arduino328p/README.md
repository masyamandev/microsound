# Microsound demo for Arduino based on ATmega328p

Minimalistic example of using microsound on Arduino based on ATmega328p.

# Characteristics

- MCU: ATmega328p
- CPU frequency: 16MHz
- Sound quality: 8bits, 31250Hz
- Output: PWM on pin PB1/D9
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
 +---+GND     |        === C1
 |   +--------+         |
 |                      |
--- Grnd               --- Grnd
```

# Build

1. Copy `microsound.ino` to the root of microsound library.
2. Open sketch in Arduino IDE.
3. Upload to Arduino.

Sketch was tested on a clone of Arduino Nano. It may not work on other clones.