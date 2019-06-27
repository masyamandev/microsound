
#define PERC	0
#define HRMN	1
#define BASS	2
#define OVRD	3

const uint8_t ohSusannaSong[] PROGMEM = {
		DATA_TEMPO(480),
		DATA_INSTRUMENT(PERC, SAMPLE_PERCUSSION),
		DATA_INSTRUMENT(BASS, SAMPLE_BASS),
		DATA_INSTRUMENT(HRMN, SAMPLE_ACCORDION),
		DATA_INSTRUMENT(OVRD, SAMPLE_OVERDRIVE),
		DATA_VOLUME(PERC, 80),
		DATA_VOLUME(HRMN, 80),
		DATA_VOLUME(BASS, 32),
		DATA_VOLUME(OVRD, 64),


//		DATA_PLAY(PERC, PERCUSSION_HAT_H, 1),
//		DATA_PLAY(PERC, PERCUSSION_HAT_L, 1),
//		DATA_PLAY(PERC, PERCUSSION_BAR_H, 1),
//		DATA_PLAY(PERC, PERCUSSION_BAR_L, 1),
//		DATA_PLAY(PERC, PERCUSSION_HAT_H, 2),
//		DATA_PLAY(PERC, PERCUSSION_HAT_L, 2),
//		DATA_PLAY(PERC, PERCUSSION_BAR_H, 2),
//		DATA_PLAY(PERC, PERCUSSION_BAR_L, 2),
//		DATA_PLAY(PERC, PERCUSSION_HAT_H, 2),

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
		DATA_VOLUME(HRMN, 80),
		DATA_VOLUME(OVRD, 28),
		DATA_VOLUME(BASS, 56),
		DATA_WAIT(1),
		DATA_VOLUME(HRMN, 72),
		DATA_VOLUME(OVRD, 24),
		DATA_VOLUME(BASS, 48),
		DATA_WAIT(1),
		DATA_VOLUME(HRMN, 60),
		DATA_VOLUME(OVRD, 20),
		DATA_VOLUME(BASS, 40),
		DATA_WAIT(1),
		DATA_VOLUME(HRMN, 28),
		DATA_VOLUME(OVRD, 16),
		DATA_VOLUME(BASS, 32),
		DATA_WAIT(1),
		DATA_VOLUME(HRMN, 36),
		DATA_VOLUME(OVRD, 12),
		DATA_VOLUME(BASS, 24),
		DATA_WAIT(1),
		DATA_VOLUME(HRMN, 24),
		DATA_VOLUME(OVRD, 8),
		DATA_VOLUME(BASS, 16),
		DATA_WAIT(1),
		DATA_VOLUME(HRMN, 12),
		DATA_VOLUME(OVRD, 4),
		DATA_VOLUME(BASS, 8),
		DATA_WAIT(1),
		DATA_VOLUME(HRMN, 0),
		DATA_VOLUME(OVRD, 0),
		DATA_VOLUME(BASS, 0),
		DATA_WAIT(16),

		COMMAND_END
};



#undef PERC
#undef HRMN
#undef BASS
#undef OVRD

