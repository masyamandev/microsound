# Microsound demo for ATtiny861 / ATtiny461

Minimalistic example of using microsound on ATtiny861 / ATtiny461.

# Characteristics

- MCU: ATtiny861 / ATtiny461
- CPU frequency: 16MHz
- Sound quality: 8bits, 32000Hz
- Output: PWM on pin PB3
- Channels: 5 wavetable + 1 noise

# Circuit

```
+5V    
 ^    ATtiny861
 |   +--------+
 +---+VCC     |    R1
     |     PB3+---/\/\--+-----> OUT
     |        |         |
 +---+GND     |        === C1
 |   +--------+         |
 |                      |
--- Grnd               --- Grnd
```

# Build

```
make clean hex 
make program
```
To build and flash this demo for ATtiny461 it's required to change `DEVICE` in `Makefile` to `attiny461`. 
