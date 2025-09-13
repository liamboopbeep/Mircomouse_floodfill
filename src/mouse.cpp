#include "mouse.h"

        void Mouse::update_position() {
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

        void Mouse::update_direction(int turn_direction) {
        direction = (direction + turn_direction) % 4;
            if (direction < 0) {
            direction += 4;
            }
        }

        void Mouse::move_forward(int dist) {
            API::moveForward(dist);
            update_position();
            // log("foward");
          }

          void Mouse::turn_right() {
            API::turnRight();
            update_direction(1);
            // log("Right");
          }

          void Mouse::turn_left() {
            API::turnLeft();
            update_direction(-1);
            // log("Left");
          }

          void Mouse::turn_around() {
            turn_right();
            turn_right();
            // log("Around");
          }

          void Mouse::FWD(int x) {
            move_forward(x);
            if (x > 1){
              move_forward(x-1);
              API::moveForwardHalf();
            }
          }

          void Mouse::SS90R() {
            API::turnRight45();
            API::moveForwardHalf();
            API::turnRight45();
          }

          void Mouse::SS90L() {
            API::turnLeft45();
            API::moveForwardHalf();
            API::turnRight45();
          }

          void Mouse::SS180R() {
            turn_right();
            move_forward();
            turn_right();
          }

          void Mouse::SS180L() {
            turn_left();
            move_forward();
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