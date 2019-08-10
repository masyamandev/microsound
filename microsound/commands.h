#ifndef MICROMUSIC_COMMANDS_INIT
#define MICROMUSIC_COMMANDS_INIT

/*
 * Commands for music data.
 * This command set supports up to 256 samples (instruments, SAMPLES_SIZE) and 16 channels (voices, CHANNELS_SIZE).
 * There is some limitation on wait length:
 * - COMMAND_PLAY handles 3 bits for wait time, up to 7 beats before next command;
 * - COMMAND_WAIT handles 6 bits for wait time, up to 63 beats before next command;
 * For longer pauses COMMAND_WAIT should be used multiple times.
 *
 * Author: Aleksandr Maksymenko aka masyaman
 */

#define COMMAND_PLAY		0b10000000	// 2 bytes:	[CWWWHHHH][NNNNNNNN]: C: command, HHHH: channelId, NNNNNNNN: note, WWW: wait
#define COMMAND_WAIT		0b01000000	// 1 byte:	[CCWWWWWW]: CC: command, WWWWWW: wait
#define COMMAND_VOLUME		0b00100000	// 2 bytes:	[CCC_HHHH][VVVVVVVV]: CCC: command, HHHH: channelId, VVVVVVVV: volume
#define COMMAND_INSTRUMENT	0b00010000	// 2 bytes:	[CCCCHHHH][SSSSSSSS]: CCCC: command, HHHH: channelId, SSSSSSSS: sample
#define COMMAND_TEMPO		0b00000001	// 3 bytes:	[CCCCCCCC][TTTTTTTT][TTTTTTTT]: C: command, T: bpm increment counter
#define COMMAND_END			0b00000000

#define DATA_PLAY(channel, note, wait)			(COMMAND_PLAY | ((wait & 0b00000111) << 4) | (channel)), (note)
#define DATA_WAIT(wait)							(COMMAND_WAIT | (wait & 0b00111111))
#define DATA_VOLUME(channel, vol)				(COMMAND_VOLUME | (channel)), (vol)
#define DATA_INSTRUMENT(channel, instrument)	(COMMAND_INSTRUMENT | (channel)), (instrument)
#define DATA_TEMPO(bpm)							(COMMAND_TEMPO), ((fromBpm(bpm) >> 8) & 0xFF), (fromBpm(bpm) & 0xFF)
#define DATA_END()								(COMMAND_END)

#endif
