
// INTERPOLATION_STRENGTH: interpolate (2^N-1) points.

#if INTERPOLATION_STRENGTH > 0

	// Linear interpolation
	uint8_t interpolationCounter;
	uint16_t interpolationValue;
	int16_t interpolationDiff;
	inline uint8_t getNextInterpolatedSample() {
		interpolationCounter = (interpolationCounter + 1) & ((1 << INTERPOLATION_STRENGTH) - 1);
		if (!interpolationCounter) {
			uint16_t next = sampleToUint16(readFromBuffer());
			interpolationDiff = ((int16_t)(next - interpolationValue)) >> INTERPOLATION_STRENGTH;
		}
		interpolationValue += interpolationDiff;
		return toSample(interpolationValue);
	}

#else

	#define getNextInterpolatedSample 	readFromBuffer

#endif
