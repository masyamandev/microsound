#ifndef setChannelWave

#define setChannelWave(waveTable, note)							\
		channel->waveStep = pgm_read_word(&frequencies[note]);	\
		channel->waveForm = waveTable;							\
		channel->waveSample = 0; // Can be omit if declick is disabled


#define setChannelVolumeWithLength(volumeTable, tableLength, ticksPerSample)	\
		channel->volumeForm = volumeTable;										\
		channel->volumeFormLength = tableLength;								\
		channel->volumeTicksPerSample = ticksPerSample;							\
		channel->volumeTicksCounter = ticksPerSample;

#define setChannelVolume(volumeTable, ticksPerSample)	\
		setChannelVolumeWithLength(volumeTable, sizeof(volumeTable) - 1, ticksPerSample);

#endif
