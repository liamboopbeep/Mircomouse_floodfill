#include <string>
#include "..\Control\Control.h"

enum States {st_init, ortho, ortho_L, ortho_R,st_stop};

void simplestatemachine(const std::string& robot_commands){
    int x;
    States current_st = st_init;
    for (char cmd : robot_commands){
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