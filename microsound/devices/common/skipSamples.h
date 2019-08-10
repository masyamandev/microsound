#if (MICROSOUND_FREQUENCY_DIVIDER > 1) && ((!defined INTERPOLATION_STRENGTH) || (INTERPOLATION_STRENGTH == 0))
	static uint8_t microsampleSampleSkipCounter;
	if ((microsampleSampleSkipCounter++) & (MICROSOUND_FREQUENCY_DIVIDER - 1)) {
		return;
	}
#endif
