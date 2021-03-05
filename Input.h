#include "Arduino.h"

class Input
{
  private:
    int leftPin;
    int rightPin;
    int rotatePin;
    int downPin;

  public:
    Input();

    uint8_t last_left_button_val;
    uint8_t last_right_button_val;
    uint8_t last_rotate_button_val;
    uint8_t last_down_button_val;

    uint8_t left_button;
    uint8_t right_button;
    uint8_t rotate_button;
    uint8_t down_button;

    void update_values();
    uint8_t get_rotation();
    uint8_t get_left();
    uint8_t get_right();
    uint8_t get_down();
    void set_initial_values();
    void reset_buttons();
};
