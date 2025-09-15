#pragma once

#include "..\API\API.h"
#include "..\Control\Control.h"

class Mouse {
public:
    float x = 0;
    float y = 0;
    int direction = 90;
    int prev_direction  = 0;

    void update_position(float dist = 1);
    void update_direction(int turn_direction);
    void move_forward(int dist = 1);
    void move_forward_half(int dist = 1);
    void turn_right();
    void turn_left();
    void turn_right45();
    void turn_left45();
    void turn_around();
    // Movement commands
    void FWD(int x);
    void SS90R();
    void SS90L();
    void SS180R();
    void SS180L();

    void DIA(int x);

    // Diagonal Right
    void DS45R();
    void DS135R();
    void SD45R();
    void SD135R();
    void DD90R();


    // Diagonal Left
    void DS45L();
    void DS135L();
    void SD45L();
    void SD135L();
    void DD90L();

};
