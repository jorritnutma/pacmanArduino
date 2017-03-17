#ifndef PACMANFIELD_H
#define PACMANFIELD_H

#include "utils.h"

class pacmanField
{
    const static uint8_t MAX_H_LINES = 32;
    const static uint8_t MAX_V_LINES = 16;


    public:
        enum dot{
            no,
            yes,
            special
        };
        const static uint8_t MAX_NUMBER_MONSTERS = 6;
        const static uint8_t MAX_SPECIAL_DOTS = 10;
        pacmanField(uint8_t, uint8_t, utils::position, utils::position);
        virtual ~pacmanField();
        bool hasWall(uint8_t x, uint8_t y, int dir);
        bool hasSpecialDot(uint8_t x, uint8_t y);
        void specialDotEaten(uint8_t x, uint8_t y);
        bool hasDot(uint8_t x, uint8_t y);
        void eatDot(uint8_t x, uint8_t y);
        dot getDotType(utils::position pos);
        void assignDot(utils::position);
        void assignSpecialDots();
        void assignVWall(uint16_t, uint16_t, uint8_t);
        void assignHWall(uint16_t, uint8_t);
        uint8_t getWidth(){return x_tiles;}
        uint8_t getHeight(){return y_tiles;}
        utils::position getMonsterStart(){return monster_start_pos;}
        utils::position getPacmanStart(){return pm_start_pos;}


    private:
    	uint8_t x_tiles, y_tiles;
    	uint16_t h_walls[MAX_H_LINES];
        uint16_t v_walls0[MAX_V_LINES];
        uint16_t v_walls1[MAX_V_LINES];
        uint16_t dots[MAX_H_LINES];
        utils::position pm_start_pos;
        utils::position monster_start_pos;
        utils::position special_dots[MAX_SPECIAL_DOTS];
};
#endif // PACMANFIELD_H
