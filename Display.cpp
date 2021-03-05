#include "Display.h"
#include "Colors.h"
#include <Arduino.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <SPI.h>


Display::Display()
{
  this->tft.initR(INITR_BLACKTAB);
}

void Display::draw_background()
{
  tft.fillScreen(Colors::LIME);
  tft.fillRect(0, 0, 20, 160, Colors::YELLOW);
  tft.fillRect(108, 0, 20, 160, Colors::YELLOW);
}

void Display::draw_score(int score)
{
      tft.fillRect(108, 0, 20, 60, Colors::YELLOW);
      tft.setTextSize(1);
      tft.setCursor(109, 5);
      tft.setTextColor(Colors::BLUE);
      tft.print(score);
}

void Display::draw_blocks(uint8_t last_pos[],
                          uint8_t new_pos[],
                          uint8_t len, 
                          int color)
{ 
  uint8_t clear_same_inds[4] = {5, 5, 5, 5};
  uint8_t draw_same_inds[4] = {5, 5, 5, 5};
  for (int i = 0; i < len - 1; i += 2)
  {
    for (int j = 0; j < len - 1; j += 2)
    {
      if (new_pos[i] == last_pos[j] &&
          new_pos[i + 1] == last_pos[j + 1])
      {
        clear_same_inds[i / 2] = j;
        draw_same_inds[i / 2] = i;
      }
    }
  }

  for (int i = 0; i < len - 1; i += 2)
  {
    bool should_clear = true;
    bool should_draw = true;

    for (int j = 0; j < 4; j++)
    {
      if (i == clear_same_inds[j])
      {
        should_clear = false;
        break;
      }
    }
    for (int j = 0; j < 4; j++)
    {
      if (i == draw_same_inds[j])
      {
        should_draw = false;
        break;
      }
    }

    if (should_clear)
      tft.fillRect(last_pos[i],
                   last_pos[i + 1],
                   block_dim,
                   block_dim,
                   Colors::LIME);

    if (should_draw)
    {
      tft.fillRect(new_pos[i],
                   new_pos[i + 1],
                   block_dim,
                   block_dim,
                   color);

      tft.drawRect(new_pos[i],
                   new_pos[i + 1],
                   block_dim,
                   block_dim,
                   Colors::BLACK);
    }
  }
}

void Display::draw_block_lines(uint8_t line_pos,
                               bool gameBoard[11][24],
                               int gameBoard_colors[11][24])
{
      tft.fillRect(20, 0, 88, line_pos*block_dim-3*block_dim, Colors::LIME);
      for(int y=0;y<=line_pos;y++)
        for(int x=0;x<11;x++)
        {
          if(gameBoard[x][y])
          {
            tft.fillRect(x*block_dim+20,
                   y* block_dim - 4 * block_dim,
                   block_dim,
                   block_dim,
                   gameBoard_colors[x][y]);

            tft.drawRect(x*block_dim+20,
                   y*block_dim - 4*block_dim,
                   block_dim,
                   block_dim,
                   Colors::BLACK);
          } 
        }
}
