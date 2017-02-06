#include <pacman_renderer.h>
#include <Driver.h>
#include <renderer_elem.h>

// pacman_renderer::pacman_renderer(int width, int length, pacmanField* field){
//         tileSize = 1;
// }

pacman_renderer::pacman_renderer(int width, int length, Driver* driver, pacmanField* field){
    
    tileSize = 39;
    tft = driver;
    pm_x = 200;
    pm_y = 200;
    pm_prop = new renderer_elem(20, 5, colors::YELLOW);
}

int pacman_renderer::calculateTileSize(int width, int length){

}

void pacman_renderer::draw_pm_border(utils::direction dir){
  tft->V_line(200, 0, 200, colors::GREEN);
  tft->H_line(0, 100, 300, colors::GREEN);

  tft->V_line(100, 100, 15, colors::YELLOW);
  
  for(int i = 0; i < tileSize >> 1 ; i++){
    if (i <= pm_borders[i]){
      tft->drawPixel(i + 200, 100 - pm_borders[i], colors::BLUE);
      tft->drawPixel(200 - i, pm_borders[i] + 100, colors::BLUE);
      tft->drawPixel(200 - i, 100 - pm_borders[i] , colors::BLUE);
      
      if (dir == utils::direction::RIGHT){
        tft->drawPixel(i+200, 100 - i, colors::YELLOW);
        tft->drawPixel(i+200, 100 + i, colors::YELLOW);
      }
      else {
        tft->drawPixel(pm_borders[i] + 200, 100 - i, colors::YELLOW);
        tft->drawPixel(pm_borders[i] + 200, 100 + i, colors::YELLOW);
        
      }
        
      tft->drawPixel(i + 200, 100 + pm_borders[i], colors::BLUE);
      
      tft->drawPixel(200 - pm_borders[i], i + 100, colors::YELLOW);
      tft->drawPixel(200 - pm_borders[i], 100 - i , colors::YELLOW);    
    }
  }  
}

utils::position pacman_renderer::drawPacmanPreCalc(utils::direction dir){
  renderer_elem* pm_prop_test = new renderer_elem(38, 5, colors::YELLOW);
  pm_prop_test->setXpos(pm_x);
  pm_prop_test->setYpos(pm_y);

  tft->drawPacman(pm_borders, pm_prop_test, dir);
  pm_y+=5;
}

// Draw a circle outline
void pacman_renderer::drawCircle(int16_t x0, int16_t y0, int16_t r,
 uint16_t color) {
  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;

  tft->drawPixel(x0  , y0+r, color);
  tft->drawPixel(x0  , y0-r, color);
  tft->drawPixel(x0+r, y0  , color);
  tft->drawPixel(x0-r, y0  , color);

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;

    tft->drawPixel(x0 + x, y0 + y, color);
    tft->drawPixel(x0 - x, y0 + y, color);
    tft->drawPixel(x0 + x, y0 - y, color);
    tft->drawPixel(x0 - x, y0 - y, color);
    tft->drawPixel(x0 + y, y0 + x, color);
    tft->drawPixel(x0 - y, y0 + x, color);
    tft->drawPixel(x0 + y, y0 - x, color);
    tft->drawPixel(x0 - y, y0 - x, color);
  }
}

void pacman_renderer::drawPacmanInit(uint16_t r){
  if (r > static_tile_size >> 1){
    return;
  }

  //tileSize = r << 1;
  
  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;

  pm_borders[0] = r;
  
  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;

    pm_borders[x] = y;
    pm_borders[y] = x;
  }
}



utils::position pacman_renderer::drawPacman(utils::direction dir){

    uint16_t r = (pm_prop->getSize()) >> 1;
    uint16_t x0 = pm_prop->getXpos() + (tileSize >> 1) + 1;
    uint16_t y0 = pm_prop->getYpos() + (tileSize >> 1);
    uint16_t color = pm_prop->getColor();
    tft->Rectf_imp(pm_prop->getXpos(), pm_prop->getYpos() - 1, tileSize + 1, tileSize, colors::BLACK);

    switch(dir){
      case utils::DOWN :
        y0 += pm_prop->getStepSize();
        tft->V_line(x0, y0-r, r, color);  
        break;
      case utils::UP :
        y0 -= pm_prop->getStepSize();
        tft->V_line(x0, y0, r, color);  
        break;
      case utils::LEFT :
        x0 -= pm_prop->getStepSize();
        tft->H_line(x0, y0, r, color);
        break;
      case utils::RIGHT :
        x0 += pm_prop->getStepSize();
        tft->H_line(x0 - r, y0, r, color);      
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
            tft->V_line(x0+x, y0-y, y+x, color); //inner right
            tft->V_line(x0+y, y0-x, 2*x+1, color); //outer right
            tft->V_line(x0-x, y0-y, y+x, color); //inner left
            tft->V_line(x0-y, y0-x, 2*x+1, color); //outer left
            break;
        case utils::UP :
            tft->V_line(x0+x, y0-x-1, x+y, color); //inner right
            tft->V_line(x0+y, y0-x, 2*x, color);   //outer right
            tft->V_line(x0-x, y0-x-1, x+y, color);   //inner left
            tft->V_line(x0-y, y0-x, 2*x, color);   //outer left
            break;
        case utils::RIGHT :
            tft->H_line(x0-y, y0+y, x+y+1, color);
            break;
        case utils::LEFT:
            tft->H_line(x0-x, y0+x, x+y, color); //inner above
            tft->H_line(x0-x, y0+y, 2*x, color);   //outer above
            tft->H_line(x0-x, y0-x, x+y, color);   //inner below
            tft->H_line(x0-x, y0-y, 2*x, color);   //outer below
            break;

        }
    }

    pm_prop->setXpos(x0 - (tileSize >> 1) - 1);
    pm_prop->setYpos(y0 - (tileSize >> 1));

    utils::position pos_n = {2,2};

    if(pm_prop->getYpos() > 300 ){
      pos_n.y=5;
    }
    else if (pm_prop->getYpos() < 20){
      pos_n.y=1;
    }
    
    return pos_n;
}
