/*
 * Library for 16x2 characters LCD displays.
 *
 * Author: Aleksandr Maksymenko aka masyaman
 */


#define LCD_DDR 	DDRD
#define LCD_PORT	PORTD
#define LCD_PIN_D4		0
#define LCD_PIN_RS		5
#define LCD_PIN_EN		6

#define LCD_PIN_DATA_MASK	((1 << LCD_PIN_D4) | (1 << (LCD_PIN_D4 + 1)) | (1 << (LCD_PIN_D4 + 2)) | (1 << (LCD_PIN_D4 + 3)))
#define LCD_PIN_MASK		(LCD_PIN_DATA_MASK | (1 << LCD_PIN_EN) | (1 << LCD_PIN_RS))


inline static void __lcd_delay() {
	_delay_ms(0.3);
}

inline static void __lcd_longDelay() {
	_delay_ms(4.1);
}

inline static void __lcd_initDelay() {
	_delay_ms(15);
}



inline static void pulseLcd()
{
    LCD_PORT |= (1 << LCD_PIN_EN);
    LCD_PORT &= ~(1 << LCD_PIN_EN);
    __lcd_delay();
}

void sendByte(uint8_t byteToSend, uint8_t isData)
{
	uint8_t clear = ~LCD_PIN_MASK;
	uint8_t dataBit = 0;
	if (isData) {
		clear |= (1 << LCD_PIN_RS);
		dataBit |= (1 << LCD_PIN_RS);
	}

    LCD_PORT &= clear;
    LCD_PORT |= ((byteToSend >> 4) << LCD_PIN_D4) | dataBit;
    pulseLcd();

    LCD_PORT &= clear;
    LCD_PORT |= ((byteToSend & 0x0F) << LCD_PIN_D4) | dataBit;
    pulseLcd();
}

void cursor(uint8_t row, uint8_t col)
{
	uint8_t address;
    if (row == 0) {
        address = 0;
    } else {
        address = 0x40;
    }

    address |= col;
    sendByte(0x80 | address, 0);
//    __lcd_longDelay();
}

void clearLcdScreen()
{
    sendByte(0x01, 0);
    __lcd_longDelay();
    sendByte(0x02, 0);
    __lcd_longDelay();
}

inline static void initLCD() {

	LCD_DDR |= LCD_PIN_MASK;

    __lcd_initDelay();

	// Send 3 times 8-bit mode and 1 time 4-bit mode
	sendByte(0b00110011, 0);
    sendByte(0b00110010, 0);

    // Init rest of settings in 4-bit mode
    sendByte(0b00101000, 0);
    sendByte(0b00001100, 0);
    sendByte(0b00000110, 0);

    clearLcdScreen();
}

void initChar(uint8_t c, uint8_t* tile)
{
    sendByte(0b01000000 | (c << 3), 0);
    for (int i = 0; i < 8; i++) {
        sendByte(*tile, 1);
        tile++;
    }
}

void initCharProgmem(uint8_t c, const uint8_t* tile)
{
    sendByte(0b01000000 | (c << 3), 0);
    for (int i = 0; i < 8; i++) {
        sendByte(pgm_read_byte(tile), 1);
        tile++;
    }
}

inline void printChar(char c)
{
	sendByte(c, 1);
}

// TODO add progmem?
void printStr(char *text)
{
    char *c;
    c = text;
    while ((c != 0) && (*c != 0)) {
        sendByte(*c, 1);
        c++;
    }
}
