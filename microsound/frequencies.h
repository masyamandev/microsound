
#define SAMPLE_LENGTH 	32 // Number of samples per period, 2^n
#define SAMPLE_MASK 	(SAMPLE_LENGTH - 1)

#define freqStep(freq) ((uint16_t) (256L * freq * SAMPLE_LENGTH / MICROSOUND_FREQUENCY))

#define FREQ_C3 	freqStep(130.81)
#define FREQ_Db3 	freqStep(138.59)
#define FREQ_D3 	freqStep(146.83)
#define FREQ_Eb3 	freqStep(155.56)
#define FREQ_E3 	freqStep(164.81)
#define FREQ_F3 	freqStep(174.61)
#define FREQ_Gb3 	freqStep(185.00)
#define FREQ_G3 	freqStep(196.00)
#define FREQ_Ab3 	freqStep(207.65)
#define FREQ_A3 	freqStep(220.00)
#define FREQ_Bb3 	freqStep(233.08)
#define FREQ_B3 	freqStep(246.94)
#define FREQ_C4 	freqStep(261.63)
#define FREQ_Db4 	freqStep(277.18)
#define FREQ_D4 	freqStep(293.66)
#define FREQ_Eb4 	freqStep(311.13)
#define FREQ_E4 	freqStep(329.63)
#define FREQ_F4 	freqStep(349.23)
#define FREQ_Gb4 	freqStep(369.99)
#define FREQ_G4 	freqStep(392.00)
#define FREQ_Ab4 	freqStep(415.30)
#define FREQ_A4 	freqStep(440.00)
#define FREQ_Bb4 	freqStep(466.16)
#define FREQ_B4 	freqStep(493.88)
#define FREQ_C5 	freqStep(523.25)
#define FREQ_Db5 	freqStep(554.37)
#define FREQ_D5 	freqStep(587.33)
#define FREQ_Eb5 	freqStep(622.25)
#define FREQ_E5 	freqStep(659.25)
#define FREQ_F5 	freqStep(698.46)
#define FREQ_Gb5 	freqStep(739.99)
#define FREQ_G5 	freqStep(783.99)
#define FREQ_Ab5 	freqStep(830.61)
#define FREQ_A5 	freqStep(880.00)
#define FREQ_Bb5 	freqStep(932.33)
#define FREQ_B5 	freqStep(987.77)
#define FREQ_C6 	freqStep(1046.50)

#define FREQ_ARRAY_SIZE		37
const uint16_t frequencies[FREQ_ARRAY_SIZE] = {
		FREQ_C3, FREQ_Db3, FREQ_D3, FREQ_Eb3, FREQ_E3, FREQ_F3, FREQ_Gb3, FREQ_G3, FREQ_Ab3, FREQ_A3, FREQ_Bb3, FREQ_B3,
		FREQ_C4, FREQ_Db4, FREQ_D4, FREQ_Eb4, FREQ_E4, FREQ_F4, FREQ_Gb4, FREQ_G4, FREQ_Ab4, FREQ_A4, FREQ_Bb4, FREQ_B4,
		FREQ_C5, FREQ_Db5, FREQ_D5, FREQ_Eb5, FREQ_E5, FREQ_F5, FREQ_Gb5, FREQ_G5, FREQ_Ab5, FREQ_A5, FREQ_Bb5, FREQ_B5,
		FREQ_C6};
