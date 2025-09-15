#include <string>
#include "statemachine.h"

enum class States {
    st_init, ortho, ortho_L, ortho_R, st_stop, ortho_LL, ortho_RR, diag_LR, diag_RL, diag_RR, diag_LL
};

void statemachine(const std::string& robot_commands, Mouse& mouse) {
    int x = 0;
    States current_st = States::st_init;

    for (char cmd : robot_commands) {
        switch (cmd) {
            case 'F':
                switch (current_st) {
                    case States::st_init:
                        current_st = States::ortho;
                        x = 0;
                        mouse.move_forward_half();
                        break;
                    case States::ortho:
                        x++;
                        break;
                    case States::ortho_L:
                        current_st = States::ortho;
                        mouse.SS90L();
                        x = 1;
                        break;
                    case States::ortho_R:
                        current_st = States::ortho;
                        mouse.SS90R();
                        x = 1;
                        break;
                    case States::ortho_LL:
                        current_st = States::ortho;
                        mouse.SS180L();
                        x = 1;
                        break;
                    case States::ortho_RR:
                        current_st = States::ortho;
                        mouse.SS180R();
                        x = 1;
                        break;
                    case States::diag_LR:
                        current_st = States::ortho;
                        mouse.DIA(x);
                        mouse.move_forward_half();
                        mouse.DS45R();
                        x = 1;
                        break;
                    case States::diag_RL:
                        current_st = States::ortho;
                        mouse.DIA(x);
                        mouse.move_forward_half();
                        mouse.DS45L();
                        x = 1;
                        break;
                    case States::diag_LL:
                        current_st = States::ortho;
                        mouse.DIA(x);
                        mouse.DS135L();
                        x = 1;
                        break;
                    case States::diag_RR:
                        current_st = States::ortho;
                        mouse.DIA(x);
                        mouse.DS135R();
                        x = 1;
                        break;
                    default:
                        break;
                }
                break;

            case 'L':
                switch (current_st) {
                    case States::st_init:
                        current_st = States::ortho;
                        mouse.move_forward_half();
                        break;
                    case States::ortho:
                        current_st = States::ortho_L;
                        mouse.FWD(x);
                        break;
                    case States::ortho_L:
                        current_st = States::ortho_LL;
                        break;
                    case States::ortho_R:
                        current_st = States::diag_RL;
                        mouse.SD45R();
                        x = 1;
                        break;
                    case States::ortho_RR:
                        current_st = States::diag_RL;
                        mouse.SD135R();
                        x = 0;
                        break;
                    case States::diag_LR:
                        current_st = States::diag_RL;
                        x++;
                        break;
                    case States::diag_RL:
                        current_st = States::diag_LL;
                        break;
                    case States::diag_RR:
                        current_st = States::diag_RL;
                        mouse.DIA(x);
                        mouse.DD90R();
                        x = 0;
                        break;
                    default:
                        break;
                }
                break;

            case 'R':
                switch (current_st) {
                    case States::st_init:
                        current_st = States::ortho;
                        mouse.move_forward_half();
                        break;
                    case States::ortho:
                        current_st = States::ortho_R;
                        mouse.FWD(x);
                        break;
                    case States::ortho_R:
                        current_st = States::ortho_RR;
                        break;
                    case States::ortho_L:
                        current_st = States::diag_LR;
                        mouse.SD45L();
                        x = 1;
                        break;
                    case States::ortho_LL:
                        current_st = States::diag_LR;
                        mouse.SD135L();
                        x = 0;
                        break;
                    case States::diag_RL:
                        current_st = States::diag_LR;
                        x++;
                        break;
                    case States::diag_LR:
                        current_st = States::diag_RR;
                        break;
                    case States::diag_LL:
                        current_st = States::diag_LR;
                        mouse.DIA(x);
                        mouse.DD90L();
                        x = 0;
                        break;
                    default:
                        break;
                }
                break;

            case 'S':
                switch (current_st) {
                    case States::st_init:
                        current_st = States::st_stop;
                        break;
                    case States::ortho:
                        current_st = States::st_stop;
                        mouse.FWD(x);
                        break;
                    case States::ortho_L:
                        current_st = States::st_stop;
                        mouse.SS90L();
                        mouse.move_forward_half();
                        break;
                    case States::ortho_R:
                        current_st = States::st_stop;
                        mouse.SS90R();
                        mouse.move_forward_half();
                        break;
                    case States::ortho_LL:
                        current_st = States::st_stop;
                        mouse.SD135L();
                        mouse.move_forward();
                        break;
                    case States::ortho_RR:
                        current_st = States::st_stop;
                        mouse.SD135R();
                        mouse.move_forward();
                        break;
                    case States::diag_LR:
                        current_st = States::st_stop;
                        mouse.DIA(x);
                        mouse.DS45R();
                        mouse.move_forward_half();
                        break;
                    case States::diag_RL:
                        current_st = States::st_stop;
                        mouse.DIA(x);
                        mouse.DS45L();
                        mouse.move_forward_half();
                        break;
                    case States::diag_LL:
                        current_st = States::st_stop;
                        mouse.DIA(x);
                        mouse.DS135L();
                        mouse.move_forward_half();
                        break;
                    case States::diag_RR:
                        current_st = States::st_stop;
                        mouse.DIA(x);
                        mouse.DS135R();
                        mouse.move_forward_half();
                        break;
                    default:
                        break;
                }
                break;
        }
    }
}
