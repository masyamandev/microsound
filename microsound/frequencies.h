
#define SAMPLE_LENGTH 	32 // Number of samples per period, 2^n
#define SAMPLE_MASK 	(SAMPLE_LENGTH - 1)

#define freqStep(freq) ((uint16_t) (256L * freq * SAMPLE_LENGTH / MICROSOUND_FREQUENCY))

#define NOTE_C3 	0
#define NOTE_Db3 	1
#define NOTE_D3 	2
#define NOTE_Eb3 	3
#define NOTE_E3 	4
#define NOTE_F3 	5
#define NOTE_Gb3 	6
#define NOTE_G3 	7
#define NOTE_Ab3 	8
#define NOTE_A3 	9
#define NOTE_Bb3 	10
#define NOTE_B3 	11
#define NOTE_C4 	12
#define NOTE_Db4 	13
#define NOTE_D4 	14
#define NOTE_Eb4 	15
#define NOTE_E4 	16
#define NOTE_F4 	17
#define NOTE_Gb4 	18
#define NOTE_G4 	19
#define NOTE_Ab4 	20
#define NOTE_A4 	21
#define NOTE_Bb4 	22
#define NOTE_B4 	23
#define NOTE_C5 	24
#define NOTE_Db5 	25
#define NOTE_D5 	26
#define NOTE_Eb5 	27
#define NOTE_E5 	28
#define NOTE_F5 	29
#define NOTE_Gb5 	30
#define NOTE_G5 	31
#define NOTE_Ab5 	32
#define NOTE_A5 	33
#define NOTE_Bb5 	34
#define NOTE_B5 	35
#define NOTE_C6 	36

#define NOTE_ARRAY_SIZE		37
const uint16_t frequencies[NOTE_ARRAY_SIZE] = {
        freqStep(130.813), freqStep(138.591), freqStep(146.832), freqStep(155.563), freqStep(164.814), freqStep(174.614), freqStep(184.997), freqStep(195.998), freqStep(207.652), freqStep(220.000), freqStep(233.082), freqStep(246.942),
        freqStep(261.626), freqStep(277.183), freqStep(293.665), freqStep(311.127), freqStep(329.628), freqStep(349.228), freqStep(369.994), freqStep(391.995), freqStep(415.305), freqStep(440.000), freqStep(466.164), freqStep(493.883),
        freqStep(523.251), freqStep(554.365), freqStep(587.330), freqStep(622.254), freqStep(659.255), freqStep(698.456), freqStep(739.989), freqStep(783.991), freqStep(830.609), freqStep(880.000), freqStep(932.328), freqStep(987.767),
        freqStep(1046.502)};

#define frequency(note)		(frequencies[note])
