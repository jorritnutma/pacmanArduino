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

void renderer_elem::updatePosition(utils::direction dir, uint8_t tileSize, uint8_t wall_width){
  turn_leftover = 0;
  int8_t dx = 0;
  int8_t dy = 0;
 
  int16_t x_offset = ((tileSize - wall_width - size) >> 1) + wall_width;
  int16_t y_offset = ((tileSize - wall_width - size) >> 1) + wall_width;
  
  utils::position pos = {x / tileSize , y / tileSize};
  utils::direction tmp_dir = dir;

  if(dir == utils::UP || dir == utils::DOWN ){
    dx = pos.x*tileSize + x_offset - x;
    if (prev_dir == utils::LEFT && dx + step_size < 0 ){
      tmp_dir = utils::LEFT;
      dx = -step_size;
    }
    else if (prev_dir == utils::RIGHT && dx - step_size > 0){
      tmp_dir = utils::RIGHT;
      dx = step_size;
    }
    else if ( prev_dir == utils::LEFT || prev_dir == utils::RIGHT) {
      dy = step_size - abs(dx);
      dy = dir == utils::DOWN ? dy : -dy;
      turn_leftover = abs(dx);
	  turn_prev_dir = prev_dir;
    }
    else {
      dy= step_size;
      dy = dir == utils::DOWN ? dy : -dy; 
    }
  }
  else {
    dy = pos.y*tileSize + y_offset - y;
    if (prev_dir == utils::UP && dy + step_size < 0 ){
      tmp_dir = utils::UP;
      dy = -step_size;
    }
    else if (prev_dir == utils::DOWN && dy - step_size > 0){
      tmp_dir = utils::DOWN;
      dy = step_size;
    }
    else if ( prev_dir == utils::UP || prev_dir == utils::DOWN) {
      dx = step_size - abs(dy);
      dx = dir == utils::RIGHT ? dx : dx * -1 ;
      turn_leftover = abs(dy);
	  turn_prev_dir = prev_dir;

    }
    else {
      dx = step_size ;
      dx = dir == utils::RIGHT ? dx : dx * -1 ;
    }

  }
  prev_dir = tmp_dir;
  x += dx;
  y += dy;
}