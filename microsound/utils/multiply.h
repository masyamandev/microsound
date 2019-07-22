
// Can be useful for attiny MCUs which does not have hardware multiplication

#ifdef SPEED_OPTIMIZED_MULTIPLICATION

inline int16_t mulSignedUnsigned(int8_t ms, uint8_t mu) {
	// TODO try to optimize
	// This implementation returns 16 bits result in 43ck
	// No need to use it for atmega MCUs or others which has hardware multiplication
	int16_t result;
	asm(

			// invert sign if needed
			"mov __tmp_reg__, %[muls]" "\n\r"
			"sbrc __tmp_reg__, 7" "\n\r"
			"neg __tmp_reg__" "\n\r"

			// multiply unsigned
			"clr %B[result]" "\n\r"
			"mov %A[result], %[mulu]" "\n\r"

			"lsr %A[result]" "\n\r"

			"brcc .+2" "\n\r"
			"add %B[result], __tmp_reg__" "\n\r"
			"ror %B[result]" "\n\r"
			"ror %A[result]" "\n\r"

			"brcc .+2" "\n\r"
			"add %B[result], __tmp_reg__" "\n\r"
			"ror %B[result]" "\n\r"
			"ror %A[result]" "\n\r"

			"brcc .+2" "\n\r"
			"add %B[result], __tmp_reg__" "\n\r"
			"ror %B[result]" "\n\r"
			"ror %A[result]" "\n\r"

			"brcc .+2" "\n\r"
			"add %B[result], __tmp_reg__" "\n\r"
			"ror %B[result]" "\n\r"
			"ror %A[result]" "\n\r"

			"brcc .+2" "\n\r"
			"add %B[result], __tmp_reg__" "\n\r"
			"ror %B[result]" "\n\r"
			"ror %A[result]" "\n\r"

			"brcc .+2" "\n\r"
			"add %B[result], __tmp_reg__" "\n\r"
			"ror %B[result]" "\n\r"
			"ror %A[result]" "\n\r"

			"brcc .+2" "\n\r"
			"add %B[result], __tmp_reg__" "\n\r"
			"ror %B[result]" "\n\r"
			"ror %A[result]" "\n\r"

			"brcc .+2" "\n\r"
			"add %B[result], __tmp_reg__" "\n\r"
			"ror %B[result]" "\n\r"
			"ror %A[result]" "\n\r"

			// invert result sign
			"cp __tmp_reg__, %[muls]" "\n\r"
			"breq .+6" "\n\r"
			"com %B[result]" "\n\r"
			"neg %A[result]" "\n\r"
			"sbci %B[result], 255" "\n\r"


			: [result] "+d" (result)
			: [muls] "r" (ms), [mulu] "r" (mu)
			  );
	return result;
}

inline uint16_t mulUnsigned(uint8_t a, uint8_t b) {
	// This implementation returns 16 bits result in 35ck
	// No need to use it for atmega MCUs or others which has hardware multiplication
	uint16_t result;
	asm(
			"clr %B[result]" "\n\r"
			"mov %A[result], %[mulu]" "\n\r"

			"lsr %A[result]" "\n\r"

			"brcc .+2" "\n\r"
			"add %B[result], %[muls]" "\n\r"
			"ror %B[result]" "\n\r"
			"ror %A[result]" "\n\r"

			"brcc .+2" "\n\r"
			"add %B[result], %[muls]" "\n\r"
			"ror %B[result]" "\n\r"
			"ror %A[result]" "\n\r"

			"brcc .+2" "\n\r"
			"add %B[result], %[muls]" "\n\r"
			"ror %B[result]" "\n\r"
			"ror %A[result]" "\n\r"

			"brcc .+2" "\n\r"
			"add %B[result], %[muls]" "\n\r"
			"ror %B[result]" "\n\r"
			"ror %A[result]" "\n\r"

			"brcc .+2" "\n\r"
			"add %B[result], %[muls]" "\n\r"
			"ror %B[result]" "\n\r"
			"ror %A[result]" "\n\r"

			"brcc .+2" "\n\r"
			"add %B[result], %[muls]" "\n\r"
			"ror %B[result]" "\n\r"
			"ror %A[result]" "\n\r"

			"brcc .+2" "\n\r"
			"add %B[result], %[muls]" "\n\r"
			"ror %B[result]" "\n\r"
			"ror %A[result]" "\n\r"

			"brcc .+2" "\n\r"
			"add %B[result], %[muls]" "\n\r"
			"ror %B[result]" "\n\r"
			"ror %A[result]" "\n\r"

			: [result] "+r" (result)
			: [muls] "r" (a), [mulu] "r" (b)
			  );
	return result;
}

inline uint8_t mulUnsigned8bits(uint8_t a, uint8_t b) {
	// This is a simplified implementation returns high byte 8 bits result in 24ck
	// No need to use it for atmega MCUs or others which has hardware multiplication
	uint8_t result;
	asm(
			"mov __tmp_reg__, %[muls]" "\n\r" // TODO rid off

			"clr %[result]" "\n\r"

			"sbrc %[mulu], 0" "\n\r"
			"add %[result], __tmp_reg__" "\n\r"
			"lsr %[result]" "\n\r"
			"sbrc %[mulu], 1" "\n\r"
			"add %[result],__tmp_reg__" "\n\r"
			"lsr %[result]" "\n\r"
			"sbrc %[mulu], 2" "\n\r"
			"add %[result], __tmp_reg__" "\n\r"
			"lsr %[result]" "\n\r"
			"sbrc %[mulu], 3" "\n\r"
			"add %[result], __tmp_reg__" "\n\r"
			"lsr %[result]" "\n\r"
			"sbrc %[mulu], 4" "\n\r"
			"add %[result], __tmp_reg__" "\n\r"
			"lsr %[result]" "\n\r"
			"sbrc %[mulu], 5" "\n\r"
			"add %[result], __tmp_reg__" "\n\r"
			"lsr %[result]" "\n\r"
			"sbrc %[mulu], 6" "\n\r"
			"add %[result], __tmp_reg__" "\n\r"
			"lsr %[result]" "\n\r"
			"sbrc %[mulu], 7" "\n\r"
			"add %[result], __tmp_reg__" "\n\r"

			: [result] "+r" (result)
			: [muls] "r" (a), [mulu] "r" (b)
			  );
	return result;
}

#else

#define mulSignedUnsigned(ms, mu)	((ms) * (mu))

#endif
