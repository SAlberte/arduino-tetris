#include <Arduino.h>
#include "GameEngine.h"
#include "Colors.h"



GameEngine::GameEngine()
{
  score = 0;
  block_dim = 8;
  for (int i = 0; i < 11; i++)
    for (int j = 0; j < 24; j++)
    {
      gameBoard[i][j] = false;
      gameBoard_colors[i][j] = Colors::LIME;
    }
  is_end = false;
  input.set_initial_values();
  screen.draw_background();
  game_loop();
}

void GameEngine::game_loop()
{

  while (!is_end)
  {
    bool is_brick_set = false;
    int random_shape = random(0, 7);
    Brick tet_shape = Brick(random_shape);
    input.set_initial_values();
    char vec_x = 0;
    char vec_y = 0;
    uint8_t fall_time = 250;
    uint8_t simple_iter = 0;
    uint8_t real_pos[8];
    uint8_t last_real_pos[8];

    while (!is_brick_set)
    {
      simple_iter++;
      unsigned long time = millis();
      vec_x = 0;
      vec_y = 0;
      if (!input.get_rotation())
      {
        control.rotate(tet_shape,
                       gameBoard,
                       real_pos,
                       last_real_pos);
        screen.draw_blocks(last_real_pos,
                           real_pos,
                           block_dim,
                           tet_shape.color);
      }
      if (!input.get_left())
      {
        control.move_left(tet_shape.positions,
                          vec_x,
                          vec_y,
                          tet_shape.positions_len,
                          gameBoard);
      }
      if (!input.get_right())
      {
        control.move_right(tet_shape.positions,
                           vec_x,
                           vec_y,
                           tet_shape.positions_len,
                           gameBoard);
      }
      control.fall(tet_shape,
                   vec_x,
                   vec_y,
                   8,
                   gameBoard,
                   is_end,
                   is_brick_set,
                   gameBoard_colors);

      control.calc_real_positions(tet_shape.positions,
                                  real_pos,
                                  last_real_pos,
                                  vec_x,
                                  vec_y,
                                  tet_shape.positions_len);

      screen.draw_blocks(last_real_pos,
                         real_pos,
                         block_dim,
                         tet_shape.color);

      input.reset_buttons();
      control.clear_full_lines(gameBoard,
                               gameBoard_colors,
                               score,
                               screen);
      while (millis() - time < fall_time)
      {
        input.update_values();

        if (simple_iter > 2 && !input.get_down())
          fall_time = 10;
      }

    }
    screen.draw_score(score);
  }
}
