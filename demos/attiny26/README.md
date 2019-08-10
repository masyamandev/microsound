# Microsound demo for ATtiny26

Minimalistic example of using microsound on ATtiny26.

# Characteristics

- MCU: ATtiny26
- CPU frequency: 16MHz
- Sound quality: 8bits, 31250Hz
- Output: PWM on pin PB2
- Channels: 4 wavetable, no per-channel volume control

# Circuit

```
+5V    
 ^    ATtiny26
 |   +--------+
 +---+VCC     |    R1
     |     PB2+---/\/\--+-----> OUT
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
