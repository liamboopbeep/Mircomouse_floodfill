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

        void Mouse::move_forward_half(int dist) {
            API::moveForwardHalf(dist);
            update_position(0.5*dist);
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
            std::cerr << "FWD:" << x << std::endl;
            if (x <= 0) return;
            move_forward(x);
            Control::FWD(x);
          }

          void Mouse::SS90R() {
            std::cerr << "SS90R" << std::endl;
            turn_right45();
            move_forward_half();
            turn_right45();
            Control::SS90R();
          }

          void Mouse::SS90L() {
            std::cerr << "SS90L" << std::endl;
            turn_left45();
            move_forward_half();
            turn_left45();
            Control::SS90L();
          }

          void Mouse::SS180R() {
            std::cerr << "SS180R" << std::endl;
            turn_right45();
            move_forward_half();
            turn_right();
            move_forward_half();
            turn_right45();
            Control::SS180R();
          }

          void Mouse::SS180L() {
            std::cerr << "SS180L" << std::endl;
            turn_left45();
            move_forward_half();
            turn_left();
            move_forward_half();
            turn_left45();
            Control::SS180L();
          }

          void Mouse::DIA(int x) {
            std::cerr << "DIA:" << x << std::endl;
            if (x <= 0) return;
            move_forward_half(x);
          }

          // Diagonal Right
          void Mouse::DS45R() {
            std::cerr << "DS45R" << std::endl;
            turn_right45();
            Control::DS45R();
          }
          void Mouse::DS135R() {
            std::cerr << "DS135R" << std::endl;
            move_forward_half();
            turn_right();
            move_forward_half();
            turn_right45();
            Control::DS135R();
          }
          void Mouse::SD45R() {
            std::cerr << "SD45R" << std::endl;
            turn_right45();
            Control::SD45R();
          }
          void Mouse::SD135R() {
            std::cerr << "SD135R" << std::endl;
            move_forward_half();
            turn_right();
            move_forward_half();
            turn_right45();
            Control::SD135R();
          }
          void Mouse::DD90R() {
            std::cerr << "DD90R" << std::endl;
            move_forward_half();
            turn_right();
            move_forward_half();
            Control::DD90R();
          }

          // Diagonal Left
          void Mouse::DS45L() {
            std::cerr << "DS45L" << std::endl;
            turn_left45();
            Control::DS45L();
          }
          void Mouse::DS135L() {
            std::cerr << "DS135L" << std::endl;
            move_forward_half();
            turn_left();
            move_forward_half();
            turn_left45();
            Control::DS135L();
          }
          void Mouse::SD45L() {
            std::cerr << "SD45L" << std::endl;
            turn_left45();
            Control::SD45L();
          }
          void Mouse::SD135L() {
            std::cerr << "SD135L" << std::endl;
            move_forward_half();
            turn_left();
            move_forward_half();
            turn_left45();
            Control::SD135L();
          }
          void Mouse::DD90L() {
            std::cerr << "DD90L" << std::endl;
            move_forward_half();
            turn_left();
            move_forward_half();
            Control::DD90L();
          }