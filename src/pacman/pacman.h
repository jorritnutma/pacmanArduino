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
        bool updateGame(utils::direction dir);
        pacmanField* loadField();
        pacmanField* genTestField(uint8_t, uint8_t);
        void setRenderer(pacman_renderer* renderer){render = renderer;}
        void setField(pacmanField* pm_field){field = pm_field; dotsLeft = pm_field->getHeight() * pm_field->getWidth();}
        pacmanField* getField(){return field;}
        void pm_border_test();
        void clearScreen();
        Driver* getDriver(){return driver;}
        void init();
        utils::direction moveElementRandom(utils::position, utils::direction);

    protected:

    private:
        Driver* driver;
        pacman_renderer* render;
        pacmanField* field;
        utils::position pm_pos;
        utils::direction pm_dir;
        utils::position monster_pos[pacmanField::MAX_NUMBER_MONSTERS];
        utils::direction monster_dir[pacmanField::MAX_NUMBER_MONSTERS];
        utils::position monster_prev_pos[pacmanField::MAX_NUMBER_MONSTERS];
        uint16_t dotsLeft;
};

#endif // PACMAN_H
