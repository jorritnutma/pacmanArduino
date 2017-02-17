
#ifndef RENDERER_ELEM_WALL_H
#define RENDERER_ELEM_WALL_H
#include "renderer_elem.h"

class renderer_elem_wall : public renderer_elem {

private :
	uint8_t wall_width;

public :
	renderer_elem_wall(uint8_t width, uint16_t col);
	uint8_t getWidth(){return wall_width;}

};

#endif //RENDERER_ELEM_WALL_H