#ifndef ROBOT_MOVEMENT_H
#define ROBOT_MOVEMENT_H

// Wall detection
bool wallFront();
bool wallRight();
bool wallLeft();

// Basic movement
void moveForward();
void turnRight();
void turnLeft();

// Forward movement with scaling
void FWD(float x = 1.0);

// Snap Spins (90° and 180°)
void SS90L();
void SS90R();
void SS180L();
void SS180R();

// Diagonal movement
void DIA(float x = 1.0);

// Diagonal Right
void DS45R();
void DS135R();
void SD45R();
void SD135R();
void DD90R();

// Diagonal Left
void DS45L();
void DS135L();
void SD45L();
void SD135L();
void DD90L();

#endif
