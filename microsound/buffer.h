/*
 * Control sound buffer.
 *
 * By default buffer is 8 samples long but this value can be increased via BUFFER_SIZE for longer user code execution.
 * Buffer size is 8 bits and is 2^n. Max buffer size is 256 samples.
 *
 * By default buffer contains 8 bits values but it can be switched to 16 bits.
 *
 * Additionally code allows to measure small periods of time via bufferReadCounter. On each buffer read value is incremented.
 */

// Length of a buffer, samples, valid values are 2^n
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 8
#endif

// Bit depth: 8 or 16
#ifndef BUFFER_BITS
#define BUFFER_BITS	8
#endif


#if BUFFER_BITS == 8
	typedef uint8_t soundSample;
	#define toSample(uint16)		((soundSample) (uint16 >> 8))
	#define sampleToUint8(sample)	((uint8_t) (sample))
	#define sampleToUint16(sample)	((uint16_t) (sample << 8))
#elif BUFFER_BITS == 16
	typedef uint16_t soundSample;
	#define toSample(uint16)		((soundSample) (uint16))
	#define sampleToUint8(sample)	((uint8_t) (sample >> 8))
	#define sampleToUint16(sample)	((uint16_t) (sample))
#endif


#define BUFFER_MASK ((uint8_t)(BUFFER_SIZE - 1))
volatile soundSample soundBuffer[BUFFER_SIZE];
volatile uint8_t bufferReadCounter;
uint8_t bufferWrite;

#define bufferRead		(bufferReadCounter & BUFFER_MASK)
#define isBufferFull	(bufferRead == bufferWrite)
#define isBufferNotFull	(bufferRead != bufferWrite)
#define samplesToWrite	(((uint8_t)(bufferRead - bufferWrite)) & BUFFER_MASK)
#define samplesInBuffer	(((uint8_t)BUFFER_SIZE) - samplesToWrite)


inline void writeToBuffer(soundSample value) {
	bufferWrite = (bufferWrite + 1) & BUFFER_MASK;
	soundBuffer[bufferWrite] = (value);
}

inline soundSample readFromBuffer() {
	return soundBuffer[(++bufferReadCounter) & BUFFER_MASK];
}
