#pragma once

#include "..\API\API.h"

class Mouse {
    public:
        int x = 0;
        int y = 0;
        int direction = 0;
        int prev_direction  = 0;

        void update_position(int &direction) {
            switch (direction) {
              case 0:  // NORTH
                y += 1;
                break;
              case 1:  // EAST
                x += 1;
                break;
              case 2:  // SOUTH
                y -= 1;
                break;
              case 3:  // WEST
                x -= 1;
                break;
            }
          }

        void update_direction(int &direction, int turn_direction) {
        direction = (direction + turn_direction) % 4;
            if (direction < 0) {
            direction += 4;
            }
        }

        void move_forward(int dist = 1) {
            API::moveForward(dist);
            update_position(direction);
            // log("foward");
          }

          void turn_right() {
            API::turnRight();
            update_direction(direction, 1);
            // log("Right");
          }

          void turn_left() {
            API::turnLeft();
            update_direction(direction, -1);
            // log("Left");
          }

          void turn_around() {
            turn_right();
            turn_right();
            // log("Around");
          }

          void FWD(int x) {
            move_forward(x);
          }

          void SS90R() {
            turn_right();
          }

          void SS90L() {
            turn_left();
          }

          void SS180R() {
            turn_right();
            move_forward();
            turn_right();
          }

          void SS180L() {
            turn_left();
            move_forward();
            turn_left();
          }

        //   void DIA(int x) {
        //     // Diagonal move scaled by x
        //   }

        //   // Diagonal Right
        //   void DS45R() {}
        //   void DS135R() {}
        //   void SD45R() {}
        //   void SD135R() {}
        //   void DD90R() {}

        //   // Diagonal Left
        //   void DS45L() {}
        //   void DS135L() {}
        //   void SD45L() {}
        //   void SD135L() {}
        //   void DD90L() {}

};