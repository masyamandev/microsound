# Microsound demo for ATmega8

Minimalistic example of using microsound on ATmega8.

# Characteristics

- MCU: ATmega8 / ATmega8a
- CPU frequency: 8MHz
- Sound quality: 8bits, 31250Hz
- Output: PWM on pin PB1
- Channels: 5 wavetable + 1 noise

# Circuit

```
+5V    
 ^    ATmega8
 |   +--------+
 +---+VCC     |    R1
     |     PB1+---/\/\--+-----> OUT
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
