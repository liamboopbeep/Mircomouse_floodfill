#include <string>
#include "statemachine.h"

enum class States {
    st_init, ortho, ortho_L, ortho_R, st_stop, ortho_LL, ortho_RR, diag_LR, diag_RL, diag_RR, diag_LL
};

void statemachine(const std::string& robot_commands) {
    int x = 0;
    States current_st = States::st_init;

    for (char cmd : robot_commands) {
        switch (cmd) {
            case 'F':
                switch (current_st) {
                    case States::st_init:
                        current_st = States::ortho;
                        x = 1;
                        break;
                    case States::ortho:
                        x++;
                        break;
                    case States::ortho_L:
                        current_st = States::ortho;
                        SS90L();
                        x = 2;
                        break;
                    case States::ortho_R:
                        current_st = States::ortho;
                        SS90R();
                        x = 2;
                        break;
                    case States::ortho_LL:
                        current_st = States::ortho;
                        SS180L();
                        x = 2;
                        break;
                    case States::ortho_RR:
                        current_st = States::ortho;
                        SS180R();
                        x = 2;
                        break;
                    case States::diag_LR:
                        current_st = States::ortho;
                        DIA(x);
                        DS45R();
                        x = 2;
                        break;
                    case States::diag_RL:
                        current_st = States::ortho;
                        DIA(x);
                        DS45L();
                        x = 2;
                        break;
                    case States::diag_LL:
                        current_st = States::ortho;
                        DIA(x);
                        DS135L();
                        x = 2;
                        break;
                    case States::diag_RR:
                        current_st = States::ortho;
                        DIA(x);
                        DS135R();
                        x = 2;
                        break;
                    default:
                        break;
                }
                break;

            case 'L':
                switch (current_st) {
                    case States::ortho:
                        current_st = States::ortho_L;
                        FWD(x);
                        break;
                    case States::ortho_L:
                        current_st = States::ortho_LL;
                        break;
                    case States::ortho_R:
                        current_st = States::diag_RL;
                        SD45R();
                        x = 2;
                        break;
                    case States::ortho_RR:
                        current_st = States::diag_RL;
                        SD135R();
                        x = 2;
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
                        DIA(x);
                        DD90R();
                        x = 2;
                        break;
                    default:
                        break;
                }
                break;

            case 'R':
                switch (current_st) {
                    case States::ortho:
                        current_st = States::ortho_R;
                        FWD(x);
                        break;
                    case States::ortho_R:
                        current_st = States::ortho_RR;
                        break;
                    case States::ortho_L:
                        current_st = States::diag_LR;
                        SD45L();
                        x = 2;
                        break;
                    case States::ortho_LL:
                        current_st = States::diag_LR;
                        SD135L();
                        x = 2;
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
                        DIA(x);
                        DD90L();
                        x = 2;
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
                        FWD(x);
                        break;
                    case States::ortho_L:
                        current_st = States::st_stop;
                        SS90L();
                        FWD(1);
                        break;
                    case States::ortho_R:
                        current_st = States::st_stop;
                        SS90R();
                        FWD(1);
                        break;
                    case States::ortho_LL:
                        current_st = States::st_stop;
                        SS180L();
                        FWD(1);
                        break;
                    case States::ortho_RR:
                        current_st = States::st_stop;
                        SS180R();
                        FWD(1);
                        break;
                    case States::diag_LR:
                        current_st = States::st_stop;
                        DIA(x);
                        DS45R();
                        FWD(1);
                        break;
                    case States::diag_RL:
                        current_st = States::st_stop;
                        DIA(x);
                        DS45L();
                        FWD(1);
                        break;
                    case States::diag_LL:
                        current_st = States::st_stop;
                        DIA(x);
                        DS135L();
                        FWD(1);
                        break;
                    case States::diag_RR:
                        current_st = States::st_stop;
                        DIA(x);
                        DS135R();
                        FWD(1);
                        break;
                    default:
                        break;
                }
                break;
        }
    }
}
