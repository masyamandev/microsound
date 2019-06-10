
#ifndef MATH_HELPERS_INIT
#define MATH_HELPERS_INIT

const int8_t sinTable[SAMPLE_LENGTH + 1] = {
		0, 25, 49, 71, 90, 106, 117, 125,
		127, 125, 117, 106, 90, 71, 49, 25,
		0, -25, -49, -71, -90, -106, -117, -125,
		-127, -125, -117, -106, -90, -71, -49, -25,
		0}; // last value could be used for interpolation

const int8_t expNegTable[SAMPLE_LENGTH + 1] = {
		127, 117, 107, 98, 90, 82, 76, 69,
		64, 58, 53, 49, 45, 41, 38, 34,
		32, 29, 26, 24, 22, 20, 19, 17,
		16, 14, 13, 12, 11, 10, 9, 8,
		0}; // last value could be used for interpolation


#endif
