#ifndef SEMIRANDOM_DEFINED
#define SEMIRANDOM_DEFINED

/*
 * Fast semirandom values generator. Used for noise generation.
 */

uint8_t semirandomA, semirandomB, semirandomC, semirandomValue;

inline void nextSemirandom() {
	semirandomA++;
	semirandomB = semirandomB ^ semirandomValue ^ semirandomA;
	semirandomC = semirandomC + semirandomB;
	semirandomValue = semirandomValue + ((semirandomC >> 1) ^ semirandomB);
}

#endif
