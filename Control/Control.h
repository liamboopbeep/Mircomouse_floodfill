#pragma once

// Forward movement with scaling
class Control {

public:

    static void FWD(int x = 1);

    // Snap Spins (90° and 180°)
    static void SS90L();
    static void SS90R();
    static void SS180L();
    static void SS180R();

    // Diagonal movement
    static void DIA(int x = 1);

    // Diagonal Right
    static void DS45R();
    static void DS135R();
    static void SD45R();
    static void SD135R();
    static void DD90R();

    // Diagonal Left
    static void DS45L();
    static void DS135L();
    static void SD45L();
    static void SD135L();
    static void DD90L();


};
