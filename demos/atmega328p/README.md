# Microsound demo for ATmega328p

Minimalistic example of using microsound on ATmega328p.

# Characteristics

- MCU: ATmega328p
- CPU frequency: 8MHz
- Sound quality: 8bits, 31250Hz
- Output: PWM on pin PB1
- Channels: 5 wavetable + 1 noise

# Circuit

```
+5V    
 ^   ATmega328p
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
