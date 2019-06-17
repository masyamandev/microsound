
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

const int8_t noise[SAMPLE_LENGTH + 1] = {
		-14, -2, 22, 53, -27, -87, -23, 123,
		-23, 66, -20, -77, -102, 95, 92, -41,
		22, -127, -26, 73, -121, 119, 64, 98,
		9, 71, -11, 66, -58, 67, 96, -78,
		-14}; // last value could be used for interpolation


#endif
