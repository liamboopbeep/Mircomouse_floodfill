#include <string>
#include "..\Control\Control.h"

enum class SimpleStates { st_init, ortho, ortho_L, ortho_R, st_stop };

void simplestatemachine(const std::string& robot_commands) {
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
                        SS90L();
                        x = 2;
                        break;
                    case SimpleStates::ortho_R:
                        simple_current_st = SimpleStates::ortho;
                        SS90R();
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
                        FWD(x);
                        break;
                    case SimpleStates::ortho_L:
                        simple_current_st = SimpleStates::ortho_L;
                        SS90L();
                        FWD(1);
                        break;
                    case SimpleStates::ortho_R:
                        simple_current_st = SimpleStates::ortho_L;
                        SS90R();
                        FWD(1);
                        break;
                    default:
                        break;
                }
                break;

            case 'R':
                switch (simple_current_st) {
                    case SimpleStates::ortho:
                        simple_current_st = SimpleStates::ortho_R;
                        FWD(x);
                        break;
                    case SimpleStates::ortho_R:
                        simple_current_st = SimpleStates::ortho_R;
                        SS90R();
                        FWD(1);
                        break;
                    case SimpleStates::ortho_L:
                        simple_current_st = SimpleStates::ortho_R;
                        SS90L();
                        FWD(1);
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
                        FWD(x);
                        break;
                    case SimpleStates::ortho_L:
                        simple_current_st = SimpleStates::st_stop;
                        SS90L();
                        FWD(1);
                        break;
                    case SimpleStates::ortho_R:
                        simple_current_st = SimpleStates::st_stop;
                        SS90R();
                        FWD(1);
                        break;
                    default:
                        break;
                }
                break;
        }
    }
}
