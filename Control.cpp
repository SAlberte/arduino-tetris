#include "Control.h"
#include <Arduino.h>

void Control::calc_real_positions(uint8_t pos[],
							  	  uint8_t new_real_pos[],
								  uint8_t last_real_pos[],
								  char vec_x,
								  char vec_y,
								  uint8_t len)
{

  for (int i = 0; i < len - 1; i += 2)
  {
    new_real_pos[i] = 20 + pos[i] * block_dim;
    new_real_pos[i + 1] = pos[i + 1] * block_dim - 4 * block_dim;

    last_real_pos[i] = new_real_pos[i] - vec_x * block_dim;
    last_real_pos[i + 1] = new_real_pos[i + 1] - vec_y * block_dim;
 
  }
}

void Control::move_left(uint8_t pos[],
						char &vec_x,
						char &vec_y,
						uint8_t len,
						bool gameBoard[][24])
{	
	uint8_t new_pos[len];
	bool can_move = true;
    for (int i = 0; i < len - 1; i += 2)
    {
      if (pos[i] > 0 && !gameBoard[pos[i] - 1][pos[i + 1]])
      {
        new_pos[i] = pos[i] - 1;
        new_pos[i + 1] = pos[i + 1];
      }
      else
      {
        can_move = false;
        break;
      }
    }
    if (can_move == true)
    {
      vec_x -= 1;
      memcpy(pos, new_pos, sizeof(pos[0]) * 8);
    }
}

void Control::move_right(  uint8_t pos[],
						   char &vec_x,
						   char &vec_y,
						   uint8_t len,
						   bool gameBoard[][24])
{	
	uint8_t new_pos[len];
	bool can_move = true;
    for (int i = 0; i < len - 1; i += 2)
    {
      if (pos[i] <= 9 && !gameBoard[pos[i] + 1][pos[i + 1]])
      {
        new_pos[i] = pos[i] + 1;
        new_pos[i + 1] = pos[i + 1];
      }
      else
      {
        can_move = false;
        break;
      }

    }
    if (can_move == true)
    {
      vec_x += 1;
      memcpy(pos, new_pos, sizeof(pos[0]) * 8);
    }
}

void Control::rotate(Brick &tet_shape,
		   			 bool gameBoard[11][24],
		   			 uint8_t new_real_pos[],
		    		 uint8_t last_real_pos[])
{
  uint8_t new_pos[8];
  if(tet_shape.shape == Brick::shapeO)
  {
    return;
  }
  
  else 
  {
    new_pos[0] = tet_shape.positions[0];
    new_pos[1] = tet_shape.positions[1];
    for(int i = 2; i< 8; i+=2)
    {
      new_pos[i] = tet_shape.positions[0]+tet_shape.positions[1]-tet_shape.positions[i+1];
      new_pos[i+1] = tet_shape.positions[1]-tet_shape.positions[0]+tet_shape.positions[i];
      if(new_pos[i]<0 || new_pos[i]>10 || new_pos[i+1]>23 || gameBoard[new_pos[i]][new_pos[i+1]])
        return;
    }

    for(int i =0;i<8;i+=2)
    {
      last_real_pos[i] = 20 + tet_shape.positions[i] * block_dim;
      last_real_pos[i + 1] = tet_shape.positions[i + 1] * block_dim - 4 * block_dim;

      new_real_pos[i] = 20 + new_pos[i] * block_dim;
      new_real_pos[i + 1] = new_pos[i + 1] * block_dim - 4 * block_dim;
    }
    memcpy(tet_shape.positions, new_pos, sizeof(tet_shape.positions[0]) * 8);
  }
}


void Control::fall(	Brick &tet_shape,
		  	char &vec_x,
		  	char &vec_y,
			uint8_t len,
			bool gameBoard[11][24],
			bool &is_end,
			bool &is_block_set,
			int gameBoard_colors[11][24])
{
  bool can_move = true;
  for (int i = 0; i < len - 1; i += 2)
  {
    if (tet_shape.positions[i + 1] >= 23 ||
        gameBoard[tet_shape.positions[i]][tet_shape.positions[i + 1] + 1])
    {
      can_move = false;
      break;
    }
  }
  
  if (!can_move)
  {
    for (int i = 0; i < len - 1; i += 2)
    {
      gameBoard[tet_shape.positions[i]][tet_shape.positions[i + 1]] = true;
      gameBoard_colors[tet_shape.positions[i]][tet_shape.positions[i + 1]] = tet_shape.color;
      is_block_set = true;
      if (tet_shape.positions[i + 1] == 3)
        is_end = true;
    }
    return;
  }
  vec_y += 1;
  for (int i = 0; i < len - 1; i += 2)
  {
    tet_shape.positions[i + 1] += vec_y;
  }
}

void Control::clear_full_lines(bool gameBoard[11][24],
                               int gameBoard_colors[11][24],
                               int &score,
                               Display screen)
{
  int combo_counter = 0;
  for (int i=3;i<24;i++)
  {
    bool is_full = true;
    for(int j=0;j<11;j++)
    {
      if(gameBoard[j][i] == false)
      {
        is_full = false;
        break;
      }
    }
    if(is_full)
    {
      for(int y=i;y>2;y--)
        for(int j=0;j<11;j++)
        {
          gameBoard[j][y] = gameBoard[j][y-1];
          gameBoard_colors[j][y] = gameBoard_colors[j][y-1];
        }
      screen.draw_block_lines(i,
                              gameBoard,
                              gameBoard_colors);
      combo_counter++;
      
    }
  }
  switch(combo_counter)
  {
    case 0:
    {
      score+=0;
      break;
    }
    case 1:
    {
      score+=4;
      break;
    }
    case 2:
    {
      score+=10;
      break;
    }
    case 3:
    {
      score+=30;
    }
    case 4:
    {
      score+=120;
    }
    default:
    score+=0;
  }
}
