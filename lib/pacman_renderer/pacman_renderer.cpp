#include <pacman_renderer.h>
#include <Driver.h>
#include <renderer_elem_pm.h>
#include <renderer_elem_wall.h>
#include <renderer_elem_monster.h>
//#include "ILI9481_pacman.h"

pacman_renderer::pacman_renderer(Driver* driver, pacmanField* field){
    tileSize = calculateTileSize(0,0);
    wall_width = 2;
    tft = (ILI9481_pacman*) driver;
                  //renderer_elem_pm(size, stepSize, color)
    pm_prop = new renderer_elem_pm(30, 10, colors::YELLOW);

    uint16_t x0 = ((tileSize - wall_width - pm_prop->getSize()) >> 1) + wall_width;
    uint16_t y0 = ((tileSize - wall_width -  pm_prop->getSize()) >> 1) + wall_width;
    pm_prop->setXpos(x0);
    pm_prop->setYpos(y0);
    pm_prop->setPrevDir(utils::DOWN);
    bg_color=colors::BLACK;

    drawWalls(field);

    tft->drawPacmanInit(pm_prop);

    monster_prop = new renderer_elem_monster(24,5,colors::WHITE);
    monster_prop->setXpos(50);
    monster_prop->setYpos(50);
    tft->drawMonsterInit(monster_prop);
}

utils::position pacman_renderer::drawMonster(utils::direction){

  tft->drawMonster1(monster_prop, colors::BLACK);
}

void pacman_renderer::drawWalls(pacmanField* field){
  renderer_elem_wall* wall = new renderer_elem_wall(wall_width, colors::BLUE); 
  
  for(int i = 0; i<7; i++){
    wall->setXpos(i);
    for(int j = 0; j < 11; j++){
      wall->setYpos(j);
      tft->drawVertWall(wall, tileSize);
      tft->drawHorWall(wall, tileSize);
    }
  }
}

uint8_t pacman_renderer::calculateTileSize(int width, int length){
  return 40;
}


utils::position pacman_renderer::drawPacman(utils::direction dir){
  
  tft->drawPacman(pm_prop, dir, bg_color);
  
  updatePosition(pm_prop, dir);
  
  utils::position pos_n = {pm_prop->getXpos() / tileSize , pm_prop->getYpos() / tileSize};
  return pos_n;
}

void pacman_renderer::updatePosition(renderer_elem* prop, utils::direction dir){
  
  int16_t x0 = prop->getXpos();
  int16_t y0 = prop->getYpos();
  int8_t dx = 0;
  int8_t dy = 0;
 
  int16_t x_offset = ((tileSize - wall_width - prop->getSize()) >> 1) + wall_width;
  int16_t y_offset = ((tileSize - wall_width - prop->getSize()) >> 1) + wall_width;
  
  utils::position pos = {prop->getXpos() / tileSize , prop->getYpos() / tileSize};
  utils::direction tmp_dir = dir;

  if(dir == utils::UP || dir == utils::DOWN ){
    dx = pos.x*tileSize + x_offset - x0;
    if (prop->getPrevDir() == utils::LEFT && dx < 0 ){
      tmp_dir = utils::LEFT;
      dx = -prop->getStepSize();
    }
    else if (prop->getPrevDir() == utils::RIGHT && dx > 0){
      tmp_dir = utils::RIGHT;
      dx = prop->getStepSize();
    }
    else if ( prop->getPrevDir() == utils::LEFT || prop->getPrevDir() == utils::RIGHT) {
      dy = prop->getStepSize() - abs(dx);
      dy = dir == utils::DOWN ? dy : -dy;
    }
    else {
      dy= prop->getStepSize();
      dy = dir == utils::DOWN ? dy : -dy; 
    }
  }
  else {
    dy = pos.y*tileSize + y_offset - y0;
    if (prop->getPrevDir() == utils::UP && dy < 0 ){
      tmp_dir = utils::UP;
      dy = -prop->getStepSize();
    }
    else if (prop->getPrevDir() == utils::DOWN && dy > 0){
      tmp_dir = utils::DOWN;
      dy = prop->getStepSize();
    }
    else if ( prop->getPrevDir() == utils::UP || prop->getPrevDir() == utils::DOWN) {
      dx = prop->getStepSize() - abs(dy);
      dx = dir == utils::RIGHT ? dx : dx * -1 ;
    }
    else {
      dx = prop->getStepSize() ;
      dx = dir == utils::RIGHT ? dx : dx * -1 ;
    }

  }
  prop->setPrevDir(tmp_dir);
  prop->setXpos(x0+dx);
  prop->setYpos(y0+dy);
}

/* MORE OR LESS OBSOLETE FUNCTIONS */

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

void pacman_renderer::draw_pm_border(utils::direction dir){
  // tft->V_line(200, 0, 200, colors::GREEN);
  // tft->H_line(0, 100, 300, colors::GREEN);

  // tft->V_line(100, 100, 15, colors::YELLOW);
  
  // for(int i = 0; i < tileSize >> 1 ; i++){
  //   if (i <= pm_borders[i]){
  //     tft->drawPixel(i + 200, 100 - pm_borders[i], colors::BLUE);
  //     tft->drawPixel(200 - i, pm_borders[i] + 100, colors::BLUE);
  //     tft->drawPixel(200 - i, 100 - pm_borders[i] , colors::BLUE);
      
  //     if (dir == utils::direction::RIGHT){
  //       tft->drawPixel(i+200, 100 - i, colors::YELLOW);
  //       tft->drawPixel(i+200, 100 + i, colors::YELLOW);
  //     }
  //     else {
  //       tft->drawPixel(pm_borders[i] + 200, 100 - i, colors::YELLOW);
  //       tft->drawPixel(pm_borders[i] + 200, 100 + i, colors::YELLOW);
        
  //     }
        
  //     tft->drawPixel(i + 200, 100 + pm_borders[i], colors::BLUE);
      
  //     tft->drawPixel(200 - pm_borders[i], i + 100, colors::YELLOW);
  //     tft->drawPixel(200 - pm_borders[i], 100 - i , colors::YELLOW);    
  //   }
  // }  
}

/***************
**OBSOLETE!!!***
****************
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
*/