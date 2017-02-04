//Technical support:goodtft@163.com
// Breakout/Arduino UNO pin usage:
// LCD Data Bit :   7   6   5   4   3   2   1   0
// Uno dig. pin :   7   6   5   4   3   2   9   8
// Uno port/pin : PD7 PD6 PD5 PD4 PD3 PD2 PB1 PB0
// Mega dig. pin:  29  28  27  26  25  24  23  22
#include <ILI9481_driver.h>
#include <utils.h>

#define TFTWIDTH   320
#define TFTHEIGHT  480

ILI9481_driver::ILI9481_driver() : Driver (TFTWIDTH, TFTHEIGHT){
    Lcd_Init();
    for(int p=0;p<10;p++) {
        pinMode(p,OUTPUT);
    }
    pinMode(A0,OUTPUT);
    pinMode(A1,OUTPUT);
    pinMode(A2,OUTPUT);
    pinMode(A3,OUTPUT);
    pinMode(A4,OUTPUT);
    digitalWrite(A0, HIGH);
    digitalWrite(A1, HIGH);
    digitalWrite(A2, HIGH);
    digitalWrite(A3, HIGH);
    digitalWrite(A4, HIGH);
    Lcd_Init();
    LCD_Clear(0xf800);
}

void ILI9481_driver::drawPixel(int16_t x, int16_t y, uint16_t color){
  
//Clip
if((x < 0) || (y < 0) || (x >= TFTWIDTH) || (y >= TFTHEIGHT)) return;

Lcd_Write_Com(0x02c); //write_memory_start
 digitalWrite(LCD_RS,HIGH);
 digitalWrite(LCD_CS,LOW);
 Address_set(x,y,x,y);

Lcd_Write_Data(color>>8);
Lcd_Write_Data(color);

 digitalWrite(LCD_CS,HIGH);

 // CS_ACTIVE;
 //   setAddrWindow(x, y, _width-1, _height-1);
 //   CS_ACTIVE;
 //   CD_COMMAND;
 //   write8(0x2C);
 //   CD_DATA;
 //   write8(color >> 8); write8(color);
 // }

 // CS_IDLE;
}
void ILI9481_driver::Lcd_Write_Bus(unsigned char d)
{
  PORTD = (PORTD & B00000011) | ((d) & B11111100);
  PORTB = (PORTB & B11111100) | ((d) & B00000011);
  PORTC &= ~WR_MASK;
  PORTC|=  WR_MASK;

}

void ILI9481_driver::Lcd_Write_Com(unsigned char VH)
{
   PORTC &= ~RS_MASK;
  Lcd_Write_Bus(VH);
}

void ILI9481_driver::Lcd_Write_Data(unsigned char VH)
{
  PORTC |= RS_MASK;
  Lcd_Write_Bus(VH);
}

void ILI9481_driver::Lcd_Write_Com_Data(unsigned char com,unsigned char dat)
{
  Lcd_Write_Com(com);
  Lcd_Write_Data(dat);
}

void ILI9481_driver::Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2)
{
        Lcd_Write_Com(0x2a);
	Lcd_Write_Data(x1>>8);
	Lcd_Write_Data(x1);
	Lcd_Write_Data(x2>>8);
	Lcd_Write_Data(x2);
        Lcd_Write_Com(0x2b);
	Lcd_Write_Data(y1>>8);
	Lcd_Write_Data(y1);
	Lcd_Write_Data(y2>>8);
	Lcd_Write_Data(y2);
	Lcd_Write_Com(0x2c);
}

void ILI9481_driver::Lcd_Init(void)
{
  digitalWrite(LCD_REST,HIGH);
  delay(5);
  digitalWrite(LCD_REST,LOW);
  delay(15);
  digitalWrite(LCD_REST,HIGH);
  delay(15);

  digitalWrite(LCD_CS,HIGH);
  digitalWrite(LCD_WR,HIGH);
  digitalWrite(LCD_CS,LOW);  //CS

    Lcd_Write_Com(0x11);
  delay(20);
  Lcd_Write_Com(0xD0);
  Lcd_Write_Data(0x07);
  Lcd_Write_Data(0x42);
  Lcd_Write_Data(0x18);

  Lcd_Write_Com(0xD1);
  Lcd_Write_Data(0x00);
  Lcd_Write_Data(0x07);//07
  Lcd_Write_Data(0x10);

  Lcd_Write_Com(0xD2);
  Lcd_Write_Data(0x01);
  Lcd_Write_Data(0x02);

  Lcd_Write_Com(0xC0);
  Lcd_Write_Data(0x10);
  Lcd_Write_Data(0x3B);
  Lcd_Write_Data(0x00);
  Lcd_Write_Data(0x02);
  Lcd_Write_Data(0x11);

  Lcd_Write_Com(0xC5);
  Lcd_Write_Data(0x03);
  Lcd_Write_Com(0x36);
  Lcd_Write_Data(0x0A);

  Lcd_Write_Com(0x3A);
  Lcd_Write_Data(0x55);

  Lcd_Write_Com(0x2A);
  Lcd_Write_Data(0x00);
  Lcd_Write_Data(0x00);
  Lcd_Write_Data(0x01);
  Lcd_Write_Data(0x3F);

  Lcd_Write_Com(0x2B);
  Lcd_Write_Data(0x00);
  Lcd_Write_Data(0x00);
  Lcd_Write_Data(0x01);
  Lcd_Write_Data(0xE0);
  delay(120);
  Lcd_Write_Com(0x29);
  Lcd_Write_Com(0x002c);
}

void ILI9481_driver::H_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c)
{
  unsigned int i,j;
  Lcd_Write_Com(0x02c); //write_memory_start
  digitalWrite(LCD_RS,HIGH);
  digitalWrite(LCD_CS,LOW);
  l=l+x;
  Address_set(x,y,l,y);
  j=l;
  for(i=1;i<=j;i++)
  {
    Lcd_Write_Data(c>>8);
    Lcd_Write_Data(c);
  }
  digitalWrite(LCD_CS,HIGH);
}

void ILI9481_driver::V_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c)
{
  unsigned int i,j;
  Lcd_Write_Com(0x02c); //write_memory_start
  digitalWrite(LCD_RS,HIGH);
  digitalWrite(LCD_CS,LOW);
  l=l+y;
  Address_set(x,y,x,l);
  //j=l*2;
  j = l;
  for(i=1;i<=j;i++)
  {
    Lcd_Write_Data(c>>8);
    Lcd_Write_Data(c);
  }
  digitalWrite(LCD_CS,HIGH);
}

void ILI9481_driver::Rect(unsigned int x,unsigned int y,unsigned int w,unsigned int h,unsigned int c)
{
  H_line(x  , y  , w, c);
  H_line(x  , y+h, w, c);
  V_line(x  , y  , h, c);
  V_line(x+w, y  , h, c);
}

void ILI9481_driver::Rectf(unsigned int x,unsigned int y,unsigned int w,unsigned int h,unsigned int c)
{
  unsigned int i;
  for(i=0;i<h;i++)
  {
    H_line(x  , y  , w, c);
    H_line(x  , y+i, w, c);
  }
}

void ILI9481_driver::LCD_Clear(unsigned int j)
{
  unsigned int i,m;

  Lcd_Write_Com(0x02c); //write_memory_start
  digitalWrite(LCD_RS,HIGH);
  digitalWrite(LCD_CS,LOW);
Address_set(0,0,319,479);

  for(i=0;i<320;i++)
    for(m=0;m<480;m++)
    {
      Lcd_Write_Data(j>>8);
      Lcd_Write_Data(j);

    }
  digitalWrite(LCD_CS,HIGH);
}

void ILI9481_driver::drawPacman(uint16_t x, uint16_t y, uint16_t dx, uint16_t dy){
  uint16_t i = 0;

  while (i < 20){
    drawPixel(x+i, circleBoundaries[i], colors::GREEN);
    i++;
  }
  
}

void ILI9481_driver::calcPacmanBoundaries(uint16_t r){

    int16_t f     = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x     = 0;
    int16_t y     = r;
    pacmanRadius  = r;

    while (x<r) {
        if (f >= 0) {
          y--;
          ddF_y += 2;
          f     += ddF_y;
        }
        x++;
        ddF_x += 2;
        f     += ddF_x;
        circleBoundaries[x] = y;
      }

}

// For I/O macros that were left undefined, declare function
// versions that reference the inline macros just once:

// TODO: clean up ifndef
//
//#ifndef write8
//void ILI9481_driver::write8(uint8_t value) {
//  write8inline(value);
//}
//#endif
//
//#ifdef read8isFunctionalized
//uint8_t ILI9481_driver::read8fn(void) {
//  uint8_t result;
//  read8inline(result);
//  return result;
//}
//#endif
//
//#ifndef setWriteDir
//void ILI9481_driver::setWriteDir(void) {
//  setWriteDirInline();
//}
//#endif
//
//#ifndef setReadDir
//void ILI9481_driver::setReadDir(void) {
//  setReadDirInline();
//}
//#endif
//
//#ifndef writeRegister8
//void ILI9481_driver::writeRegister8(uint8_t a, uint8_t d) {
//  writeRegister8inline(a, d);
//}
//#endif
//
//#ifndef writeRegister16
//void ILI9481_driver::writeRegister16(uint16_t a, uint16_t d) {
//  writeRegister16inline(a, d);
//}
//#endif
//
//#ifndef writeRegisterPair
//void ILI9481_driver::writeRegisterPair(uint8_t aH, uint8_t aL, uint16_t d) {
//  writeRegisterPairInline(aH, aL, d);
//}
//#endif
//
//void ILI9481_driver::writeRegister24(uint8_t r, uint32_t d) {
//  CS_ACTIVE;
//  CD_COMMAND;
//  write8(r);
//  CD_DATA;
//  delayMicroseconds(10);
//  write8(d >> 16);
//  delayMicroseconds(10);
//  write8(d >> 8);
//  delayMicroseconds(10);
//  write8(d);
//  CS_IDLE;
//
//}
//
//void ILI9481_driver::writeRegister32(uint8_t r, uint32_t d) {
//  CS_ACTIVE;
//  CD_COMMAND;
//  write8(r);
//  CD_DATA;
//  delayMicroseconds(10);
//  write8(d >> 24);
//  delayMicroseconds(10);
//  write8(d >> 16);
//  delayMicroseconds(10);
//  write8(d >> 8);
//  delayMicroseconds(10);
//  write8(d);
//  CS_IDLE;
//
//}
