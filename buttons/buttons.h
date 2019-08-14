/*
 * Library for controlling up to 8 buttons on a single port.
 *
 * Author: Aleksandr Maksymenko aka masyaman
 */

#define BUTTONS_DDR_REGISTER 	CONCAT2(DDR, BUTTONS_PORT)
#define BUTTONS_PIN_REGISTER	CONCAT2(PIN, BUTTONS_PORT)
#define BUTTONS_PORT_REGISTER	CONCAT2(PORT, BUTTONS_PORT)

#ifndef BUTTONS_MASK
#define BUTTONS_MASK	0xFF
#endif

uint8_t buttonsPreviousState;
uint8_t buttonsClicked;

#define isButtonPressed(mask)	(!(BUTTONS_PIN_REGISTER & (mask)))

inline void initButtons() {
	BUTTONS_DDR_REGISTER &= ~BUTTONS_MASK;
	BUTTONS_PORT_REGISTER |= BUTTONS_MASK;
	buttonsPreviousState = BUTTONS_PIN_REGISTER;
	buttonsClicked = 0;
}


inline void updateButtons() {
	// TODO skip in case of short delay

	uint8_t buttonsCurrentState = BUTTONS_PIN_REGISTER;
	buttonsClicked |= (~buttonsCurrentState) & buttonsPreviousState;
	buttonsPreviousState = buttonsCurrentState;
}

uint8_t isButtonClicked(uint8_t buttonMask) {
	//updateButtons();

	uint8_t clicked = buttonsClicked & buttonMask;
	buttonsClicked &= ~buttonMask;
	return clicked;
}


