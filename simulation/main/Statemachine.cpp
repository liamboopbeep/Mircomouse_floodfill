#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <Control.cpp>

////////simplified state machine no diagonals///////
/*
void statemachine(){
    int x;
    States current_st = st_init;
    char cmd;
    for (char cmd : robot_commands){
        cmd = robot_commands[i];
        switch (cmd) {
            case 'F':
                switch (current_st) {
                    case st_init:
                        current_st = ortho;
                        x = 1;
                        break;
                    case ortho:
                        current_st = ortho;
                        x++;
                        break;
                    case ortho_L:
                        current_st = ortho;
                        SS90L();
                        x = 2;
                        break;
                    case ortho_R:
                        current_st = ortho;
                        SS90R();
                        x = 2;
                        break;
						
                }
                break;
            case 'L':
                switch (current_st) {
                    case ortho:
                        current_st = ortho_L;
                        FWD(x);
                        break;
					case ortho_L:
						current_st = ortho_L;
						SS90L;
						FWD(1);
						break;
					case ortho_R:
                        current_st = ortho_L;
						SS90R;
						FWD(1);
						break;
					
                }
                break;

            case 'R':
                switch (current_st) {
                    case ortho:
                        current_st = ortho_R;
                        FWD(x);
                        break;
					case ortho_R:
						current_st = ortho_R;
						SS90R;
						FWD(1);
						break;
					case ortho_L:
                        current_st = ortho_R;
						SS90L;
						FWD(1);
						break;
					
                }
                break;


            case 'S':
                switch (current_st) {
                    case st_init:
                        current_st = st_stop;
                        break;
                    case ortho:
                        current_st = st_stop;
                        FWD(x);
                        break;
                    case ortho_L:
                        current_st = st_stop;
                        SS90L();
                        FWD(1);
                        break;
                    case ortho_R:
                        current_st = st_stop;
                        SS90R();
                        FWD(1);
                        break;
						
                }
                break;
        }
    }
}
*////end of simple state machine////

enum States {st_init, ortho, ortho_L, ortho_LL, ortho_R, ortho_RR, diag_LR, diag_RL, diag_RR,diag_LL,st_stop};

// State machine function
void statemachine(const std::string& robot_commands) {
    int x = 0; // Initialize x
    States current_st = st_init;
    
    for (char cmd : robot_commands) {
        switch (cmd) {
            case 'F':
                switch (current_st) {
                    case st_init:
                        current_st = ortho;
                        x = 1;
                        break;
                    case ortho:
                        current_st = ortho;
                        x++;
                        break;
                    case ortho_L:
                        current_st = ortho;
                        SS90L();
                        x = 2;
                        break;
                    case ortho_R:
                        current_st = ortho;
                        SS90R();
                        x = 2;
                        break;
                    case ortho_LL:
                        current_st = ortho;
                        SS180L();
                        x = 2;
                        break;
                    case ortho_RR:
                        current_st = ortho;
                        SS180R();
                        x = 2;
                        break;
                    case diag_LR:
                        current_st = ortho;
                        DIA(x);
                        DS45R();
                        x = 2; 
                        break; 
                    case diag_RL:  
                        current_st = ortho;
                        DIA(x);
                        DS45L();
                        x = 2;
                        break;
                    case diag_LL:
                        current_st = ortho;
                        DIA(x);
                        DS135L();
                        x = 2;
                        break;
                    case diag_RR:
                        current_st = ortho;
                        DIA(x);
                        DS135R();
                        x = 2;
                        break;
                }
                break;

            case 'L':
                switch (current_st) {
                    case ortho:
                        current_st = ortho_L;
                        FWD(x);
                        break;
                    case ortho_L:
                        current_st = ortho_LL;
                        break;
                    case ortho_R:
                        current_st = diag_RL;
                        SD45R();
                        x = 2;
                        break;
                    case ortho_RR:
                        current_st = diag_RL;
                        SD135R();
                        x = 2;
                        break;
                    case diag_LR:
                        current_st = diag_RL;
                        x++;
                        break;
                    case diag_RL:
                        current_st = diag_LL;
                        break;
                    case diag_RR:
                        current_st = diag_RL;
                        DIA(x);
                        DD90R();
                        x = 2;
                        break;
                }
                break;

            case 'R':
                switch (current_st) {
                    case ortho:
                        current_st = ortho_R;
                        FWD(x);
                        break;
                    case ortho_R:
                        current_st = ortho_RR;
                        break;
                    case ortho_L:
                        current_st = diag_LR;
                        SD45L();
                        x = 2;
                        break;
                    case ortho_LL:
                        current_st = diag_LR;
                        SD135L();
                        x = 2;
                        break;
                    case diag_RL:
                        current_st = diag_LR;
                        x++;
                        break;
                    case diag_LR:
                        current_st = diag_RR;
                        break;
                    case diag_LL:
                        current_st = diag_LR;
                        DIA(x);
                        DD90L();
                        x = 2;
                        break;
                }
                break;

            case 'S':
                switch (current_st) {
                    case st_init:
                        current_st = st_stop;
                        break;
                    case ortho:
                        current_st = st_stop;
                        FWD(x);
                        break;
                    case ortho_L:
                        current_st = st_stop;
                        SS90L();
                        FWD(1);
                        break;
                    case ortho_R:
                        current_st = st_stop;
                        SS90R();
                        FWD(1);
                        break;
                    case ortho_LL:
                        current_st = st_stop;
                        SS180L();
                        FWD(1);
                        break;
                    case ortho_RR:
                        current_st = st_stop;
                        SS180R();
                        FWD(1);
                        break;
                    case diag_LR:
                        current_st = st_stop;
                        DIA(x);
                        DS45R();
                        FWD(1);
                        break; 
                    case diag_RL:  
                        current_st = st_stop;
                        DIA(x);
                        DS45L();
                        FWD(1);
                        break;
                    case diag_LL:
                        current_st = st_stop;
                        DIA(x);
                        DS135L();
                        FWD(1);
                        break;
                    case diag_RR:
                        current_st = st_stop;
                        DIA(x);
                        DS135R();
                        FWD(1);
                        break;
                }
                break;
        }
    }
}