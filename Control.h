#include <Arduino.h>
#include "Brick.h"
#include "Display.h"

class Control
{
	public:
		uint8_t block_dim = 8;
	
		void calc_real_positions(uint8_t pos[],
							  	uint8_t new_real_pos[],
								uint8_t last_real_pos[],
								char vec_x,
								char vec_y,
								uint8_t len);
								
		void move_left(uint8_t pos[],
					   char &vec_x,
					   char &vec_y,
					   uint8_t len,
					   bool gameBoard[][24]);

		void move_right(uint8_t pos[],
						   char &vec_x,
						   char &vec_y,
						   uint8_t len,
						   bool gameBoard[][24]);
						   
		void rotate(Brick &tet_shape,
					bool gameBoard[11][24],
					uint8_t new_real_pos[],
					uint8_t last_real_pos[]);
					
		void fall(Brick &tet_shape,
				  char &vec_x,
				  char &vec_y,
				  uint8_t len,
				  bool gameBoard[11][24],
				  bool &is_end,
			      bool &is_block_set,
				  int gameBoard_colors[11][24]);

   void clear_full_lines(bool gameBoard[11][24],
                               int gameBoard_colors[11][24],
                               int &score,
                               Display screen);
};
