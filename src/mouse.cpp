#include "mouse.h"
#include <iostream>

        void Mouse::update_position(float dist) {
            switch (direction) {
              case 90:  // NORTH
                y += dist;
                break;
              case 0:  // EAST
                x += dist;
                break;
              case 270:  // SOUTH
                y -= dist;
                break;
              case 180:  // WEST
                x -= dist;
                break;
            }
          }

        void Mouse::update_direction(int turn_direction) {
        direction = (direction + turn_direction) % 360;
            if (direction < 0) {
            direction += 360;
            }
        }

        void Mouse::move_forward(int dist) {
            API::moveForward(dist);
            update_position(dist);
            // log("foward");
          }

        void Mouse::move_forward_half() {
            API::moveForwardHalf();
            update_position(0.5);
          }

          void Mouse::turn_right() {
            API::turnRight();
            update_direction(-90);
            // log("Right");
          }

          void Mouse::turn_left() {
            API::turnLeft();
            update_direction(90);
            // log("Left");
          }

          void Mouse::turn_right45() {
            API::turnRight45();
            update_direction(-45);
            // log("Right");
          }

          void Mouse::turn_left45() {
            API::turnLeft45();
            update_direction(45);
            // log("Left");
          }


          void Mouse::turn_around() {
            turn_right();
            turn_right();
            // log("Around");
          }

          void Mouse::FWD(int x) {
            // if (x == 1){
            //   std::cerr << "FWD:" << x << std::endl;
            //   move_forward();
            //   return;
            // }
            std::cerr << "FWD:" << x << std::endl;
            if (x <= 0) return;
            move_forward(x);
          }

          void Mouse::SS90R() {
            std::cerr << "SS90R" << std::endl;
            turn_right45();
            move_forward_half();
            turn_right45();
          }

          void Mouse::SS90L() {
            std::cerr << "SS90L" << std::endl;
            turn_left45();
            move_forward_half();
            turn_left45();
          }

          void Mouse::SS180R() {
            std::cerr << "SS180R" << std::endl;
            turn_right45();
            move_forward_half();
            turn_right();
            move_forward_half();
            turn_right45();
          }

          void Mouse::SS180L() {
            std::cerr << "SS180L" << std::endl;
            turn_left45();
            move_forward_half();
            turn_left();
            move_forward_half();
            turn_left45();
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