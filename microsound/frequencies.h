
#define SAMPLE_LENGTH 	256 // Number of samples per period, 2^n
#define SAMPLE_MASK 	(SAMPLE_LENGTH - 1)

#define freqStep(freq) ((uint16_t) (256L * freq * SAMPLE_LENGTH / MICROSOUND_FREQUENCY))

#define NOTE_C1 	0
#define NOTE_Db1 	1
#define NOTE_D1 	2
#define NOTE_Eb1 	3
#define NOTE_E1 	4
#define NOTE_F1 	5
#define NOTE_Gb1 	6
#define NOTE_G1 	7
#define NOTE_Ab1 	8
#define NOTE_A1 	9
#define NOTE_Bb1 	10
#define NOTE_B1 	11
#define NOTE_C2 	12
#define NOTE_Db2 	13
#define NOTE_D2 	14
#define NOTE_Eb2 	15
#define NOTE_E2 	16
#define NOTE_F2 	17
#define NOTE_Gb2 	18
#define NOTE_G2 	19
#define NOTE_Ab2 	20
#define NOTE_A2 	21
#define NOTE_Bb2 	22
#define NOTE_B2 	23
#define NOTE_C3 	24
#define NOTE_Db3 	25
#define NOTE_D3 	26
#define NOTE_Eb3 	27
#define NOTE_E3 	28
#define NOTE_F3 	29
#define NOTE_Gb3 	30
#define NOTE_G3 	31
#define NOTE_Ab3 	32
#define NOTE_A3 	33
#define NOTE_Bb3 	34
#define NOTE_B3 	35
#define NOTE_C4 	36
#define NOTE_Db4 	37
#define NOTE_D4 	38
#define NOTE_Eb4 	39
#define NOTE_E4 	40
#define NOTE_F4 	41
#define NOTE_Gb4 	42
#define NOTE_G4 	43
#define NOTE_Ab4 	44
#define NOTE_A4 	45
#define NOTE_Bb4 	46
#define NOTE_B4 	47
#define NOTE_C5 	48
#define NOTE_Db5 	49
#define NOTE_D5 	50
#define NOTE_Eb5 	51
#define NOTE_E5 	52
#define NOTE_F5 	53
#define NOTE_Gb5 	54
#define NOTE_G5 	55
#define NOTE_Ab5 	56
#define NOTE_A5 	57
#define NOTE_Bb5 	58
#define NOTE_B5 	59
#define NOTE_C6 	60

#define NOTE_ARRAY_SIZE		61
const uint16_t frequencies[NOTE_ARRAY_SIZE] = {
        freqStep(32.703), freqStep(34.648), freqStep(36.708), freqStep(38.891), freqStep(41.203), freqStep(43.654), freqStep(46.249), freqStep(48.999), freqStep(51.913), freqStep(55.000), freqStep(58.270), freqStep(61.735),
        freqStep(65.406), freqStep(69.296), freqStep(73.416), freqStep(77.782), freqStep(82.407), freqStep(87.307), freqStep(92.499), freqStep(97.999), freqStep(103.826), freqStep(110.000), freqStep(116.541), freqStep(123.471),
        freqStep(130.813), freqStep(138.591), freqStep(146.832), freqStep(155.563), freqStep(164.814), freqStep(174.614), freqStep(184.997), freqStep(195.998), freqStep(207.652), freqStep(220.000), freqStep(233.082), freqStep(246.942),
        freqStep(261.626), freqStep(277.183), freqStep(293.665), freqStep(311.127), freqStep(329.628), freqStep(349.228), freqStep(369.994), freqStep(391.995), freqStep(415.305), freqStep(440.000), freqStep(466.164), freqStep(493.883),
        freqStep(523.251), freqStep(554.365), freqStep(587.330), freqStep(622.254), freqStep(659.255), freqStep(698.456), freqStep(739.989), freqStep(783.991), freqStep(830.609), freqStep(880.000), freqStep(932.328), freqStep(987.767),
        freqStep(1046.502)};

#define frequency(note)		(frequencies[note])
