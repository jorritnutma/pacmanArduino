
#ifndef RENDERER_ELEM_PM_H
#define RENDERER_ELEM_PM_H
#include "renderer_elem.h"

class renderer_elem_pm : public renderer_elem {

private :
	bool mouth_open;

public :
	renderer_elem_pm(uint8_t size_n, uint8_t step_size_n, uint16_t col);
	bool getMouthOpen(){return mouth_open;}
	void setMouthOpen(bool open){mouth_open = open;}

};

#endif //RENDERER_ELEM_PM_H