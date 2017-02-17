//Technical support:goodtft@163.com
// Breakout/Arduino UNO pin usage:
// LCD Data Bit :   7   6   5   4   3   2   1   0
// Uno dig. pin :   7   6   5   4   3   2   9   8
// Uno port/pin : PD7 PD6 PD5 PD4 PD3 PD2 PB1 PB0
// Mega dig. pin:  29  28  27  26  25  24  23  22
#include <ILI9481_driver.h>

#define TFTWIDTH   320
#define TFTHEIGHT  480

//TODO: to be moved togher with the drawtriangle function
#define _swap_int16_t(a, b) { int16_t t = a; a = b; b = t; }

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
    
    //LCD_Clear(0xf800);
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
  unsigned int i;
  Lcd_Write_Com(0x02c); //write_memory_start
  digitalWrite(LCD_RS,HIGH);
  digitalWrite(LCD_CS,LOW);
  l=l+x;
  Address_set(x,y,l,y);
  for(i=1;i<=l;i++)
  {
    Lcd_Write_Data(c>>8);
    Lcd_Write_Data(c);
  }
  digitalWrite(LCD_CS,HIGH);
}

void ILI9481_driver::V_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c)
{
  unsigned int i;
  Lcd_Write_Com(0x02c); //write_memory_start
  digitalWrite(LCD_RS,HIGH);
  digitalWrite(LCD_CS,LOW);
  l=l+y;
  Address_set(x,y,x,l);
  for(i=y;i<=l;i++)
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

  unsigned int i,j;
  Lcd_Write_Com(0x02c); //write_memory_start
  digitalWrite(LCD_RS,HIGH);
  digitalWrite(LCD_CS,LOW);
  h=h+y;
  w=w+x;
  Address_set(x,y,w,h);
  
  for(i = y; i <= h;i++)
  {
    for(j=x; j <= w; j++){
      Lcd_Write_Data(c>>8);
      Lcd_Write_Data(c);
    }
  }
  digitalWrite(LCD_CS,HIGH);

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

//TODO: to be moved to some adafruit_GFX like class with sophisticated drawing functions
void ILI9481_driver::fillTriangle(int16_t x0, int16_t y0,
 int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {

  int16_t a, b, y, last;

  // Sort coordinates by Y order (y2 >= y1 >= y0)
  if (y0 > y1) {
    _swap_int16_t(y0, y1); _swap_int16_t(x0, x1);
  }
  if (y1 > y2) {
    _swap_int16_t(y2, y1); _swap_int16_t(x2, x1);
  }
  if (y0 > y1) {
    _swap_int16_t(y0, y1); _swap_int16_t(x0, x1);
  }

  if(y0 == y2) { // Handle awkward all-on-same-line case as its own thing
    a = b = x0;
    if(x1 < a)      a = x1;
    else if(x1 > b) b = x1;
    if(x2 < a)      a = x2;
    else if(x2 > b) b = x2;
    H_line(a, y0, b-a+1, color);
    return;
  }

  int16_t
    dx01 = x1 - x0,
    dy01 = y1 - y0,
    dx02 = x2 - x0,
    dy02 = y2 - y0,
    dx12 = x2 - x1,
    dy12 = y2 - y1;
  int32_t
    sa   = 0,
    sb   = 0;

  // For upper part of triangle, find scanline crossings for segments
  // 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y1
  // is included here (and second loop will be skipped, avoiding a /0
  // error there), otherwise scanline y1 is skipped here and handled
  // in the second loop...which also avoids a /0 error here if y0=y1
  // (flat-topped triangle).
  if(y1 == y2) last = y1;   // Include y1 scanline
  else         last = y1-1; // Skip it

  for(y=y0; y<=last; y++) {
    a   = x0 + sa / dy01;
    b   = x0 + sb / dy02;
    sa += dx01;
    sb += dx02;
    /* longhand:
    a = x0 + (x1 - x0) * (y - y0) / (y1 - y0);
    b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
    */
    if(a > b) _swap_int16_t(a,b);
    H_line(a, y, b-a+1, color);
  }

  // For lower part of triangle, find scanline crossings for segments
  // 0-2 and 1-2.  This loop is skipped if y1=y2.
  sa = dx12 * (y - y1);
  sb = dx02 * (y - y0);
  for(; y<=y2; y++) {
    a   = x1 + sa / dy12;
    b   = x0 + sb / dy02;
    sa += dx12;
    sb += dx02;
    /* longhand:
    a = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
    b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
    */
    if(a > b) _swap_int16_t(a,b);
    H_line(a, y, b-a+1, color);
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
