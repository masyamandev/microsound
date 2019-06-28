
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
	#define toSample(uint16)		(uint16 >> 8)
	#define sampleToUint8(sample)	(sample)
	#define sampleToUint16(sample)	(sample << 8)
#elif BUFFER_BITS == 16
	typedef uint16_t soundSample;
	#define toSample(uint16)		(uint16)
	#define sampleToUint8(sample)	(sample >> 8)
	#define sampleToUint16(sample)	(sample)
#endif


#define BUFFER_MASK (BUFFER_SIZE - 1)
volatile soundSample soundBuffer[BUFFER_SIZE];
volatile soundSample bufferRead;
soundSample bufferWrite;


#define isBufferFull	(bufferRead == bufferWrite)
#define isBufferNotFull	(bufferRead != bufferWrite)


inline void writeToBuffer(soundSample value) {
	bufferWrite = (bufferWrite + 1) & BUFFER_MASK;
	soundBuffer[bufferWrite] = (value);
}

inline soundSample readFromBuffer() {
	bufferRead = (bufferRead + 1) & BUFFER_MASK;
	return soundBuffer[bufferRead];
}
