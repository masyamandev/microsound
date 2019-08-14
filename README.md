# Microsound

Microsound is a sound generation engine for 8-bits AVR microcontroller based on wave table.

Engine is designed for small firmware size (2-8 kBytes depending on included instruments) and
is able to play up to 5 notes simultaneously plus one noise channel on 8MHz MCU with hardware
multiplication. ATtiny MCUs does not have hardware multiplication so performance is approximately 
2 times slower. This means that ATtiny should use less channels or use higher frequency.

Supported MCUs are:
- ATmega8
- ATmega328p
- ATtiny25/45/85
- ATtiny261/461/861
- ATtiny26

Even through 2kBytes MCUs are supported it's strongly recommended to use 4+kBytes MCUs.

# Software requirements

Code is writtenn in c with some inline assebler for ATtiny devices. Tools are used to build demos:
- `make` as build system
- `avr-gcc` as compiler
- `avrdude` as MCU flashing tool

To build and flash MCU:
```
make clean hex 
make program
```

# Dir structure

Project has the following dir structure:
- microsound: main codebase for sound generator.
- - devices: different drivers for MCUs. There can be several different drivers for the same MCU, e.g. 
for different timer usage.
- - instruments: wavetable samples.
- - samples: examples of sound effects and melodies.
- utils: various utils used by microsound engine.
- demos: demos for different MCUs. Most of demos contain minimal examples for building working example.
- lcd: driver for LCD display used in some demos.

# Usage

Basic usage contains of several steps:
```
// Include driver for your MCU and micromusic engine:
#include "../../microsound/devices/atmega8timer1cpu8mhz.h"
#include "../../microsound/micromusic.h"

// Make some settings
#define CHANNELS_SIZE	5
#define SAMPLES_SIZE	16
#define USE_NOISE_CHANNEL

initMusic(); // Init music data and sound control
sei(); // Enable interrupts, silence sound should be generated
setSample(0, instrument1); // Use instrument1 as sample 0
setSample(1, instrument2); // Init all other instruments...

playMusic(mySong); // Start playing music at pointer mySong
while (!isMusicStopped) {
    fillMusicBuffer(); // Fill music buffer in loop
    // Do some other stuff
}

```

Song data should contain the following:
```
// Init byte array in PROGMEM memory space:
const uint8_t demoSample[] PROGMEM = {
		DATA_TEMPO(160), // Set beats per minute
		DATA_INSTRUMENT(0, 1), // Assign instrument 1 (see setSemple) to channel 0
		DATA_INSTRUMENT(1, 1), // Assign instrument 1 (see setSemple) to channel 1
		DATA_VOLUME(0, 128), // Set volume 128 to channel 1
		DATA_VOLUME(0, 128), // Set volume 128 to channel 1
		DATA_PLAY(0, NOTE_A4, 1), // Play note A4 on channel 0 and wait 1 beat 
		DATA_PLAY(1, NOTE_A3, 1), // Play note A3 on channel 1 and wait 1 beat
		DATA_WAIT(63), // Wait 63 beats
		DATA_END() // End of data stream
};
```

Commands are packed into 1-3 bytes and has some limitations:
- DATA_VOLUME accepts volume values in range [0..255] or [0..127] in some software 
multiplication implementations for ATtiny.
- DATA_PLAY accepts wait values in range [0..7].
- DATA_WAIT accepts wait values in range [0..63].

For more detailed information see `demos` and `micromusic/commands.h`.

# Writing own melodies

There is a port of microsound engine to JavaScript `demos/wavepot.js`. 
This port can be used to play byte stream on site wavepot.com. This port does *not* have limitations
described above, so stream may not be played properly on MCU if these limitations does not meet requirements.
Also this port may produce slightly better sound quality. To simulate 8-bits sound similar to c engine
set variable `simulate8bits` to `true`.
