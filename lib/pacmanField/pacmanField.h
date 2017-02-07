#ifndef PACMANFIELD_H
#define PACMANFIELD_H

#include "utils.h"

class pacmanField
{
    const static uint8_t MAX_H_LINES = 32;
    const static uint8_t MAX_V_LINES = 16;
    public:
        pacmanField(uint8_t, uint8_t);
        virtual ~pacmanField();
        bool hasWall(uint8_t x, uint8_t y, utils::direction dir);
        void assignVWall(uint16_t, uint16_t, uint8_t);
        void assignHWall(uint16_t, uint8_t);

    private:
    	uint8_t x_tiles, y_tiles;
    	uint8_t tileSize;
    	uint16_t h_walls[MAX_H_LINES];
        uint16_t v_walls0[MAX_V_LINES];
        uint16_t v_walls1[MAX_V_LINES];
};
#endif // PACMANFIELD_H
