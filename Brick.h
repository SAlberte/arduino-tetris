#include "Arduino.h"

class Brick
{
  public:
    enum
    {
      shapeI = 0,
      shapeT = 1,
      shapeO = 2,
      shapeL = 3,
      shapeJ = 4,
      shapeS = 5,
      shapeZ = 6
    };

    uint8_t positions[8];
    uint8_t positions_len;
    int shape;
    int color;

    Brick(int shape);
    void set_initial_params();
    void set_initial_placement();
};
