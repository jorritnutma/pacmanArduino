#ifndef PACMAN_H
#define PACMAN_H

#include "pacman_renderer.h"
//#include<pacmanField.h>
#include "Arduino.h"


class pacman
{
    public:
        pacman();
        virtual ~pacman();
        bool updateGame();
        pacmanField* loadField();
        pacmanField* genTestField(uint8_t, uint8_t);
        void setRenderer(pacman_renderer* renderer){render = renderer;}
        void pm_border_test();
        void clearScreen();
        Driver* getDriver(){return driver;}
        void init();

    protected:

    private:
        Driver* driver;
        pacman_renderer* render;
        utils::position pm_pos;
        utils::direction pm_dir;
};

#endif // PACMAN_H
