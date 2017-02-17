#include <renderer_elem.h>

renderer_elem::renderer_elem(uint8_t size_n, uint8_t step_size_n, uint16_t col){
	x = 0;
	y = 0;
	size = size_n;
	step_size = step_size_n;
	color = col;
}

renderer_elem::renderer_elem(uint16_t col){
	x = 0;
	y = 0;
	size = 0;
	step_size = 0;
	color = col;
}