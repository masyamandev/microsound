
// Can be useful for attiny MCUs which does not have hardware multiplication

#ifndef INLINE_MULTIPLICATION_SIGNED_UNSIGNED
#define INLINE_MULTIPLICATION_SIGNED_UNSIGNED inline /* inline by default */
#endif
#ifndef INLINE_MULTIPLICATION_UNSIGNED_UNSIGNED
#define INLINE_MULTIPLICATION_UNSIGNED_UNSIGNED inline /* inline by default */
#endif

#if !defined SPEED_OPTIMIZED_MULTIPLICATION

	// Use hardware multiplication if possible

	#define mulSignedUnsigned(ms, mu)	((ms) * (mu))
	#define mulUnsigned8bits(a, b)		((uint8_t) (((a) * (b)) >> 8))

#elif !defined SIMPLIFIED_MULTIPLICATION

	// Use software speed optimized multiplication

	// LIMIT: ms = [-127..127], mu = [0..255]
	INLINE_MULTIPLICATION_SIGNED_UNSIGNED
	int16_t mulSignedUnsigned(int8_t ms, uint8_t mu) {
		// This implementation returns 16 bits result in 40ck
		// No need to use it for atmega MCUs or others which has hardware multiplication
		int16_t result;
		asm(
				"clr %B[result]" "\n\r"
				"mov %A[result], %[muls]" "\n\r"
				"sbrc %A[result], 7" "\n\r"
				"neg %A[result]" "\n\r"

				"lsr %A[result]" "\n\r"

				"brcc .+2" "\n\r"
				"add %B[result], %[mulu]" "\n\r"
				"ror %B[result]" "\n\r"
				"ror %A[result]" "\n\r"

				"brcc .+2" "\n\r"
				"add %B[result], %[mulu]" "\n\r"
				"ror %B[result]" "\n\r"
				"ror %A[result]" "\n\r"

				"brcc .+2" "\n\r"
				"add %B[result], %[mulu]" "\n\r"
				"ror %B[result]" "\n\r"
				"ror %A[result]" "\n\r"

				"brcc .+2" "\n\r"
				"add %B[result], %[mulu]" "\n\r"
				"ror %B[result]" "\n\r"
				"ror %A[result]" "\n\r"

				"brcc .+2" "\n\r"
				"add %B[result], %[mulu]" "\n\r"
				"ror %B[result]" "\n\r"
				"ror %A[result]" "\n\r"

				"brcc .+2" "\n\r"
				"add %B[result], %[mulu]" "\n\r"
				"ror %B[result]" "\n\r"
				"ror %A[result]" "\n\r"

				"brcc .+2" "\n\r"
				"add %B[result], %[mulu]" "\n\r"
				"ror %B[result]" "\n\r"
				"ror %A[result]" "\n\r"

				// Bit7 is 0. This optimized block will cause issue on muls = -128. To avoid this use block similar to above.
				"lsr %B[result]" "\n\r"
				"ror %A[result]" "\n\r"

				// Invert result sign
				"tst %[muls]" "\n\r"
				"brlt .+6" "\n\r"
				"com %B[result]" "\n\r"
				"neg %A[result]" "\n\r"
				"sbci %B[result], 255" "\n\r"


				: [result] "=&d" (result)
				: [muls] "r" (ms), [mulu] "r" (mu)
				  );
		return result;
	}

	INLINE_MULTIPLICATION_UNSIGNED_UNSIGNED uint16_t mulUnsigned(uint8_t a, uint8_t b) {
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

				: [result] "=&r" (result)
				: [muls] "r" (a), [mulu] "r" (b)
				  );
		return result;
	}

	inline uint8_t mulUnsigned8bits(uint8_t a, uint8_t b) {
		return mulUnsigned(a, b) >> 8;
	}

#else

	// Use simplified multiplication with limitations. It's slightly faster and has requires less program memory but gives worse sound quality.
	// Also it requires instruments to have volume 127 or less.

	// LIMIT: return only high byte of multiplication result, low byte is 0
	INLINE_MULTIPLICATION_SIGNED_UNSIGNED
	int16_t mulSignedUnsigned(int8_t ms, uint8_t mu) {
		// This implementation returns high byte of 16 bits result in 31ck
		// No need to use it for atmega MCUs or others which has hardware multiplication
		int16_t result;
		asm(

				// invert sign if needed
				"mov __tmp_reg__, %[muls]" "\n\r"
				"sbrc __tmp_reg__, 7" "\n\r"
				"neg __tmp_reg__" "\n\r"

				// multiply unsigned
				"clr %A[result]" "\n\r"
				"clr %B[result]" "\n\r"

				"sbrc %[mulu], 0" "\n\r"
				"add %B[result], __tmp_reg__" "\n\r"
				"lsr %B[result]" "\n\r"
				"sbrc %[mulu], 1" "\n\r"
				"add %B[result], __tmp_reg__" "\n\r"
				"lsr %B[result]" "\n\r"
				"sbrc %[mulu], 2" "\n\r"
				"add %B[result], __tmp_reg__" "\n\r"
				"lsr %B[result]" "\n\r"
				"sbrc %[mulu], 3" "\n\r"
				"add %B[result], __tmp_reg__" "\n\r"
				"lsr %B[result]" "\n\r"
				"sbrc %[mulu], 4" "\n\r"
				"add %B[result], __tmp_reg__" "\n\r"
				"lsr %B[result]" "\n\r"
				"sbrc %[mulu], 5" "\n\r"
				"add %B[result], __tmp_reg__" "\n\r"
				"lsr %B[result]" "\n\r"
				"sbrc %[mulu], 6" "\n\r"
				"add %B[result], __tmp_reg__" "\n\r"
				"lsr %B[result]" "\n\r"
				"sbrc %[mulu], 7" "\n\r"
				"add %B[result], __tmp_reg__" "\n\r"
				"lsr %B[result]" "\n\r"

				// invert result sign
				"sbrc %[muls], 7" "\n\r"
				"neg %B[result]" "\n\r"


				: [result] "=&d" (result)
				: [muls] "r" (ms), [mulu] "r" (mu)
				  );
		return result;
	}

	// LIMIT: a = [0..255], b = [0..127]
	INLINE_MULTIPLICATION_UNSIGNED_UNSIGNED
	uint8_t mulUnsigned8bits(uint8_t a, uint8_t b) {
		// This is a simplified implementation returns high byte 8 bits result in 25ck
		// No need to use it for atmega MCUs or others which has hardware multiplication
		uint8_t result;
		asm(
				"clr %[result]" "\n\r"

				"sbrc %[mulu], 0" "\n\r"
				"add %[result], %[muls]" "\n\r"
				"lsr %[result]" "\n\r"
				"sbrc %[mulu], 1" "\n\r"
				"add %[result],%[muls]" "\n\r"
				"lsr %[result]" "\n\r"
				"sbrc %[mulu], 2" "\n\r"
				"add %[result], %[muls]" "\n\r"
				"lsr %[result]" "\n\r"
				"sbrc %[mulu], 3" "\n\r"
				"add %[result], %[muls]" "\n\r"
				"lsr %[result]" "\n\r"
				"sbrc %[mulu], 4" "\n\r"
				"add %[result], %[muls]" "\n\r"
				"lsr %[result]" "\n\r"
				"sbrc %[mulu], 5" "\n\r"
				"add %[result], %[muls]" "\n\r"
				"lsr %[result]" "\n\r"
				"sbrc %[mulu], 6" "\n\r"
				"add %[result], %[muls]" "\n\r"
				"lsr %[result]" "\n\r"
				"sbrc %[mulu], 7" "\n\r"
				"add %[result], %[muls]" "\n\r"
				"lsr %[result]" "\n\r"

				: [result] "=&r" (result)
				: [muls] "r" (b), [mulu] "r" (a)
				  );
		return result;

	}

#endif
