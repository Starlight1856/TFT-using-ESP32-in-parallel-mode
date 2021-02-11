/*
  UTFT.h - Multi-Platform library support for Color TFT LCD Boards
  Copyright (C)2015 Rinky-Dink Electronics, Henning Karlsen. All right reserved
  
  This library is the continuation of my ITDB02_Graph, ITDB02_Graph16
  and RGB_GLCD libraries for Arduino and chipKit. As the number of 
  supported display modules and controllers started to increase I felt 
  it was time to make a single, universal library as it will be much 
  easier to maintain in the future.

  Basic functionality of this library was origianlly based on the 
  demo-code provided by ITead studio (for the ITDB02 modules) and 
  NKC Electronics (for the RGB GLCD module/shield).

  This library supports a number of 8bit, 16bit and serial graphic 
  displays, and will work with both Arduino, chipKit boards and select 
  TI LaunchPads. For a full list of tested display modules and controllers,
  see the document UTFT_Supported_display_modules_&_controllers.pdf.

  When using 8bit and 16bit display modules there are some 
  requirements you must adhere to. These requirements can be found 
  in the document UTFT_Requirements.pdf.
  There are no special requirements when using serial displays.

  You can find the latest version of the library at 
  http://www.RinkyDinkElectronics.com/

  This library is free software; you can redistribute it and/or
  modify it under the terms of the CC BY-NC-SA 3.0 license.
  Please see the included documents for further information.

  Commercial use of this library requires you to buy a license that
  will allow commercial use. This includes using the library,
  modified or not, as a tool to sell products.

  The license applies to all part of the library including the 
  examples and tools supplied with the library.


  UTFTESP32.h modified version specifically for use with a ESP32 driving
  ILI9846 480x320 TFT  display in 8 bit parallel mode. This is not compatible
  with other boards. Various TFT driver definitions have been left in just in 
  case anyone wants to extend the functionality to drive other displays.
  2020 Paul Byrne
  
  
*/

#ifndef UTFTESP32_h
#define UTFTESP32_h

#include "Arduino.h"

//#define UTFT_VERSION	282_ESP32

#define LEFT 0
#define RIGHT 9999
#define CENTER 9998

#define PORTRAIT 0
#define LANDSCAPE 1

//** Only using ILI9486 controlled TFT
#define ILI9486			28
#define CTE40			28	// ILI9486	(16bit)


//*********************************
// COLORS
//*********************************
// VGA color palette
#define VGA_BLACK		0x0000
#define VGA_WHITE		0xFFFF
#define VGA_RED			0xF800
#define VGA_GREEN		0x07E0
#define VGA_BLUE		0x001F
#define VGA_SILVER		0xC618
#define VGA_GRAY		0x8410
#define VGA_MAROON		0x8000
#define VGA_YELLOW		0xFFE0
#define VGA_OLIVE		0x8400
#define VGA_LIME		0x07E0
#define VGA_AQUA		0x07FF
#define VGA_TEAL		0x0410
#define VGA_NAVY		0x0010
#define VGA_FUCHSIA		0xF81F
#define VGA_PURPLE		0x8010
#define VGA_TRANSPARENT	0xFFFFFFFF


#define fontbyte(x) pgm_read_byte(&cfont.font[x])
#define swap(type, i, j) {type t = i; i = j; j = t;}
#define regtype volatile uint32_t
#define regsize uint32_t
#define bitmapdatatype unsigned short*

struct _current_font
{
	uint8_t* font;
	uint8_t x_size;
	uint8_t y_size;
	uint8_t offset;
	uint8_t numchars;
};

class UTFTESP32
{
	public:
		UTFTESP32();
		
		void	InitLCD(byte orientation=LANDSCAPE);
		void	clrScr();
		void	drawPixel(int x, int y);
		void	drawLine(int x1, int y1, int x2, int y2);
		void	fillScr(byte r, byte g, byte b);
		void	fillScr(word color);
		void	drawRect(int x1, int y1, int x2, int y2);
		void	drawRoundRect(int x1, int y1, int x2, int y2);
		void	fillRect(int x1, int y1, int x2, int y2);
		void	fillRoundRect(int x1, int y1, int x2, int y2);
		void	drawCircle(int x, int y, int radius);
		void	fillCircle(int x, int y, int radius);
		void	setColor(byte r, byte g, byte b);
		void	setColor(word color);
		word	getColor();
		void	setBackColor(byte r, byte g, byte b);
		void	setBackColor(word color);
		word	getBackColor();
		void    CalcColour( unsigned char red, unsigned char green, unsigned char blue, unsigned short* colour16 );
		void	print(char *st, int x, int y, int deg=0);
		void	print(String st, int x, int y, int deg=0);
		void	printNumI(long num, int x, int y, int length=0, char filler=' ');
		void	printNumF(double num, byte dec, int x, int y, char divider='.', int length=0, char filler=' ');
		void	setFont(uint8_t* font);
		uint8_t* getFont();
		uint8_t	getFontXsize();
		uint8_t	getFontYsize();
		void	drawBitmap(int x, int y, int sx, int sy, bitmapdatatype data, int scale=1);
		void	drawBitmap(int x, int y, int sx, int sy, bitmapdatatype data, int deg, int rox, int roy);
		void    drawBitmap(int x, int y, int sx, int sy, byte* data, int scale);
		void    drawOneBitBitmap(int x, int y, int sx, int sy, const byte* data, const unsigned short int* table, unsigned short int* extcolour, bool tableused=true);

		void    drawBitmap4(int x, int y, int sx, int sy,const  byte* data, const unsigned short int* table, bool mask = true );
		void    Write4BitData( unsigned char pixel_colour_index, const unsigned short int* table, bool mask );
	    void    drawEllipse(int x, int y, int a, int b);
		void    drawFilledEllipse(int x, int y, int a, int b);
		void    drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t colour);
		void    fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t colour);
		void    bezierCurve(int x[4] , int y[4], uint16_t colour );
		void    fp_bezierCurve(int x[4] , int y[4], uint16_t colour);
		int		getDisplayXSize();
		int		getDisplayYSize();
		
		void    vertScrollSetup( int16_t top_fixed_area, int16_t vert_scroll_start_addr, int16_t bottom_fixed_area );
		void    vertScroll( int16_t offset );
	
		
/*
	The functions and variables below should not normally be used.
	They have been left publicly available for use in add-on libraries
	that might need access to the lower level functions of UTFT.

	Please note that these functions and variables are not documented
	and I do not provide support on how to use them.
*/
	
		byte			fch, fcl, bch, bcl;
		byte			orient;
		long			disp_x_size, disp_y_size;
		byte			display_model, display_transfer_mode, display_serial_mode;

		_current_font	cfont;
		boolean			_transparent;

		void LCD_Writ_Bus(char VH,char VL, byte mode);
		void LCD_Write_COM(char VL);
		void LCD_Write_DATA(char VH,char VL);
		void LCD_Write_DATA(char VL);
		void LCD_Write_COM_DATA(char com1,int dat1);
		void _hw_special_init();
		void setPixel(word color);
		void drawHLine(int x, int y, int l);
		void drawVLine(int x, int y, int l);
		void printChar(byte c, int x, int y);
		void setXY(word x1, word y1, word x2, word y2);
		void clrXY();
		void rotateChar(byte c, int x, int y, int pos, int deg);
		//void _set_direction_registers(byte mode);
		void FastDraw16(char hibyte, char lobyte, long pix);
		void FastDraw8(char colbyte, long pix);
		void convert_float(char *buf, double num, int width, byte prec);
	
		
		int64_t inline imath_fixmul2( int32_t a,  int32_t b);
		int64_t POW3( long a);
		int64_t POW2( long a);


};

#endif
