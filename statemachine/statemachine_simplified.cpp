#include <string>
#include "statemachine_simplified.h"

enum class SimpleStates { st_init, ortho, ortho_L, ortho_R, st_stop };

void simplestatemachine(const std::string& robot_commands, Mouse& mouse) {
    int x = 0;
    SimpleStates simple_current_st = SimpleStates::st_init;

    for (char cmd : robot_commands) {
        switch (cmd) {
            case 'F':
                switch (simple_current_st) {
                    case SimpleStates::st_init:
                        simple_current_st = SimpleStates::ortho;
                        x = 1;
                        break;
                    case SimpleStates::ortho:
                        simple_current_st = SimpleStates::ortho;
                        x++;
                        break;
                    case SimpleStates::ortho_L:
                        simple_current_st = SimpleStates::ortho;
                        mouse.SS90L();
                        x = 2;
                        break;
                    case SimpleStates::ortho_R:
                        simple_current_st = SimpleStates::ortho;
                        mouse.SS90R();
                        x = 2;
                        break;
                    default:
                        break;
                }
                break;

            case 'L':
                switch (simple_current_st) {
                    case SimpleStates::ortho:
                        simple_current_st = SimpleStates::ortho_L;
                        mouse.FWD(x);
                        break;
                    case SimpleStates::ortho_L:
                        simple_current_st = SimpleStates::ortho_L;
                        mouse.SS90L();
                        mouse.FWD(1);
                        break;
                    case SimpleStates::ortho_R:
                        simple_current_st = SimpleStates::ortho_L;
                        mouse.SS90R();
                        mouse.FWD(1);
                        break;
                    default:
                        break;
                }
                break;

            case 'R':
                switch (simple_current_st) {
                    case SimpleStates::ortho:
                        simple_current_st = SimpleStates::ortho_R;
                        mouse.FWD(x);
                        break;
                    case SimpleStates::ortho_R:
                        simple_current_st = SimpleStates::ortho_R;
                        mouse.SS90R();
                        mouse.FWD(1);
                        break;
                    case SimpleStates::ortho_L:
                        simple_current_st = SimpleStates::ortho_R;
                        mouse.SS90L();
                        mouse.FWD(1);
                        break;
                    default:
                        break;
                }
                break;

            case 'S':
                switch (simple_current_st) {
                    case SimpleStates::st_init:
                        simple_current_st = SimpleStates::st_stop;
                        break;
                    case SimpleStates::ortho:
                        simple_current_st = SimpleStates::st_stop;
                        mouse.FWD(x);
                        break;
                    case SimpleStates::ortho_L:
                        simple_current_st = SimpleStates::st_stop;
                        mouse.SS90L();
                        mouse.FWD(1);
                        break;
                    case SimpleStates::ortho_R:
                        simple_current_st = SimpleStates::st_stop;
                        mouse.SS90R();
                        mouse.FWD(1);
                        break;
                    default:
                        break;
                }
                break;
        }
    }
}
