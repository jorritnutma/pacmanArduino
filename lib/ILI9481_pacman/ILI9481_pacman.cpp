
#include "ILI9481_pacman.h"
#include "ILI9481_driver.h"

ILI9481_pacman::ILI9481_pacman() : ILI9481_driver() {


}

void ILI9481_pacman::drawPacmanInit(renderer_elem_pm* pm_prop){
  if (pm_prop->getSize() > MAX_TILE_SIZE){
    return;
  }
  
  int16_t f = 1 - (pm_prop->getSize() >> 1);
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * (pm_prop->getSize() >> 1);
  int16_t x = 0;
  int16_t y = (pm_prop->getSize() >> 1);

  pm_borders[0] = pm_prop->getSize() >> 1;
  
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

void ILI9481_pacman::drawPacman( renderer_elem_pm* pm_prop, utils::direction dir, uint16_t bg_color)
{

  unsigned int i,j,k;
  
  uint16_t x = pm_prop->getXpos() ;
  uint16_t y = pm_prop->getYpos();
  uint16_t h = y + pm_prop->getSize();
  uint16_t w = x + pm_prop->getSize();
  uint16_t r = pm_prop->getSize() >> 1;
  uint8_t c = (uint8_t) pm_prop->getColor();
  uint8_t c_high = (uint8_t) (pm_prop->getColor() >> 8);
      

  Lcd_Write_Com(0x02c); //write_memory_start
  digitalWrite(LCD_RS,HIGH);
  digitalWrite(LCD_CS,LOW);
  
  Address_set(x, y, w, h);

  for (i = 0; i <= pm_prop->getSize(); i++) {
    if ( i < r ) {
      k = r-i ;
    }
    else {
      k = i-r;
    }
    for(j=0; j <= pm_prop->getSize(); j++){
      if ( j >= r - pm_borders[k] && j <= r + pm_borders[k] ){
        Lcd_Write_Data(c_high);
        Lcd_Write_Data(c);
      }
      else {
        Lcd_Write_Data(bg_color>>8);
        Lcd_Write_Data(bg_color); 
      }
    }
  }

  digitalWrite(LCD_CS,HIGH);
  
  uint16_t x0, y0, x1, y1;
  switch (pm_prop->getPrevDir()){
    case utils::DOWN :
      Rectf(x, y - pm_prop->getStepSize(), pm_prop->getSize(), pm_prop->getStepSize() - 1, bg_color);
      x0 = x + (r >> 1);
      y0 = y + pm_prop->getSize();
      x1 = x + r + (r>>1);
      y1 = y + pm_prop->getSize();
      break;
    case utils::UP :
      Rectf(x, y+pm_prop->getSize()+1, pm_prop->getSize(), pm_prop->getStepSize(), bg_color);
      x0 = x + (r >> 1);
      y0 = y;
      x1 = x + r + (r>>1);
      y1 = y;
      break;
    case utils::RIGHT :
      Rectf(x - pm_prop->getStepSize(), y, pm_prop->getStepSize() - 1, pm_prop->getSize(), bg_color);
      x0 = x + pm_prop->getSize();
      y0 = y + (r>>1);
      x1 = x + pm_prop->getSize();
      y1 = y + r + (r>>1);
      break;
    case utils::LEFT :
      Rectf(x + pm_prop->getSize() + 1, y, pm_prop->getStepSize(), pm_prop->getSize(), bg_color);
      x0 = x;
      y0 = y + (r>>1);
      x1 = x;
      y1 = y + r + (r>>1);
      break;      
  }

  if(pm_prop->getMouthOpen()){
    fillTriangle(x0, y0, x + r, y + r, x1, y1, bg_color);
    pm_prop->setMouthOpen(false);
  }
  else {
    pm_prop->setMouthOpen(true);
  }
}
