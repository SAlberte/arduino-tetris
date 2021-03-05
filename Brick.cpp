#include "Brick.h"
#include "Colors.h"
#include <Arduino.h>

Brick::Brick(int shape)
{
  this->positions_len = 8;
  this->shape = shape;
  set_initial_params();
  set_initial_placement();

}

void Brick::set_initial_params()
{
  switch (this->shape)
  {
	case shapeI:
	  {
		uint8_t temp[] = {0, 1, 0, 0, 0, 2, 0, 3};
		memcpy(this->positions, temp, sizeof(temp[0]) * 8);
		this->color = Colors::RED;
	  }
	  break;
	case shapeT:
	  {
		uint8_t temp[] = {1, 0, 1, 1, 2, 0, 0, 0};
		memcpy(this->positions, temp, sizeof(temp[0]) * 8);
		this->color = Colors::GRAY;
	  }
	  break;
	case shapeO:
	  {
		uint8_t temp[] = {1, 1, 1, 0, 0, 1, 0, 0};
		memcpy(this->positions, temp, sizeof(temp[0]) * 8);
		this->color = Colors::CYAN;
	  }
	  break;
	case shapeL:
	  {
		uint8_t temp[] = {0, 1, 0, 0, 0, 2, 1, 2};
		memcpy(this->positions, temp, sizeof(temp[0]) * 8);
		this->color = Colors::YELLOW;
	  }
	  break;
	case shapeJ:
	  {
		uint8_t temp[] = {1, 1, 1, 0, 0, 2, 1, 2};
		memcpy(this->positions, temp, sizeof(temp[0]) * 8);
		this->color = Colors::MAGENTA;
	  }
	  break;
	case shapeS:
	  {
		uint8_t temp[] = {1, 1, 2, 0, 0, 1, 1, 0};
		memcpy(this->positions, temp, sizeof(temp[0]) * 8);
		this->color = Colors::BLUE;
	  }
	  break;
	case shapeZ:
	  {
		uint8_t temp[] = {1, 1, 1, 0, 0, 0, 2, 1};
		memcpy(this->positions, temp, sizeof(temp[0]) * 8);
		this->color = Colors::GREEN;
	  }
	  break;
	default:
	  {
		uint8_t temp[] = {0, 0, 0, 1, 0, 2, 0, 3};
		memcpy(this->positions, temp, sizeof(temp[0]) * 8);
		this->color = Colors::RED;
	  }
  }
}

void Brick::set_initial_placement()
{
 for(int i=0; i<this->positions_len; i+=2)
  {
	this->positions[i]+=4;

  }
}
