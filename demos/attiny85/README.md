# Microsound demo for ATtiny85 / ATtiny45

Minimalistic example of using microsound on ATtiny85 / ATtiny45.

# Characteristics

- MCU: ATtiny85 / ATtiny45
- CPU frequency: 16MHz
- Sound quality: 8bits, 32000Hz
- Output: PWM on pin PB4
- Channels: 5 wavetable + 1 noise

# Circuit

```
+5V    
 ^    ATtiny85
 |   +--------+
 +---+VCC     |    R1
     |     PB4+---/\/\--+-----> OUT
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
To build and flash this demo for ATtiny45 it's required to change `DEVICE` in `Makefile` to `attiny45`. 
