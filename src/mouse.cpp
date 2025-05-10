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
};