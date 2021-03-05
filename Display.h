#include <Arduino.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <SPI.h>

#define TFT_CS        10
#define TFT_RST        8
#define TFT_DC         9


class Display
{
	public:
    uint8_t block_dim = 8;
		Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
    
    Display();
    void draw_score(int score);

		void draw_background();
    void draw_blocks(uint8_t last_pos[],
                    uint8_t new_pos[],
                    uint8_t len, 
                    int color);

    void draw_block_lines(uint8_t line_pos,
                          bool gameBoard[11][24],
                          int gameBoard_colors[11][24]);
};
