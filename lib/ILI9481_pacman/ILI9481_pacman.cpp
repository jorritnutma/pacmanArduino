
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
 
  uint16_t x = pm_prop->getXpos(), y = pm_prop->getYpos();
  uint8_t i,j,k;
  uint8_t r = pm_prop->getSize() >> 1;
  uint8_t c = (uint8_t) pm_prop->getColor();
  uint8_t c_high = (uint8_t) (pm_prop->getColor() >> 8);
  
  setupRectDrawing(x, y, pm_prop->getSize(), pm_prop->getSize());
 
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

void ILI9481_pacman::drawMonsterInit(renderer_elem_monster* prop){
  if (prop->getSize() > MAX_TILE_SIZE){
    return;
  }
  
  int16_t f = 1 - (prop->getSize() >> 1);
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * (prop->getSize() >> 1);
  int8_t x = 0;
  int8_t y = (prop->getSize() >> 1);

  const uint8_t oneHalf = prop->getSize() >> 1;
  const uint8_t oneFourth = prop->getSize() >> 2;
  const uint8_t oneEight = prop->getSize()>>3;
  const uint8_t th = prop->getSize() / 6;
  const uint8_t dth = th / oneEight;

  monster_border_left[0] = oneHalf;
  monster_border_right[0] = oneHalf;
  
  for (uint8_t i = 1; i <= oneFourth; i++) {
    if ( i <= oneEight ) {
      monster_border_right[i] = oneHalf;
      monster_border_right[oneHalf - i + 1] = oneHalf;
    }
    else{
      uint8_t triangle = oneHalf - ((i - oneEight) * dth);
      monster_border_right[i] = triangle;
      monster_border_right[oneHalf - i + 1] = triangle; 
    }

  }

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;

    monster_border_left[x] = y;
    monster_border_left[y] = x;
  }
}

void ILI9481_pacman::drawMonster1(renderer_elem_monster* prop, uint16_t bg_color){
  unsigned int i,j;
  uint16_t y0=100, x0=100;

  for (int i = 0; i < (prop->getSize() >> 1); i++)
  {
    drawPixel(x0 + monster_border_left[i], y0 - i, colors::WHITE);
    drawPixel(x0 - monster_border_right[i], y0 - i, colors::WHITE);

    drawPixel(x0 + monster_border_left[i], y0 + i, colors::WHITE);
    drawPixel(x0 - monster_border_right[i], y0 + i, colors::WHITE);
  }

  uint16_t x = prop->getXpos() ;
  uint16_t y = prop->getYpos();
  uint16_t h = y + prop->getSize();
  uint16_t w = x + prop->getSize();
  uint16_t r = prop->getSize() >> 1;
  uint8_t c = (uint8_t) prop->getColor();
  uint8_t c_high = (uint8_t) (prop->getColor() >> 8);
      

  // Lcd_Write_Com(0x02c); //write_memory_start
  // digitalWrite(LCD_RS,HIGH);
  // digitalWrite(LCD_CS,LOW);
  
  // Address_set(x, y, w, h);

  // for (i = 0; i <= prop->getSize(); i++) {
  //   if ( i < r ) {
  //     for(j=0; j <= prop->getSize(); j++){
  //       if ( j >= r - monster_borders[r-i] && j <= r + monster_borders[r-i] ){
  //         Lcd_Write_Data(c_high);
  //         Lcd_Write_Data(c);
  //       }
  //       else {
  //         Lcd_Write_Data(bg_color>>8);
  //         Lcd_Write_Data(bg_color); 
  //       }
  //     }
  //   }
  //   else {
  //     for(j=0; j <= prop->getSize(); j++){
  //       Lcd_Write_Data(c_high);
  //       Lcd_Write_Data(c);
  //     }
  //   }
  // }

  // digitalWrite(LCD_CS,HIGH);
}


// void ILI9481_pacman::drawMonster(renderer_elem_monster* prop, uint16_t bg_color){
//   unsigned int i,j;
  
//   uint16_t x = prop->getXpos() ;
//   uint16_t y = prop->getYpos();
//   uint16_t h = y + prop->getSize();
//   uint16_t w = x + prop->getSize();
//   uint16_t r = prop->getSize() >> 1;
//   uint8_t c = (uint8_t) prop->getColor();
//   uint8_t c_high = (uint8_t) (prop->getColor() >> 8);
      

//   Lcd_Write_Com(0x02c); //write_memory_start
//   digitalWrite(LCD_RS,HIGH);
//   digitalWrite(LCD_CS,LOW);
  
//   Address_set(x, y, w, h);

//   for (i = 0; i <= prop->getSize(); i++) {
//     if ( i < r ) {
//       for(j=0; j <= prop->getSize(); j++){
//         if ( j >= r - monster_borders[r-i] && j <= r + monster_borders[r-i] ){
//           Lcd_Write_Data(c_high);
//           Lcd_Write_Data(c);
//         }
//         else {
//           Lcd_Write_Data(bg_color>>8);
//           Lcd_Write_Data(bg_color); 
//         }
//       }
//     }
//     else {
//       for(j=0; j <= prop->getSize(); j++){
//         Lcd_Write_Data(c_high);
//         Lcd_Write_Data(c);
//       }
//     }
//   }

//   digitalWrite(LCD_CS,HIGH);
// }

void ILI9481_pacman::drawVertWall(renderer_elem_wall* wall_prop, uint8_t tileSize){
  uint16_t x = wall_prop->getXpos() * tileSize;
  uint16_t y = wall_prop->getYpos() * tileSize;
  Rectf(x,y, wall_prop->getWidth(), tileSize, wall_prop->getColor() );
}

void ILI9481_pacman::drawHorWall(renderer_elem_wall* wall_prop, uint8_t tileSize){
  uint16_t x = wall_prop->getXpos() * tileSize;
  uint16_t y = wall_prop->getYpos() * tileSize;
  Rectf(x, y, tileSize,  wall_prop->getWidth(), wall_prop->getColor());
}