#ifndef _cold3c_
#define _cold3c_

unsigned short int cold3ctable[16] PROGMEM ={0x0000,0x8000,0x0400,0x6F5E,0x0010,0x8010,0x0410,0xF75B,0xC618,0xF800,0x07E0,0x6F5E,0x001F,0xF81F,0x36DC,0xFFFF};

byte cold3c[0x0800] PROGMEM ={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x88,0x8F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x88,0x88,0x88,0x88,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x88,0x88,0x88,0x88,0x88,0x8F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x88,0x88,0x88,0x88,0x88,0x88,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x88,0x88,0x88,0x88,0x88,0x88,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xEF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xF6,0x66,0x66,0x66,0xFF,0xFF,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x8F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xEF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xF6,0x66,0x66,0x66,0xFF,0xFF,0x88,0x88,0x77,0x77,0x77,0x78,0x88,0x8F,0xFF,0xFF,0xFF,0xFF,0xFF,0xEE,0xFE,0xEF,0xEE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x88,0x88,0x77,0x77,0x77,0x78,0x88,0x8F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xEE,0xEE,0xEF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x88,0x88,0x77,0x77,0x77,0x78,0x88,0x8F,0xFF,0xFF,0xFF,0xFF,0xEF,0xFF,0xEE,0xEE,0xFF,0xFF,0xEF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x88,0x88,0x77,0x77,0x77,0x78,0x88,0x8F,0xFF,0xFF,0xFE,0xFF,0xEF,0xFF,0xFE,0xEF,0xFF,0xFF,0xEF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x88,0x88,0x77,0x77,0x77,0x78,0x88,0x8F,0xFF,0xFF,0xEE,0xEE,0xEF,0xFF,0xFE,0xEF,0xFF,0xFE,0xEE,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x88,0x88,0x77,0x77,0x77,0x78,0x88,0x8F,0xFF,0xFF,0xFF,0xEE,0xEE,0xFF,0xFE,0xEF,0xFF,0xFE,0xEE,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x88,0x88,0x77,0x77,0x77,0x78,0x88,0x8F,0xFF,0xFF,0xFF,0xEE,0xEE,0xEF,0xFE,0xEF,0xFE,0xEE,0xEE,0xEE,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xF6,0x66,0x66,0xFF,0xFF,0x88,0x88,0x77,0x77,0x77,0x78,0x88,0x8F,0xFF,0xFF,0xFE,0xEE,0xFF,0xEE,0xEE,0xEE,0xEE,0xEF,0xFE,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xF6,0x66,0x66,0xFF,0xFF,0x88,0x88,0x77,0x77,0x77,0x78,0x88,0x8F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xEE,0xEE,0xEF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x88,0x88,0x77,0x77,0x77,0x78,0x88,0x8F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xEE,0xEE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x88,0x88,0x77,0x77,0x77,0x78,0x88,0x8F,0xFF,0xFF,0xFE,0xFF,0xFF,0xEE,0xEE,0xEE,0xEE,0xFF,0xFF,0xEF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x88,0x88,0x77,0x77,0x77,0x78,0x88,0x8F,0xFF,0xFF,0xFE,0xEE,0xEE,0xEE,0xFE,0xEF,0xFE,0xEE,0xEE,0xEF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x88,0x88,0x77,0x77,0x77,0x78,0x88,0x8F,0xFF,0xFF,0xFF,0xEE,0xEE,0xFF,0xFE,0xEF,0xFF,0xEE,0xEE,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x88,0x88,0x77,0x77,0x77,0x78,0x88,0x8F,0xFF,0xFF,0xFE,0xEE,0xEF,0xFF,0xFE,0xEF,0xFF,0xFE,0xEE,0xEE,0xFF,0xFF,0xFF,
0xFF,0xFF,0xF6,0x66,0x66,0x66,0x66,0xFF,0xFF,0x88,0x88,0x77,0x77,0x77,0x78,0x88,0x8F,0xFF,0xFF,0xFE,0xFF,0xEF,0xFF,0xFE,0xEF,0xFF,0xFE,0xEF,0xEE,0xFF,0xFF,0xFF,
0xFF,0xFF,0xF6,0x66,0x66,0x66,0x66,0xFF,0xFF,0x88,0x88,0x77,0x77,0x77,0x78,0x88,0x8F,0xFF,0xFF,0xFF,0xFF,0xEF,0xFF,0xEE,0xEE,0xFF,0xFE,0xEF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x88,0x88,0x77,0x77,0x77,0x78,0x88,0x8F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xEE,0xEE,0xEF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x88,0x88,0x77,0x77,0x77,0x78,0x88,0x8F,0xFF,0xFF,0xFF,0xFF,0xFF,0xEE,0xFE,0xEF,0xEE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x88,0x88,0x77,0x77,0x77,0x78,0x88,0x8F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xEF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x88,0x88,0x77,0x77,0x77,0x78,0x88,0x8F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xEF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x88,0x88,0x77,0x77,0x77,0x78,0x88,0x8F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x88,0x88,0x77,0x77,0x77,0x78,0x88,0x8F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xF6,0x66,0x66,0xFF,0xFF,0x88,0x88,0x77,0x77,0x77,0x78,0x88,0x8F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xF6,0x66,0x66,0xFF,0xFF,0x88,0x88,0x77,0x77,0x77,0x78,0x88,0x8F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x88,0x88,0x77,0x77,0x77,0x78,0x88,0x8F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x88,0x88,0x77,0x77,0x77,0x78,0x88,0x8F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x88,0x88,0x77,0x77,0x77,0x78,0x88,0x8F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x88,0x88,0x77,0x77,0x77,0x78,0x88,0x8F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x88,0x88,0x77,0x77,0x77,0x78,0x88,0x8F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x88,0x88,0x77,0x77,0x77,0x78,0x88,0x8F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xF6,0x66,0x66,0x66,0xFF,0xFF,0x88,0x88,0x77,0x77,0x77,0x78,0x88,0x8F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xF6,0x66,0x66,0x66,0xFF,0xFF,0x88,0x88,0xEE,0xEE,0xEE,0xE8,0x88,0x8F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x88,0x88,0xEE,0xEE,0xEE,0xE8,0x88,0x8F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x88,0x88,0xEE,0xEE,0xEE,0xE8,0x88,0x8F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x88,0x88,0xEE,0xEE,0xEE,0xE8,0x88,0x88,0x8F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x88,0x88,0x88,0xEE,0xEE,0xEE,0xE8,0x88,0x88,0x88,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x88,0x88,0xEE,0xEE,0xEE,0xEE,0xBB,0x88,0x88,0x88,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x88,0x88,0x8E,0xEE,0xEE,0xEE,0xEB,0xBB,0xBB,0x88,0x88,0x8F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x88,0x88,0xEE,0xEE,0xEE,0xEE,0xBB,0xBB,0xBB,0xB8,0x88,0x88,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x88,0x8E,0xEE,0xEE,0xEE,0xEB,0xBB,0xBB,0xBB,0xB8,0x88,0x88,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x88,0x8E,0xEE,0xEE,0xEE,0xBB,0xBB,0xBB,0xBB,0xBB,0x88,0x88,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x88,0x8E,0xEE,0xEE,0xEE,0xBB,0xBB,0xBB,0xBB,0xBB,0x88,0x88,0x8F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x88,0xEE,0xEE,0xEE,0xEE,0xBB,0xBB,0xBB,0xBB,0xBB,0x88,0x88,0x8F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x88,0x88,0xEE,0xEE,0xEE,0xEE,0xBB,0xBB,0xBB,0xBB,0xBB,0xB8,0x88,0x8F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x88,0x88,0xEE,0xEE,0xEE,0xEE,0xBB,0xBB,0xBB,0xBB,0xBB,0xB8,0x88,0x8F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x88,0x88,0xEE,0xEE,0xEE,0xEE,0xBB,0xBB,0xBB,0xBB,0xBB,0x88,0x88,0x8F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x88,0xEE,0xEE,0xEE,0xEE,0xBB,0xBB,0xBB,0xBB,0xBB,0x88,0x88,0x8F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x88,0x8E,0xEE,0xEE,0xEE,0xEB,0xBB,0xBB,0xBB,0xBB,0x88,0x88,0x8F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x88,0x88,0xEE,0xEE,0xEE,0xEE,0xBB,0xBB,0xBB,0xBB,0x88,0x88,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x88,0x88,0xEE,0xEE,0xEE,0xEE,0xBB,0xBB,0xBB,0xB8,0x88,0x88,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x88,0x88,0x8E,0xEE,0xEE,0xEE,0xEB,0xBB,0xBB,0x88,0x88,0x88,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x88,0x88,0x88,0xEE,0xEE,0xEE,0xEE,0xBB,0xB8,0x88,0x88,0x8F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x88,0x88,0x8E,0xEE,0xEE,0xEE,0xE8,0x88,0x88,0x88,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x88,0x88,0x88,0x8E,0xEE,0xEE,0x88,0x88,0x88,0x8F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x8F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x88,0x88,0x88,0x88,0x88,0x8F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x88,0x88,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

#endif
