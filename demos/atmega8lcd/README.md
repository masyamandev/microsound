# Microsound demo for ATmega8

Example project with usage microsound on ATmega8.

This project shows how 16x2 characters LCD display can be used simultaneously with 
playing sound.
Some buttons are used to play samples.

# Characteristics

- MCU: ATmega8 / ATmega8a
- CPU frequency: 8MHz
- Sound quality: 8bits, 31250Hz
- Output: PWM on pin PB1
- Channels: 5 wavetable + 1 noise

# Circuit

```
              +5V    
               ^     ATmega8
               |   +---------+
               +---+VCC      |
    Buttons        |      PD0+-----> to LCD D4
        _          |      PD1+-----> to LCD D5
  +-----_`---------+PC0   PD2+-----> to LCD D6
  +-----_`---------+PC1   PD3+-----> to LCD D7
  +-----_`---------+PC2   PD5+-----> to LCD RS
  +-----_`---------+PC3   PD6+-----> to LCD E
  +-----_`---------+PC4      |
  +----- `---------+PC5      |    R1
  |                |      PB1+---/\/\--+-----> OUT
  |            +---+GND      |         |
  |            |   +---------+        === C1
  |            |                       |
 --- Grnd     --- Grnd                --- Grnd
```

MCU pinout:
* PC0-PC5: buttons
* PD0-PD3, PD5-PD6: LCD display
* PB1: PWM output

LCD display pinout:
* VSS: Grnd
* VDD: +5V
* VO:  to variable resistor for contrast adjustment
* RS: PD5
* RW: Grnd
* E: PD6
* D4-D7: PD0-PD3
* A: +5V via resistor
* K: Grnd


# Build

```
make clean hex 
make program
```
