#ifndef setChannelWave

#define setChannelWave(waveTable, note)							\
		channel->waveStep = pgm_read_word(&frequencies[note]);	\
		channel->waveForm = waveTable;


#define setChannelVolume(volumeTable, ticksPerSample)					\
		channel->volumeForm = volumeTable;						\
		channel->volumeFormLength = sizeof(volumeTable) - 1;	\
		channel->volumeTicksPerSample = ticksPerSample;					\
		channel->volumeTicksCounter = ticksPerSample;

#endif
