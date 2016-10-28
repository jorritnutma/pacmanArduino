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
        pacman_renderer* getRenderer(){return render;}

    protected:

    private:
        pacman_renderer* render;
        //pacmanField* field;
};

#endif // PACMAN_H
