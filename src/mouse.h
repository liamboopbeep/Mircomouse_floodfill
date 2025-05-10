#pragma once

#include "..\API\API.h"

class Mouse {
public:
    int x = 0;
    int y = 0;
    int direction = 0;
    int prev_direction  = 0;

    void update_position(int& direction);
    void update_direction(int& direction, int turn_direction);
    void move_forward(int dist = 1);
    void turn_right();
    void turn_left();
    void turn_around();
    void FWD(int x);
    void SS90R();
    void SS90L();
    void SS180R();
    void SS180L();
};
