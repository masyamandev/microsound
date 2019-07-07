
/*!
 * Test tool for microsound library. Use it on http://wavepot.com/
 * https://github.com/masyamandev/microsound
 */



/*
 * Notes
 */

var NOTE_SILENCE = 0;
var NOTE_C1 = 1;
var NOTE_Db1 = 2;
var NOTE_D1 = 3;
var NOTE_Eb1 = 4;
var NOTE_E1 = 5;
var NOTE_F1 = 6;
var NOTE_Gb1 = 7;
var NOTE_G1 = 8;
var NOTE_Ab1 = 9;
var NOTE_A1 = 10;
var NOTE_Bb1 = 11;
var NOTE_B1 = 12;
var NOTE_C2 = 13;
var NOTE_Db2 = 14;
var NOTE_D2 = 15;
var NOTE_Eb2 = 16;
var NOTE_E2 = 17;
var NOTE_F2 = 18;
var NOTE_Gb2 = 19;
var NOTE_G2 = 20;
var NOTE_Ab2 = 21;
var NOTE_A2 = 22;
var NOTE_Bb2 = 23;
var NOTE_B2 = 24;
var NOTE_C3 = 25;
var NOTE_Db3 = 26;
var NOTE_D3 = 27;
var NOTE_Eb3 = 28;
var NOTE_E3 = 29;
var NOTE_F3 = 30;
var NOTE_Gb3 = 31;
var NOTE_G3 = 32;
var NOTE_Ab3 = 33;
var NOTE_A3 = 34;
var NOTE_Bb3 = 35;
var NOTE_B3 = 36;
var NOTE_C4 = 37;
var NOTE_Db4 = 38;
var NOTE_D4 = 39;
var NOTE_Eb4 = 40;
var NOTE_E4 = 41;
var NOTE_F4 = 42;
var NOTE_Gb4 = 43;
var NOTE_G4 = 44;
var NOTE_Ab4 = 45;
var NOTE_A4 = 46;
var NOTE_Bb4 = 47;
var NOTE_B4 = 48;
var NOTE_C5 = 49;
var NOTE_Db5 = 50;
var NOTE_D5 = 51;
var NOTE_Eb5 = 52;
var NOTE_E5 = 53;
var NOTE_F5 = 54;
var NOTE_Gb5 = 55;
var NOTE_G5 = 56;
var NOTE_Ab5 = 57;
var NOTE_A5 = 58;
var NOTE_Bb5 = 59;
var NOTE_B5 = 60;
var NOTE_C6 = 61;

var frequencies = [
		    0,
        32.703, 34.648, 36.708, 38.891, 41.203, 43.654, 46.249, 48.999, 51.913, 55.000, 58.270, 61.735, 
        65.406, 69.296, 73.416, 77.782, 82.407, 87.307, 92.499, 97.999, 103.826, 110.000, 116.541, 123.471, 
        130.813, 138.591, 146.832, 155.563, 164.814, 174.614, 184.997, 195.998, 207.652, 220.000, 233.082, 246.942, 
        261.626, 277.183, 293.665, 311.127, 329.628, 349.228, 369.994, 391.995, 415.305, 440.000, 466.164, 493.883, 
        523.251, 554.365, 587.330, 622.254, 659.255, 698.456, 739.989, 783.991, 830.609, 880.000, 932.328, 987.767, 
        1046.502];

var OVERDRIVE_SHORT = 128;
var PERCUSSION_HAT_H = 0;
var PERCUSSION_HAT_L = 1;
var PERCUSSION_BAR_H = 2;
var PERCUSSION_BAR_L = 3;

/*
 * Data 
 */

var CHANNELS = 4;

var PERC = 0;
var BASS = 1;
var HRMN = 2;
var OVRD = 3;

var soundData = [		
		DATA_TEMPO(480),
		DATA_INSTRUMENT(PERC, SAMPLE_PERCUSSION),
		DATA_INSTRUMENT(BASS, SAMPLE_BASS),
		DATA_INSTRUMENT(HRMN, SAMPLE_HARMONICA),
		DATA_INSTRUMENT(OVRD, SAMPLE_OVERDRIVE),
		DATA_VOLUME(PERC, 80),
		DATA_VOLUME(HRMN, 64),
		DATA_VOLUME(BASS, 32),
		DATA_VOLUME(OVRD, 64),

		// DATA_PLAY(PERC, PERCUSSION_HAT_H, 1),
		// DATA_PLAY(PERC, PERCUSSION_HAT_L, 1),
		// DATA_PLAY(PERC, PERCUSSION_BAR_H, 1),
		// DATA_PLAY(PERC, PERCUSSION_BAR_L, 1),
		// DATA_PLAY(PERC, PERCUSSION_HAT_H, 2),
		// DATA_PLAY(PERC, PERCUSSION_HAT_L, 2),
		// DATA_PLAY(PERC, PERCUSSION_BAR_H, 2),
		// DATA_PLAY(PERC, PERCUSSION_BAR_L, 2),
		// DATA_PLAY(PERC, PERCUSSION_HAT_H, 2),
    // DATA_END(),

		DATA_PLAY(HRMN, NOTE_C4, 1),
		DATA_PLAY(HRMN, NOTE_D4, 0),
		DATA_PLAY(PERC, PERCUSSION_HAT_L, 1),

		DATA_PLAY(HRMN, NOTE_E4, 0),
		DATA_PLAY(BASS, NOTE_C2, 0),
		DATA_PLAY(PERC, PERCUSSION_BAR_L, 2),
		DATA_PLAY(HRMN, NOTE_G4, 0),
		DATA_PLAY(OVRD, NOTE_C3 | OVERDRIVE_SHORT, 0),
		DATA_PLAY(PERC, PERCUSSION_HAT_H, 2),
		DATA_PLAY(HRMN, NOTE_G4, 0),
		DATA_PLAY(OVRD, NOTE_C3, 0),
		DATA_PLAY(BASS, NOTE_E2, 0),
		DATA_PLAY(PERC, PERCUSSION_BAR_L, 3),
		DATA_PLAY(HRMN, NOTE_A4, 0),
		DATA_PLAY(PERC, PERCUSSION_HAT_L, 1),

		DATA_PLAY(HRMN, NOTE_G4, 0),
		DATA_PLAY(BASS, NOTE_C2, 0),
		DATA_PLAY(PERC, PERCUSSION_HAT_H, 2),
		DATA_PLAY(HRMN, NOTE_E4, 0),
		DATA_PLAY(OVRD, NOTE_C3 | OVERDRIVE_SHORT, 0),
		DATA_PLAY(PERC, PERCUSSION_BAR_L, 2),
		DATA_PLAY(HRMN, NOTE_C4, 0),
		DATA_PLAY(OVRD, NOTE_C3, 0),
		DATA_PLAY(BASS, NOTE_G1, 0),
		DATA_PLAY(PERC, PERCUSSION_BAR_H, 3),
		DATA_PLAY(HRMN, NOTE_D4, 1),

		DATA_PLAY(HRMN, NOTE_E4, 0),
		DATA_PLAY(BASS, NOTE_C2, 0),
		DATA_PLAY(PERC, PERCUSSION_HAT_L, 2),
		DATA_PLAY(HRMN, NOTE_E4, 0),
		DATA_PLAY(OVRD, NOTE_C3 | OVERDRIVE_SHORT, 0),
		DATA_PLAY(PERC, PERCUSSION_HAT_L, 2),
		DATA_PLAY(HRMN, NOTE_D4, 0),
		DATA_PLAY(OVRD, NOTE_C3, 0),
		DATA_PLAY(PERC, PERCUSSION_HAT_H, 2),
		DATA_PLAY(HRMN, NOTE_C4, 0),
		DATA_PLAY(OVRD, NOTE_G3 | OVERDRIVE_SHORT, 0),
		DATA_PLAY(PERC, PERCUSSION_HAT_L, 2),


		DATA_PLAY(HRMN, NOTE_D4, 0),
		DATA_PLAY(OVRD, NOTE_G3, 0), // check this
		DATA_PLAY(BASS, NOTE_G2, 0),
		DATA_PLAY(PERC, PERCUSSION_BAR_H, 2),
		DATA_PLAY(PERC, PERCUSSION_HAT_L, 2),
		DATA_PLAY(PERC, PERCUSSION_BAR_H, 2),
		DATA_PLAY(HRMN, NOTE_C4, 1),
		DATA_PLAY(HRMN, NOTE_D4, 0),
		DATA_PLAY(PERC, PERCUSSION_HAT_L, 1),

		DATA_PLAY(HRMN, NOTE_E4, 0),
		DATA_PLAY(BASS, NOTE_C2, 0),
		DATA_PLAY(PERC, PERCUSSION_HAT_H, 2),
		DATA_PLAY(HRMN, NOTE_G4, 0),
		DATA_PLAY(OVRD, NOTE_C3 | OVERDRIVE_SHORT, 0),
		DATA_PLAY(PERC, PERCUSSION_HAT_L, 2),
		DATA_PLAY(HRMN, NOTE_G4, 0),
		DATA_PLAY(OVRD, NOTE_C3, 0),
		DATA_PLAY(BASS, NOTE_E2, 0),
		DATA_PLAY(PERC, PERCUSSION_BAR_H, 3),
		DATA_PLAY(HRMN, NOTE_A4, 0),
		DATA_PLAY(PERC, PERCUSSION_HAT_L, 1),

		DATA_PLAY(HRMN, NOTE_G4, 0),
		DATA_PLAY(BASS, NOTE_C2, 0),
		DATA_PLAY(PERC, PERCUSSION_HAT_H, 2),
		DATA_PLAY(HRMN, NOTE_E4, 0),
		DATA_PLAY(OVRD, NOTE_C3 | OVERDRIVE_SHORT, 0),
		DATA_PLAY(PERC, PERCUSSION_HAT_L, 2),
		DATA_PLAY(HRMN, NOTE_C4, 0),
		DATA_PLAY(OVRD, NOTE_C3, 0),
		DATA_PLAY(BASS, NOTE_G1, 0),
		DATA_PLAY(PERC, PERCUSSION_HAT_L, 3),
		DATA_PLAY(HRMN, NOTE_D4, 0),
		DATA_PLAY(PERC, PERCUSSION_HAT_L, 1),

		DATA_PLAY(HRMN, NOTE_E4, 0),
		DATA_PLAY(OVRD, NOTE_G3 | OVERDRIVE_SHORT, 0),
		DATA_PLAY(BASS, NOTE_C2, 0),
		DATA_PLAY(PERC, PERCUSSION_BAR_L, 2),
		DATA_PLAY(HRMN, NOTE_E4, 0),
		DATA_PLAY(OVRD, NOTE_G3 | OVERDRIVE_SHORT, 0),
		DATA_PLAY(BASS, NOTE_C2, 0),
		DATA_PLAY(PERC, PERCUSSION_HAT_L, 2),
		DATA_PLAY(HRMN, NOTE_D4, 0),
		DATA_PLAY(OVRD, NOTE_C3 | OVERDRIVE_SHORT, 0),
		DATA_PLAY(BASS, NOTE_A1, 0),
		DATA_PLAY(PERC, PERCUSSION_BAR_H, 2),
		DATA_PLAY(HRMN, NOTE_D4, 0),
		DATA_PLAY(OVRD, NOTE_C3 | OVERDRIVE_SHORT, 0),
		DATA_PLAY(BASS, NOTE_G1, 0),
		DATA_PLAY(PERC, PERCUSSION_HAT_L, 2),

		DATA_PLAY(HRMN, NOTE_C4, 0),
		DATA_PLAY(OVRD, NOTE_C3, 0),
		DATA_PLAY(BASS, NOTE_C2, 0),
		DATA_PLAY(PERC, PERCUSSION_BAR_H, 2),
		DATA_PLAY(BASS, NOTE_G2, 0),
		DATA_PLAY(PERC, PERCUSSION_HAT_L, 2),
		DATA_PLAY(BASS, NOTE_C3, 0),
		DATA_PLAY(PERC, PERCUSSION_HAT_H, 6),


		DATA_TEMPO(480 * 4),
		DATA_VOLUME(HRMN, 56),
		DATA_VOLUME(OVRD, 28),
		DATA_VOLUME(BASS, 56),
		DATA_WAIT(1),
		DATA_VOLUME(HRMN, 56),
		DATA_VOLUME(OVRD, 24),
		DATA_VOLUME(BASS, 48),
		DATA_WAIT(1),
		DATA_VOLUME(HRMN, 40),
		DATA_VOLUME(OVRD, 20),
		DATA_VOLUME(BASS, 40),
		DATA_WAIT(1),
		DATA_VOLUME(HRMN, 32),
		DATA_VOLUME(OVRD, 16),
		DATA_VOLUME(BASS, 32),
		DATA_WAIT(1),
		DATA_VOLUME(HRMN, 24),
		DATA_VOLUME(OVRD, 12),
		DATA_VOLUME(BASS, 24),
		DATA_WAIT(1),
		DATA_VOLUME(HRMN, 16),
		DATA_VOLUME(OVRD, 8),
		DATA_VOLUME(BASS, 16),
		DATA_WAIT(1),
		DATA_VOLUME(HRMN, 8),
		DATA_VOLUME(OVRD, 4),
		DATA_VOLUME(BASS, 8),
		DATA_WAIT(1),
		DATA_VOLUME(HRMN, 0),
		DATA_VOLUME(OVRD, 0),
		DATA_VOLUME(BASS, 0),
		DATA_WAIT(16),

		DATA_END()
];


/*
 * Instruments 
 */
var expNegTable = [
		255, 249, 244, 238, 233, 228, 223, 219, 214, 209, 205, 200, 196, 192, 188, 184,
		180, 176, 172, 168, 165, 161, 158, 154, 151, 148, 145, 142, 139, 136, 133, 130,
		127, 124, 122, 119, 116, 114, 111, 109, 107, 104, 102, 100, 98, 96, 94, 92,
		90, 88, 86, 84, 82, 80, 79, 77, 75, 74, 72, 71, 69, 68, 66, 65,
		63, 62, 61, 59, 58, 57, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46,
		45, 44, 43, 42, 41, 40, 39, 38, 37, 37, 36, 35, 34, 34, 33, 32,
		31, 31, 30, 29, 29, 28, 27, 27, 26, 26, 25, 25, 24, 24, 23, 23,
		22, 22, 21, 21, 20, 20, 19, 19, 18, 18, 18, 17, 17, 17, 16, 16,
		15, 15, 15, 14, 14, 14, 13, 13, 13, 13, 12, 12, 12, 12, 11, 11,
		11, 11, 10, 10, 10, 10, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8,
		7, 7, 7, 7, 7, 7, 6, 6, 6, 6, 6, 6, 6, 6, 5, 5,
		5, 5, 5, 5, 5, 5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
		3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		0];
		
		
var sinTable = [
		0, 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 39, 42, 45,
		48, 51, 54, 57, 59, 62, 65, 67, 70, 73, 75, 78, 80, 82, 85, 87,
		89, 91, 94, 96, 98, 100, 102, 103, 105, 107, 108, 110, 112, 113, 114, 116,
		117, 118, 119, 120, 121, 122, 123, 123, 124, 125, 125, 126, 126, 126, 126, 126,
		127, 126, 126, 126, 126, 126, 125, 125, 124, 123, 123, 122, 121, 120, 119, 118,
		117, 116, 114, 113, 112, 110, 108, 107, 105, 103, 102, 100, 98, 96, 94, 91,
		89, 87, 85, 82, 80, 78, 75, 73, 70, 67, 65, 62, 59, 57, 54, 51,
		48, 45, 42, 39, 36, 33, 30, 27, 24, 21, 18, 15, 12, 9, 6, 3,
		0, -3, -6, -9, -12, -15, -18, -21, -24, -27, -30, -33, -36, -39, -42, -45,
		-48, -51, -54, -57, -59, -62, -65, -67, -70, -73, -75, -78, -80, -82, -85, -87,
		-89, -91, -94, -96, -98, -100, -102, -103, -105, -107, -108, -110, -112, -113, -114, -116,
		-117, -118, -119, -120, -121, -122, -123, -123, -124, -125, -125, -126, -126, -126, -126, -126,
		-127, -126, -126, -126, -126, -126, -125, -125, -124, -123, -123, -122, -121, -120, -119, -118,
		-117, -116, -114, -113, -112, -110, -108, -107, -105, -103, -102, -100, -98, -96, -94, -91,
		-89, -87, -85, -82, -80, -78, -75, -73, -70, -67, -65, -62, -59, -57, -54, -51,
		-48, -45, -42, -39, -36, -33, -30, -27, -24, -21, -18, -15, -12, -9, -6, -3,
    0];
  
var pianoWaveTable = [
		0, 1, 3, 7, 12, 17, 24, 31, 38, 44, 50, 55, 58, 60, 60, 59,
		56, 52, 49, 45, 43, 42, 43, 45, 48, 50, 51, 52, 51, 48, 45, 40,
		36, 31, 26, 21, 16, 11, 6, 3, 0, -1, -3, -5, -8, -11, -15, -19,
		-24, -28, -31, -34, -35, -36, -34, -30, -26, -20, -15, -10, -6, -4, -2, 4,
		10, 17, 21, 25, 27, 29, 31, 32, 32, 31, 29, 27, 24, 23, 24, 26,
		30, 34, 38, 41, 44, 47, 50, 54, 58, 65, 72, 80, 88, 96, 104, 111,
		118, 122, 125, 127, 125, 123, 119, 115, 109, 104, 98, 92, 86, 80, 75, 70,
		67, 64, 61, 58, 55, 50, 46, 42, 38, 35, 33, 32, 32, 31, 30, 29,
		28, 25, 22, 18, 13, 7, 0, -5, -10, -13, -13, -12, -10, -8, -6, -5,
		-6, -8, -12, -17, -24, -31, -38, -44, -48, -50, -51, -50, -48, -45, -41, -37,
		-33, -30, -27, -26, -26, -28, -30, -33, -36, -40, -43, -46, -50, -53, -56, -59,
		-61, -64, -67, -70, -72, -73, -73, -72, -71, -68, -64, -60, -55, -50, -45, -41,
		-39, -38, -37, -37, -38, -39, -40, -41, -41, -42, -43, -43, -45, -47, -49, -53,
		-58, -62, -67, -71, -73, -74, -74, -71, -66, -59, -52, -44, -37, -31, -27, -24,
		-24, -26, -29, -34, -40, -46, -53, -59, -65, -68, -70, -69, -66, -62, -56, -50,
		-44, -39, -36, -33, -31, -29, -26, -22, -17, -12, -8, -5, -3, -2, -1, -1,
		0];

function SAMPLE_PIANO(channel, data, t) {
  console.log("play piano at " + t);
  channel.waveForm = pianoWaveTable;
  channel.frequency = frequencies[data];
  channel.volumeForm = expNegTable;
  channel.volumeTicksPerSample = 4;
} 


var bassGuitarWaveTable = [
		4, 19, 33, 47, 60, 72, 83, 92, 101, 108, 114, 119, 122, 125, 126, 127,
		126, 125, 123, 120, 116, 112, 108, 103, 98, 92, 87, 81, 75, 70, 64, 59,
		54, 49, 44, 40, 36, 32, 29, 25, 23, 20, 18, 16, 14, 13, 11, 10,
		8, 7, 6, 5, 3, 2, 1, 0, -1, -2, -4, -5, -6, -7, -9, -10,
		-11, -11, -12, -13, -13, -13, -13, -14, -14, -13, -13, -13, -12, -12, -12, -11,
		-11, -10, -9, -9, -8, -8, -7, -6, -5, -4, -4, -3, -2, -1, 0, 0,
		0, 1, 2, 2, 3, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5,
		4, 3, 3, 2, 1, 1, 0, 0, -1, -2, -3, -4, -4, -5, -6, -6,
		-7, -7, -7, -7, -7, -7, -7, -6, -6, -6, -5, -5, -4, -4, -3, -3,
		-2, -2, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, -1, -1, -1, -1, -2, -2, -2, -3, -3, -3, -3,
		-3, -3, -3, -3, -3, -2, -2, -2, -1, -1, -1, 0, 0, 0, -1, -1,
		-2, -3, -4, -5, -7, -8, -10, -12, -14, -16, -18, -20, -21, -23, -24, -25,
		-26, -26, -26, -26, -25, -24, -23, -22, -20, -19, -17, -16, -16, -16, -17, -18,
		-20, -23, -27, -31, -36, -42, -49, -56, -63, -70, -78, -85, -92, -98, -104, -108,
		-112, -115, -116, -116, -115, -113, -109, -103, -96, -88, -78, -67, -55, -41, -26, -11,
		4];

function SAMPLE_BASS(channel, data, t) {
  console.log("play bass at " + t);
  channel.waveForm = bassGuitarWaveTable;
  channel.frequency = frequencies[data];
  channel.volumeForm = expNegTable;
  channel.volumeTicksPerSample = 4;
} 


var harmonicaWaveTable = [
		0, -11, -29, -39, -39, -37, -37, -45, -53, -53, -49, -43, -34, -24, -22, -17,
		-6, 6, 22, 39, 55, 69, 72, 72, 76, 78, 83, 85, 81, 79, 74, 63,
		52, 47, 36, 17, 0, -19, -33, -40, -42, -48, -60, -75, -86, -94, -98, -95,
		-87, -75, -66, -55, -43, -27, -13, -2, 9, 18, 25, 31, 36, 40, 45, 48,
		44, 36, 26, 19, 13, 7, 3, -4, -14, -26, -40, -51, -56, -61, -72, -78,
		-77, -77, -77, -73, -67, -61, -57, -52, -42, -31, -20, -9, 1, 10, 17, 27,
		37, 44, 50, 52, 52, 50, 49, 50, 51, 45, 31, 14, 2, 0, -4, -13,
		-20, -24, -30, -32, -28, -26, -27, -22, -16, -10, 0, 14, 27, 30, 28, 26,
		27, 33, 34, 34, 40, 42, 36, 33, 39, 41, 32, 22, 12, 5, 1, -1,
		-1, -6, -13, -14, -15, -16, -16, -20, -24, -27, -26, -24, -19, -14, -12, -13,
		-11, -12, -14, -15, -18, -23, -30, -35, -36, -35, -39, -46, -49, -52, -57, -63,
		-68, -65, -56, -50, -50, -51, -41, -28, -18, -12, -8, -2, 2, 5, 13, 25,
		34, 37, 37, 35, 34, 35, 36, 30, 18, 7, 0, -7, -14, -18, -20, -26,
		-36, -44, -48, -48, -47, -44, -37, -32, -26, -17, -7, 5, 18, 32, 50, 70,
		91, 111, 127, 124, 106, 87, 70, 64, 58, 54, 59, 53, 35, 20, 12, 1,
		-2, 12, 21, 22, 22, 27, 33, 33, 35, 45, 46, 34, 24, 17, 7, 3,
		0];

var harmonicaVolumeTable = [
  16, 86, 142, 177, 199, 212, 220, 224, 225, 226, 225, 224, 222, 220, 218, 216,
];

function SAMPLE_HARMONICA(channel, data, t) {
  console.log("play harmonica at " + t);
  channel.waveForm = harmonicaWaveTable;
  channel.frequency = frequencies[data - 12];
  channel.volumeForm = harmonicaVolumeTable;
  channel.volumeTicksPerSample = 2;
} 


var overdrivenGuitarChordWaveTable = [
		0, 0, -5, -26, -47, -37, -23, -35, -51, -52, -58, -58, -51, -53, -74, -80,
		-74, -81, -93, -91, -84, -86, -93, -90, -82, -80, -85, -88, -87, -81, -66, -60,
		-63, -59, -49, -49, -55, -49, -37, -32, -22, -16, -17, -14, -6, -1, 5, 17,
		25, 49, 44, 35, 39, 49, 66, 77, 86, 94, 101, 107, 115, 124, 127, 120,
		105, 110, 124, 122, 100, 92, 98, 98, 96, 95, 71, 56, 65, 72, 49, 30,
		28, 24, 13, 9, 13, 12, 3, -15, -38, -48, -39, -27, -27, -35, -32, -30,
		-38, -41, -40, -46, -55, -57, -57, -57, -45, -37, -46, -58, -61, -55, -45, -37,
		-34, -26, -32, -35, -33, -30, -18, -13, -13, -9, -2, 3, 5, 4, 4, 3,
		-5, -2, 4, -1, -18, -11, 5, 2, -11, -14, -19, -14, 1, 12, -3, -12,
		-9, -12, -16, -11, -5, -8, -12, -10, -10, -14, -25, -31, -26, -18, -4, -8,
		-23, -19, -3, 0, -12, -21, -18, -15, -10, -8, -11, -8, -5, -16, -22, -10,
		1, 16, 5, -4, 0, 8, 19, 19, 17, 24, 35, 40, 42, 45, 47, 42,
		27, 29, 46, 52, 36, 33, 40, 36, 32, 35, 24, 17, 24, 23, 1, -7,
		4, 6, -1, -1, 5, 6, -1, -11, -17, -19, -12, 0, 7, 4, 7, 7,
		3, 7, 21, 23, 13, 7, 9, 17, 33, 41, 32, 21, 19, 19, 22, 25,
		23, 32, 30, 27, 23, 12, 19, 30, 36, 36, 30, 24, 22, 18, 13, 9,
		0];

var overdrivenGuitarChordVolumeTableShort = [
		255, 248, 244, 238, 233, 228, 223, 219, 214, 209, 205, 200, 196, 192, 128, 64,
		0];

function SAMPLE_OVERDRIVE(channel, data, t) {
  console.log("play overdriven guitar at " + t);
  channel.waveForm = overdrivenGuitarChordWaveTable;
  channel.frequency = frequencies[data % 64 - 12];
  if (data > 64) {
    channel.volumeForm = overdrivenGuitarChordVolumeTableShort;
    channel.volumeTicksPerSample = 1;
  } else {
    channel.volumeForm = expNegTable;
    channel.volumeTicksPerSample = 8;
  }
} 


var noiseVolumeH = [
    102, 89, 78, 69, 60, 53, 46, 41, 36, 31, 27, 24, 21, 18, 16, 14, 
    12, 11, 9, 8, 7, 6, 5, 5, 4, 3, 3, 3, 2, 2, 2, 1, 
		0];

var noiseVolumeM = [
    153, 129, 108, 91, 76, 64, 54, 45, 38, 32, 27, 22, 19, 16, 13, 11, 
    9, 8, 6, 5, 4, 4, 3, 2, 2, 2, 1, 1, 1, 1, 0, 0,
		0];
		
var noiseVolumeL = [
    51, 43, 36, 30, 25, 21, 18, 15, 12, 10, 9, 7, 6, 5, 4, 3, 
    3, 2, 2, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0];

var barVolumeH = [
		184, 176, 168, 161, 154, 148, 141, 135, 130, 124, 119, 114, 109, 104, 100, 96,
		92, 88, 84, 80, 77, 74, 70, 67, 65, 62, 59, 57, 54, 52, 50, 48,
		46, 44, 42, 40, 38, 37, 35, 33, 32, 31, 29, 28, 27, 26, 25, 24,
		23, 22, 21, 20, 19, 18, 17, 16, 16, 15, 14, 14, 13, 13, 12, 12,
//		11, 11, 10, 10, 9, 9, 8, 8, 8, 7, 7, 7, 6, 6, 6, 6,
//		5, 5, 5, 5, 4, 4, 4, 4, 4, 3, 3, 3, 3, 3, 3, 3,
//		2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1,
//		1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
		0
];

var barVolumeL = [ 
		/*184, 176, 168, 161, 154, 148, 141, 135,*/ 130, 124, 119, 114, 109, 104, 100, 96,
		92, 88, 84, 80, 77, 74, 70, 67, 65, 62, 59, 57, 54, 52, 50, 48,
		46, 44, 42, 40, 38, 37, 35, 33, 32, 31, 29, 28, 27, 26, 25, 24,
		23, 22, 21, 20, 19, 18, 17, 16, 16, 15, 14, 14, 13, 13, 12, 12,
//		11, 11, 10, 10, 9, 9, 8, 8, 8, 7, 7, 7, 6, 6, 6, 6,
//		5, 5, 5, 5, 4, 4, 4, 4, 4, 3, 3, 3, 3, 3, 3, 3,
//		2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1,
//		1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
		0
];

function SAMPLE_PERCUSSION(channel, data, t) {
  console.log("play percussion at " + t);
  
  noiseStart = t;
  noiseVolume = channel.volume;
  
	if (data == PERCUSSION_BAR_H) {
		noiseVolumeForm = noiseVolumeM;
    channel.waveForm = sinTable;
    channel.frequency = 55;
    channel.volumeForm = barVolumeH;
    channel.volumeTicksPerSample = 2;
	} else if (data == PERCUSSION_BAR_L) {
		noiseVolumeForm = noiseVolumeL;
    channel.waveForm = sinTable;
    channel.frequency = 55;
    channel.volumeForm = barVolumeL;
    channel.volumeTicksPerSample = 1;
	} else if (data == PERCUSSION_HAT_H) {
		noiseVolumeForm = noiseVolumeH;
		channel.frequency = 0;
	} else {
		noiseVolumeForm = noiseVolumeL;
		channel.frequency = 0;
	}
} 





/*
 * Engine 
 */

var channels = [];

var dataIndex = 0;
var nextCommandTime = 0;
var beatTime = 60;


var noiseStart = 999;
var noiseVolumeForm = [0];
var noiseVolume = 0;

function rand() {
  return Math.random() * 2 - 1;
}


function playNote(waveSample, t) {
  // waveForm, frequency, volumeForm, volumeTicksPerSample, volume
  var waveIndex = Math.floor(t * waveSample.frequency * 256) % 256;
  var volumeIndex = Math.floor(Math.min(t / 0.004 / waveSample.volumeTicksPerSample, waveSample.volumeForm.length - 1));
  return waveSample.waveForm[waveIndex] * waveSample.volumeForm[volumeIndex] * waveSample.volume / 128 / 256 / 256;
}


function clear() {
  dataIndex = 0;
  nextCommandTime = -1;
  beatTime = 60;
  
  noiseStart = 999;
  noiseVolumeForm = [0];
  noiseVolume = 0;
  
  for (var i = 0; i < CHANNELS; i++) {
    channels[i] = {
        waveForm: sinTable,
        frequency: 0, 
        volumeForm: expNegTable,
        volumeTicksPerSample: 4,
        volume: 0,
        startTime: 0
    };
  }
}

function play(t) {
  
  while (t >= nextCommandTime) {
    soundData[dataIndex](t);
    dataIndex++;
  }

  var res = 0;
  
  for (var i = 0; i < channels.length; i++) {
    res += playNote(channels[i], t - channels[i].startTime);
  }
  
  var noiseVolIndex = Math.floor((t - noiseStart) / 0.004);
  if (noiseVolIndex < noiseVolumeForm.length) {
    res += rand() * noiseVolumeForm[noiseVolIndex] * noiseVolume / 256 / 256;
  }
  
  return res;
}


function dsp(t) {
  
  if (t < 0.001) {
    clear();
    return 0;
  }
  
  return play(t);
}





/*
 * Commands
 */
 
function DATA_TEMPO(bpm) {
  return function(t) {
    beatTime = 60 / bpm;
    console.log("set tempo to " + beatTime);
  };
}

function DATA_INSTRUMENT(channelId, sample) {
  return function(t) {
    console.log("set instrument for " + channelId + " at " + t);
    channels[channelId].instrument = sample;
  };
}

function DATA_VOLUME(channelId, volume) {
  return function(t) {
    console.log("set volume for " + channelId + " to " + volume + " at " + t);
    channels[channelId].volume = volume;
  };
}

function DATA_PLAY(channelId, data, waitBeats) {
  return function(t) {
    console.log("new note for " + channelId + " at " + t);
    channels[channelId].instrument(channels[channelId], data, t);
    channels[channelId].startTime = t;
    nextCommandTime += waitBeats * beatTime;
    console.log("next command at " + nextCommandTime);
  };
}


function DATA_WAIT(waitBeats) {
  return function(t) {
    nextCommandTime += waitBeats * beatTime;
    console.log("next command at " + nextCommandTime);
  };
}

function DATA_END() {
  return function(t) {
    nextCommandTime = t;
    dataIndex = -1;
    console.log("end at " + t);
  };
}

