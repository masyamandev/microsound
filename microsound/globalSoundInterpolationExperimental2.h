
// Experimental interpolation using quadratic function

#if INTERPOLATION_STRENGTH > 0

	#if INTERPOLATION_STRENGTH == 1
		#define INTERPOLATION_DIFF_MULTIPLIER	85
	#elif INTERPOLATION_STRENGTH == 2
		#define INTERPOLATION_DIFF_MULTIPLIER	26
	#elif INTERPOLATION_STRENGTH == 3
		#define INTERPOLATION_DIFF_MULTIPLIER	7
	#elif INTERPOLATION_STRENGTH == 4
		#define INTERPOLATION_DIFF_MULTIPLIER	2
	#endif

	uint8_t interpolationCounter;
	uint8_t interpolationPrevValue;
	int8_t interpolationPrevDiff;
//		int16_t prevDiff;

	uint16_t interpolationValue;
	int16_t interpolationDiff, interpolationDiffDiff;


	// Quadratic interpolation with distortion
	inline uint8_t getNextInterpolatedSample() {
		interpolationCounter = (interpolationCounter + 1) & ((1 << INTERPOLATION_STRENGTH) - 1);

		if (!interpolationCounter) {

//				interpolationDiff = interpolationPrevDiff << 8 >> INTERPOLATION_STRENGTH;
//				uint8_t nextValue = INTERPOLATION_SOURCE_FUNCTION();
//				interpolationPrevDiff = nextValue - (interpolationValue >> 8) - interpolationPrevDiff;
////				prevValue = nextValue;
//				interpolationDiffDiff = interpolationPrevDiff * INTERPOLATION_DIFF_MULTIPLIER;
////				interpolationValue = nextValue << 8;
////				return nextValue;

			interpolationDiff = ((int16_t) interpolationPrevDiff) << 8 >> (INTERPOLATION_STRENGTH);
			uint8_t nextValue = readFromBuffer();
			interpolationPrevDiff = nextValue - interpolationPrevValue;
			interpolationPrevValue = nextValue;
			interpolationDiffDiff = interpolationPrevDiff * INTERPOLATION_DIFF_MULTIPLIER;
			interpolationValue = nextValue << 8;

//				interpolationDiff = ((int16_t) prevDiff) << 8 >> (INTERPOLATION_STRENGTH);
			return nextValue;
		}
		interpolationDiff += interpolationDiffDiff;
		interpolationValue += interpolationDiff;
		return interpolationValue >> 8;
	}

#else

	#define getNextInterpolatedSample 	readFromBuffer

#endif
