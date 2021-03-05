#include "Arduino.h"
#include "Input.h"
#include "Control.h"

class GameEngine
{
  public:
    GameEngine();
    Control control;
    int score;
    bool gameBoard[11][24];
    int gameBoard_colors[11][24];
    bool is_end;
    Input input;
    Display screen;
    uint8_t block_dim;

    void game_loop();
};
