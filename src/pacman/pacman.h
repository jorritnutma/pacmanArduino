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
        void updateGame();
        pacmanField* loadField();
        void setRenderer(pacman_renderer* renderer){render = renderer;}
        Driver* getDriver(){return driver;}
        void init();

    protected:

    private:
        Driver* driver;
        pacman_renderer* render;
        utils::position pm_pos;
        
};

#endif // PACMAN_H
