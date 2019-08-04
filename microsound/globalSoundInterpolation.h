/*
 * Takes care about sound interpolation.
 * This implementation provides simple linear interpolation.
 *
 * Value INTERPOLATION_STRENGTH means interpolation of (2^N-1) intermediate points.
 */

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
