#include "Input.h"
#include <Arduino.h>

Input::Input()
{
  this->leftPin = 2;
  this->rightPin = 5;
  this->rotatePin = 4;
  this->downPin = 6;

  set_initial_values();
}

void Input::update_values()
{
  uint8_t left_button_status = digitalRead(leftPin);
  uint8_t right_button_status = digitalRead(rightPin);
  uint8_t rotate_button_status = digitalRead(rotatePin);
  uint8_t down_button_status = digitalRead(downPin);

  if (last_left_button_val == 1 && left_button_status == 0)
  {
    left_button = 0;
  }
  else if (last_right_button_val == 1 && right_button_status == 0)
  {
    right_button = 0;
  }
  if (last_rotate_button_val == 1 && rotate_button_status == 0)
  {
    rotate_button = 0;
  }
  if (last_down_button_val == 1 && down_button_status == 0)
  {
    down_button = 0;
  }
  last_rotate_button_val = rotate_button_status;
  last_left_button_val = left_button_status;
  last_right_button_val = right_button_status;
  last_down_button_val = down_button_status;
}

uint8_t Input::get_rotation()
{
  return rotate_button;
}

uint8_t Input::get_left()
{
  return left_button;
}

uint8_t Input::get_right()
{
  return right_button;
}

uint8_t Input::get_down()
{
  return down_button;
}

void Input::set_initial_values()
{
  this->last_left_button_val = 1;
  this->last_right_button_val = 1;
  this->last_rotate_button_val = 1;
  this->last_down_button_val = 0;
  this->left_button = 1;
  this->right_button = 1;
  this->rotate_button = 1;
  this->down_button = 1;
}

void Input::reset_buttons()
{
  left_button = 1;
  right_button = 1;
  rotate_button = 1;
  down_button = 1;
}
