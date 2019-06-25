#ifndef SEMIRANDOM_DEFINED
#define SEMIRANDOM_DEFINED


uint8_t semirandomA, semirandomB, semirandomC, semirandomValue;

inline void nextSemirandom() {
	semirandomA++;
	semirandomB = semirandomB ^ semirandomValue ^ semirandomA;
	semirandomC = semirandomC + semirandomB;
	semirandomValue = semirandomValue + ((semirandomC >> 1) ^ semirandomB);
}

#endif
