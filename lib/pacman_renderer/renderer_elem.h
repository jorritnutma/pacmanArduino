#ifndef RENDERER_ELEM_H
#define RENDERER_ELEM_H

#include <Arduino.h>
#include "utils.h"
class renderer_elem{

protected :
	uint16_t x, y;
	uint8_t size;
	uint8_t step_size;
	uint16_t color;
	utils::direction prev_dir;
	uint8_t turn_leftover;
	utils::direction turn_prev_dir;

public :
	renderer_elem(uint8_t, uint8_t, uint16_t color);
	renderer_elem(uint16_t color);
	void updatePosition(utils::direction, uint8_t tileSize, uint8_t wall_width);
	
	uint16_t getXpos(){return x;}
	void setXpos(uint16_t x_n){x = x_n;}
	uint16_t getYpos(){return y;}
	void setYpos(uint16_t y_n ){ y = y_n;}

	uint16_t getColor(){return color;}
	void setColor(uint16_t color_n) {color = color_n;}

	uint8_t getSize(){return size;}
	void setSize(uint8_t size_n) {size = size_n;}

	uint8_t getStepSize(){return step_size;}
	void setStepSize(uint8_t step_size_n){step_size = step_size_n;}

	utils::direction getPrevDir(){return prev_dir;}
	void setPrevDir(utils::direction dir) {prev_dir = dir;}

	uint8_t getTurnLeftover(){return turn_leftover;}
	uint8_t getTurnPrevDir(){return turn_prev_dir;}
	void setTurningInfo(uint8_t leftover, utils::direction prev_dir){turn_leftover = leftover; turn_prev_dir = prev_dir;}
};

#endif //RENDERER_ELEM_H