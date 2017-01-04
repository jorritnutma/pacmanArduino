#ifndef PACMAN_H
#define PACMAN_H

#include "pacman_renderer.h"
//#include<pacmanField.h>
//#include "pacman_utils.h"


class pacman
{
    public:
        pacman();
        virtual ~pacman();
        bool updateGame();
        pacmanField* loadField();
        void setRenderer(pacman_renderer* renderer){render = renderer;}
        void pm_border_test();
        void clearScreen();
        Driver* getDriver(){return driver;}

    protected:

    private:
        Driver* driver;
        pacman_renderer* render;
        utils::position pm_pos;
        
};

#endif // PACMAN_H
