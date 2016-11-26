#include <pacman_renderer.h>
#include <Driver.h>

// pacman_renderer::pacman_renderer(int width, int length, pacmanField* field){
//         tileSize = 1;
// }

pacman_renderer::pacman_renderer(int width, int length, Driver* driver, pacmanField* field){
    tileSize = 40;
    tft = driver;
}

int pacman_renderer::calculateTileSize(int width, int length){

}

void pacman_renderer::fillCircleHelper(int16_t x0, int16_t y0, int16_t r,
 uint8_t cornername, int16_t delta, uint16_t color) {

  int16_t f     = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x     = 0;
  int16_t y     = r;

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f     += ddF_y;
    }
    x++;
    ddF_x += 2;
    f     += ddF_x;

    if (cornername & 0x1) {
      tft->V_line(x0+x, y0-y, 2*y+1+delta, color);
      tft->V_line(x0+y, y0-x, 2*x+1+delta, color);
    }
    if (cornername & 0x2) {
    	tft->V_line(x0-x, y0-y, 2*y+1+delta, color);
      tft->V_line(x0-y, y0-x, 2*x+1+delta, color);
    }
  }
}

void pacman_renderer::fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) {
  tft->V_line(x0, y0-r, 2*r+1, color);
  fillCircleHelper(x0, y0, r, 3, 0, color);
}


utils::position pacman_renderer::drawPacman(utils::position pos, utils::direction dir){
    uint16_t r = (tileSize) >> 1;
    
    tft->Rectf(pos.x - r, pos.y-r, tileSize, tileSize, colors::BLACK);

    switch(dir){
      case utils::DOWN :
        tft->V_line(pos.x, pos.y-r, r+1, pacman_color);  
        break;
      case utils::UP :
        tft->V_line(pos.x, pos.y-1, r, pacman_color);  
        break;
      case utils::LEFT :
        tft->H_line(pos.x, pos.y, r+1, pacman_color);
        break;
      case utils::RIGHT :
        tft->H_line(pos.x - r, pos.y, r +1, pacman_color);      
    }
    
    
    int16_t f     = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x     = 0;
    int16_t y     = r;

    while (x<y) {
        if (f >= 0) {
          y--;
          ddF_y += 2;
          f     += ddF_y;
        }
        x++;
        ddF_x += 2;
        f     += ddF_x; 

        switch (dir) {
        case utils::DOWN :
            tft->V_line(pos.x+x, pos.y-y, y+x, pacman_color); //inner right
            tft->V_line(pos.x+y, pos.y-x, 2*x+1, pacman_color); //outer right
            tft->V_line(pos.x-x, pos.y-y, y+x, pacman_color); //inner left
            tft->V_line(pos.x-y, pos.y-x, 2*x+1, pacman_color); //outer left

            break;
        case utils::UP :
            tft->V_line(pos.x+x, pos.y-x-1, x+y, pacman_color); //inner right
            tft->V_line(pos.x+y, pos.y-x, 2*x, pacman_color);   //outer right
            tft->V_line(pos.x-x, pos.y-x-1, x+y, pacman_color);   //inner left
            tft->V_line(pos.x-y, pos.y-x, 2*x, pacman_color);   //outer left
            break;
        case utils::RIGHT :
            tft->H_line(pos.x-y, pos.y+y, x+y+1, pacman_color);
            break;
        case utils::LEFT:
            tft->H_line(pos.x-x, pos.y+x, x+y, pacman_color); //inner above
            tft->H_line(pos.x-x, pos.y+y, 2*x, pacman_color);   //outer above
            tft->H_line(pos.x-x, pos.y-x, x+y, pacman_color);   //inner below
            tft->H_line(pos.x-x, pos.y-y, 2*x, pacman_color);   //outer below
            break;

        }

    }
}
