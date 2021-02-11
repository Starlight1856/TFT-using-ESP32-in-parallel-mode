/*
  UTFT.cpp - Multi-Platform library support for Color TFT LCD Boards
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
  
  
   
  UTFTESP32.cpp modified version specifically for use with a ESP32 driving
  ILI9846 480x320 TFT  display in 8 bit parallel mode. This is not compatible
  with other boards. Various TFT driver definitions have been left in just in 
  case anyone wants to extend the functionality to drive other displays.
  2020 Paul Byrne
*/

typedef long long _int64;

#define ESP32
#include <UTFTESP32.h>

//** for Fixed point calculations
const int32_t  FP_VALUE_ONE = 131072;
const int32_t  FIXED_POINT_BITS2 = 17;

//********************************************************
//**
//********************************************************

UTFTESP32::UTFTESP32()
{
	//** fixed for ILI9486 320X480 display	
	disp_x_size = 319;
	disp_y_size = 479;
	display_model =	CTE40;
	
}


//********************************************************
//** Direct ESP32 register
//********************************************************
void UTFTESP32::LCD_Write_COM(char VL)  
{  
    uint32_t d = VL;
	d =  d << 12;

	//** WR                                        1
    //** LCD_RS	               1
    //** DATA	                 xxxx xxxx 
    //** B        0000 0000 0000 0000 0000 0000 0000 0000
    //** HEX         0    0   1     F    F    0    0    0 
    GPIO.out_w1tc = 0x002FF000;  // RS ( CD command) lo
    GPIO.out_w1ts = d;
	
	GPIO.out_w1ts = 0x00000010;   //  WR lo
    GPIO.out_w1tc = 0x00000010;   //  WR lo
	
	GPIO.out_w1ts = 0x00200000;   //  RS ( CD command) hi
   
	
}

//********************************************************
//** Direct ESP32 register
//********************************************************
void UTFTESP32::LCD_Write_DATA(char VH,char VL)
{
    uint32_t d;
	
		
	d =  VH;
	d =  d << 12;
    GPIO.out_w1tc = 0x000FF000;  //
    GPIO.out_w1ts = d;
	
	GPIO.out_w1ts = 0x00000010;
    GPIO.out_w1tc = 0x00000010;   //

	d =  VL;
	d =  d << 12;
    GPIO.out_w1tc = 0x000FF000;  //
    GPIO.out_w1ts = d;
	
	GPIO.out_w1ts = 0x00000010;
    GPIO.out_w1tc = 0x00000010;   //c


}

//********************************************************
//**Direct ESP32 register
//********************************************************
void UTFTESP32::LCD_Write_DATA(char VL)
{
    uint32_t d = VL;
	d =  d << 12;

	
    GPIO.out_w1tc = 0x000FF000;  
    GPIO.out_w1ts = d;
	
	GPIO.out_w1ts = 0x00000010;
    GPIO.out_w1tc = 0x00000010;   


}

//********************************************************
//**Direct ESP32 register
//********************************************************
void UTFTESP32::LCD_Write_COM_DATA(char com1,int dat1)
{
     LCD_Write_COM(com1);
     LCD_Write_DATA(dat1>>8,dat1);
}

//********************************************************
//** Setup; ILI9486 driver only
//********************************************************
void UTFTESP32::InitLCD(byte orientation)
{
	orient=orientation;

	
	pinMode(21,OUTPUT);      //** LCD_RS  ( CD command) Command L Data H  
	digitalWrite( 21, HIGH); //** Set data default
    pinMode(4,OUTPUT);       //** LCD_WR
	pinMode(33,OUTPUT);      //** 
    pinMode(32,OUTPUT);

    pinMode( 12,OUTPUT);  //** this pin configuration is fixed 12-19
	pinMode( 13,OUTPUT);  //**
	pinMode( 14,OUTPUT);  //**
	pinMode( 15,OUTPUT);  //**
    pinMode( 16,OUTPUT);  //**
	pinMode( 17,OUTPUT);  //**
	pinMode( 18,OUTPUT);  //**
	pinMode( 19,OUTPUT);  //** this pin configuration is fixed 12-19
	
	//** Power on Reset
	digitalWrite( 32, HIGH);
    delay(15);
	digitalWrite( 32, LOW); // reset
    delay(15);
	digitalWrite( 32, HIGH);
    delay(15);
	
	digitalWrite( 33, LOW); // chip select
	
    //** Initialise 9486 
	switch(display_model)
	{
	#include "tft_drivers/ili9486/initlcd.h"
	}

	setBackColor(0, 0, 0);
	cfont.font=0;
	_transparent = false;
}

//********************************************************
//**
//********************************************************
void UTFTESP32::setXY(word x1, word y1, word x2, word y2)
{
	if (orient==LANDSCAPE)
	{
		swap(word, x1, y1);
		swap(word, x2, y2)
		y1=disp_y_size-y1;
		y2=disp_y_size-y2;
		swap(word, y1, y2)
	}

	LCD_Write_COM(0x2a); 
	LCD_Write_DATA(x1>>8);
	LCD_Write_DATA(x1);
	LCD_Write_DATA(x2>>8);
	LCD_Write_DATA(x2);
	LCD_Write_COM(0x2b); 
	LCD_Write_DATA(y1>>8);
	LCD_Write_DATA(y1);
	LCD_Write_DATA(y2>>8);
	LCD_Write_DATA(y2);
	LCD_Write_COM(0x2c); 
}

//********************************************************
//**
//********************************************************
void UTFTESP32::clrXY()
{
	if (orient==PORTRAIT)
		setXY(0,0,disp_x_size,disp_y_size);
	else
		setXY(0,0,disp_y_size,disp_x_size);
}

//********************************************************
//**
//********************************************************
void UTFTESP32::drawRect(int x1, int y1, int x2, int y2)
{
	if (x1>x2)
	{
		swap(int, x1, x2);
	}
	if (y1>y2)
	{
		swap(int, y1, y2);
	}

	drawHLine(x1, y1, x2-x1);
	drawHLine(x1, y2, x2-x1);
	drawVLine(x1, y1, y2-y1);
	drawVLine(x2, y1, y2-y1);
}

//********************************************************
//**
//********************************************************
void UTFTESP32::drawRoundRect(int x1, int y1, int x2, int y2)
{
	if (x1>x2)
	{
		swap(int, x1, x2);
	}
	if (y1>y2)
	{
		swap(int, y1, y2);
	}
	if ((x2-x1)>4 && (y2-y1)>4)
	{
		drawPixel(x1+1,y1+1);
		drawPixel(x2-1,y1+1);
		drawPixel(x1+1,y2-1);
		drawPixel(x2-1,y2-1);
		drawHLine(x1+2, y1, x2-x1-4);
		drawHLine(x1+2, y2, x2-x1-4);
		drawVLine(x1, y1+2, y2-y1-4);
		drawVLine(x2, y1+2, y2-y1-4);
	}
}

//********************************************************
//**
//********************************************************
void UTFTESP32::fillRect(int x1, int y1, int x2, int y2)
{
	long count;
	
	//cbi(P_CS, B_CS);
	if (x1>x2)
	{
		swap(int, x1, x2);
	}
	if (y1>y2)
	{
		swap(int, y1, y2);
	}
	
	
	setXY(x1, y1, x2, y2);

	count = ((long(x2-x1)+1)*(long(y2-y1)+1));
	FastDraw16(fch, fcl, count );

	
}

void UTFTESP32::fillRoundRect(int x1, int y1, int x2, int y2)
{

	
	if (x1>x2)
	{
		swap(int, x1, x2);
	}
	if (y1>y2)
	{
		swap(int, y1, y2);
	}

	if ((x2-x1)>4 && (y2-y1)>4)
	{
		for (int i=0; i<((y2-y1)/2)+1; i++)
		{
			switch(i)
			{
			case 0:
				drawHLine(x1+2, y1+i, x2-x1-4);
				drawHLine(x1+2, y2-i, x2-x1-4);
				break;
			case 1:
				drawHLine(x1+1, y1+i, x2-x1-2);
				drawHLine(x1+1, y2-i, x2-x1-2);
				break;
			default:
				drawHLine(x1, y1+i, x2-x1);
				drawHLine(x1, y2-i, x2-x1);
			}
		}
	}

}

//***************************************************************
//**
//** 
//**
//***************************************************************
void UTFTESP32::drawCircle(int x, int y, int radius)
{
	int f = 1 - radius;
	int ddF_x = 1;
	int ddF_y = -2 * radius;
	int x1 = 0;
	int y1 = radius;
 
		
	setXY(x, y + radius, x, y + radius);
	LCD_Write_DATA(fch,fcl);
	
	setXY(x, y - radius, x, y - radius);
	LCD_Write_DATA(fch,fcl);
	
	setXY(x + radius, y, x + radius, y);
	LCD_Write_DATA(fch,fcl);
	
	setXY(x - radius, y, x - radius, y);
	LCD_Write_DATA(fch,fcl);
 
	while(x1 < y1)
	{
		if(f >= 0) 
		{
			y1--;
			ddF_y += 2;
			f += ddF_y;
		}
		x1++;
		ddF_x += 2;
		f += ddF_x;    
		
		setXY(x + x1, y + y1, x + x1, y + y1);
		LCD_Write_DATA(fch,fcl);
		setXY(x - x1, y + y1, x - x1, y + y1);
		LCD_Write_DATA(fch,fcl);
		
		setXY(x + x1, y - y1, x + x1, y - y1);
		LCD_Write_DATA(fch,fcl);
		setXY(x - x1, y - y1, x - x1, y - y1);
		LCD_Write_DATA(fch,fcl);
		
		setXY(x + y1, y + x1, x + y1, y + x1);
		LCD_Write_DATA(fch,fcl);
		setXY(x - y1, y + x1, x - y1, y + x1);
		LCD_Write_DATA(fch,fcl);
		
		setXY(x + y1, y - x1, x + y1, y - x1);
		LCD_Write_DATA(fch,fcl);
		setXY(x - y1, y - x1, x - y1, y - x1);
		LCD_Write_DATA(fch,fcl);
	}
    clrXY();
}
//************************************************************
//**
//** Replace original r² = x² + y² with Bresenham's algorithm.
//**
//************************************************************
void UTFTESP32::fillCircle(int x, int y, int radius)
{
	int f = 1 - radius;
	int ddF_x = 1;
	int ddF_y = -2 * radius;
	int x1 = 0;
	int y1 = radius;
 
		
    drawHLine( x - radius, y, 2 * radius );
 
	while(x1 < y1)
	{
		if(f >= 0) 
		{
			y1--;
			ddF_y += 2;
			f += ddF_y;
		}
		x1++;
		ddF_x += 2;
		f += ddF_x;    
		
	
		drawHLine( x - x1, y + y1, 2 * x1 );
			
		drawHLine( x - x1, y - y1, 2 * x1 );
		
		drawHLine( x - y1, y - x1, 2 * y1 );
			
		drawHLine( x - y1, y + x1, 2 * y1 );
		
	}

	clrXY();	

	
}

//********************************************************
//**
//** x and y are centre coordinates
//** a and b semi and major axes, if a=b then a circle
//**
//********************************************************
void UTFTESP32::drawEllipse(int x, int y, int a, int b)
{
    int wx, wy;
    int thresh;
    int asq = a * a;
    int bsq = b * b;
    int xa, ya;

	setXY(x, y + b, x, y + b);
	LCD_Write_DATA(fch,fcl);

    wx = 0;
    wy = b;
    xa = 0;
    ya = asq * 2 * b;
    thresh = asq / 4 - asq * b;

	
    for (;;) {
        thresh += xa + bsq;

        if (thresh >= 0) {
            ya -= asq * 2;
            thresh -= ya;
            wy--;
        }

        xa += bsq * 2;
        wx++;

        if (xa >= ya)
          break;



		setXY( x+wx, y-wy, x+wx, y-wy);
	    LCD_Write_DATA(fch,fcl);
		
		setXY(x-wx, y-wy , x-wx, y-wy );
	    LCD_Write_DATA(fch,fcl);

		setXY(x+wx, y+wy , x+wx, y+wy );
	    LCD_Write_DATA(fch,fcl);
		
		setXY(x-wx, y+wy , x-wx, y+wy );
	    LCD_Write_DATA(fch,fcl);
	
    }

	setXY(x+a, y, x+a, y );
	LCD_Write_DATA(fch,fcl);
			
	setXY(x-a, y, x-a, y );
	LCD_Write_DATA(fch,fcl);


    wx = a;
    wy = 0;
    xa = bsq * 2 * a;

    ya = 0;
    thresh = bsq / 4 - bsq * a;

    for (;;)
	  {
        thresh += ya + asq;

        if (thresh >= 0) {
            xa -= bsq * 2;
            thresh = thresh - xa;
            wx--;
        }

        ya += asq * 2;
        wy++;

        if (ya > xa)
          break;


		setXY(x+wx, y-wy, x+wx, y-wy );
    	LCD_Write_DATA(fch,fcl);


		setXY(x-wx, y-wy, x-wx, y-wy );
    	LCD_Write_DATA(fch,fcl);



		setXY(x+wx, y+wy, x+wx, y+wy );
    	LCD_Write_DATA(fch,fcl);
		

		setXY(x-wx, y+wy, x-wx, y+wy );
    	LCD_Write_DATA(fch,fcl);
		
    }

 clrXY();	
}

//********************************************************
//**
//** x and y are centre coordinates
//** a and b semi and major axes, if a=b then a circle
//**
//********************************************************
void UTFTESP32::drawFilledEllipse(int x, int y, int a, int b)
{
	
    int wx, wy;
    int thresh;
    int asq = a * a;
    int bsq = b * b;
    int xa, ya;

   

    wx = 0;
    wy = b;
    xa = 0;
    ya = asq * 2 * b;
    thresh = asq / 4 - asq * b;

	
    for (;;) {
        thresh += xa + bsq;

        if (thresh >= 0) {
            ya -= asq * 2;
            thresh -= ya;
            wy--;
        }

        xa += bsq * 2;
        wx++;

        if (xa >= ya)
          break;

	
		drawHLine( x-wx, y-wy, 2 * wx );
		
		drawHLine( x-wx, y+wy, 2 * wx );
		
    }

		
    drawHLine( x-a, y, 2* a );

    wx = a;
    wy = 0;
    xa = bsq * 2 * a;

    ya = 0;
    thresh = bsq / 4 - bsq * a;

    for (;;)
	  {
        thresh += ya + asq;

        if (thresh >= 0) {
            xa -= bsq * 2;
            thresh = thresh - xa;
            wx--;
        }

        ya += asq * 2;
        wy++;

        if (ya > xa)
          break;

	    drawHLine( x-wx, y-wy, 2 * wx );

	    drawHLine( x-wx, y+wy, 2 * wx );
		
    }
	
  clrXY();	
}

//********************************************************
//**
//********************************************************
void UTFTESP32::clrScr()
{
	long i;
	long count;
	int xsize, ysize;
	
	if (orient==LANDSCAPE)
	  {
      xsize = disp_y_size;
	  ysize = disp_x_size; 
	  }
	 else
	  {
      xsize = disp_x_size;
	  ysize = disp_y_size; 
	  }

	  
	setXY(0, 0, xsize, ysize);
	count = ((disp_x_size+1)*(disp_y_size+1));
	FastDraw8( 0, count );
	

}
//********************************************************
//**
//********************************************************
void UTFTESP32::fillScr(byte r, byte g, byte b)
{
	word color = ((r&248)<<8 | (g&252)<<3 | (b&248)>>3);
	fillScr(color);
}

//********************************************************
//**
//********************************************************
void UTFTESP32::fillScr(word color)
{
	long i;
    long count;
	char ch, cl;
    int xsize, ysize;
	
	if (orient==LANDSCAPE)
	  {
      xsize = disp_y_size;
	  ysize = disp_x_size; 
	  }
	 else
	  {
      xsize = disp_x_size;
	  ysize = disp_y_size; 
	  }

	
	ch=byte(color>>8);
	cl=byte(color & 0xFF);
		

	setXY(0, 0, xsize, ysize);
	count = ((disp_x_size+1)*(disp_y_size+1));	
	FastDraw16(ch, cl, count);


}

//********************************************************
//**
//********************************************************
void UTFTESP32::setColor(byte r, byte g, byte b)
{
  unsigned short colour16;
  
  CalcColour( r, g, b, &colour16 );

  fch= (colour16 & 0xff00) >> 8;
  fcl= (colour16 & 0x00ff);
  
}
//********************************************************
//**
//********************************************************
void UTFTESP32::setColor(word color)
{
	fch=byte(color>>8);
	fcl=byte(color & 0xFF);
}

//********************************************************
//**
//********************************************************
word UTFTESP32::getColor()
{
	return (fch<<8) | fcl;
}

//********************************************************
//**
//********************************************************
void UTFTESP32::setBackColor(byte r, byte g, byte b)
{
	unsigned short colour16;
	
	CalcColour( r, g, b, &colour16 );

    bch= (colour16 & 0xff00) >> 8;
    bcl= (colour16 & 0x00ff);
	
	_transparent=false;
}

//********************************************************
//**
//********************************************************
void UTFTESP32::setBackColor(word color)
{
	if (color==VGA_TRANSPARENT)
		_transparent=true;
	else
	{
		bch=byte(color>>8);
		bcl=byte(color &0xFF);
		_transparent=false;
	}
}

//********************************************************
//**
//********************************************************
word UTFTESP32::getBackColor()
{
	return (bch<<8) | bcl;
}

//********************************************************
//** Calculate nearest 16 bit colour from 24 bit using
//** fixed point calculations for speed.
//**
//** 24 bit rrrrrrrr gggggggg bbbbbbbb
//** 16 bit rrrrr gggggg bbbbb
//**
//** 16 bit red = 24 bit red * (32/256) 
//** 16 bit green = 24 bit green * (64/256)
//** 16 bit blue = 24 bit blue * (32/256)
//** 
//********************************************************
void UTFTESP32::CalcColour( unsigned char red, unsigned char green, unsigned char blue, unsigned short* colour16 )
{
    unsigned short int red16, green16, blue16;
    unsigned char bh, bl;

	bh=((red&248)|green>>5);
	bl=((green&28)<<3|blue>>3);

    *colour16 = ( bh << 8) | bl;	


}


//********************************************************
//**
//********************************************************
void UTFTESP32::setPixel(word color)
{
	LCD_Write_DATA((color>>8),(color&0xFF));	// rrrrrggggggbbbbb
	
}

//********************************************************
//**
//********************************************************
void UTFTESP32::drawPixel(int x, int y)
{
	setXY(x, y, x, y);
	setPixel(( fch<<8)|fcl);
	clrXY();
}

//********************************************************
//**
//********************************************************
void UTFTESP32::drawLine(int x1, int y1, int x2, int y2)
{
	if (y1==y2)
		drawHLine(x1, y1, x2-x1);
	else if (x1==x2)
		drawVLine(x1, y1, y2-y1);
	else
	{
		unsigned int	dx = (x2 > x1 ? x2 - x1 : x1 - x2);
		short			xstep =  x2 > x1 ? 1 : -1;
		unsigned int	dy = (y2 > y1 ? y2 - y1 : y1 - y2);
		short			ystep =  y2 > y1 ? 1 : -1;
		int				col = x1, row = y1;


		if (dx < dy)
		{
			int t = - (dy >> 1);
			while (true)
			{
				setXY (col, row, col, row);
				LCD_Write_DATA (fch, fcl);
				if (row == y2)
					return;
				row += ystep;
				t += dx;
				if (t >= 0)
				{
					col += xstep;
					t   -= dy;
				}
			} 
		}
		else
		{
			int t = - (dx >> 1);
			while (true)
			{
				setXY (col, row, col, row);
				LCD_Write_DATA (fch, fcl);
				if (col == x2)
					return;
				col += xstep;
				t += dy;
				if (t >= 0)
				{
					row += ystep;
					t   -= dx;
				}
			} 
		}

	}
	clrXY();
}

//********************************************************
//**
//********************************************************
void UTFTESP32::drawHLine(int x, int y, int l)
{
	if (l<0)
	  {
		l = -l;
		x -= l;
	  }
	  
	setXY(x, y, x+l, y);

	FastDraw16(fch, fcl, l);

	clrXY();
}

//********************************************************
//**
//********************************************************
void UTFTESP32::drawVLine(int x, int y, int l)
{
	if (l<0)
	  {
		l = -l;
		y -= l;
	  }
	
	setXY(x, y, x, y+l);
	
	FastDraw16(fch, fcl,l);
	
	clrXY();
}
//********************************************************
//**
//********************************************************
void UTFTESP32::printChar(byte c, int x, int y)
{
	byte i,ch;
	word j;
	word temp; 


	if (!_transparent)
	{
		if (orient==PORTRAIT)
		{
			setXY(x,y,x+cfont.x_size-1,y+cfont.y_size-1);
	  
			temp=((c-cfont.offset)*((cfont.x_size/8)*cfont.y_size))+4;
			for(j=0;j<((cfont.x_size/8)*cfont.y_size);j++)
			{
				ch=pgm_read_byte(&cfont.font[temp]);
				for(i=0;i<8;i++)
				{   
					if((ch&(1<<(7-i)))!=0)   
					{
						setPixel((fch<<8)|fcl);
					} 
					else
					{
						setPixel((bch<<8)|bcl);
					}   
				}
				temp++;
			}
		}
		else
		{
			temp=((c-cfont.offset)*((cfont.x_size/8)*cfont.y_size))+4;

			for(j=0;j<((cfont.x_size/8)*cfont.y_size);j+=(cfont.x_size/8))
			{
				setXY(x,y+(j/(cfont.x_size/8)),x+cfont.x_size-1,y+(j/(cfont.x_size/8)));
				for (int zz=(cfont.x_size/8)-1; zz>=0; zz--)
				{
					ch=pgm_read_byte(&cfont.font[temp+zz]);
					for(i=0;i<8;i++)
					{   
						if((ch&(1<<i))!=0)   
						{
							setPixel((fch<<8)|fcl);
						} 
						else
						{
							setPixel((bch<<8)|bcl);
						}   
					}
				}
				temp+=(cfont.x_size/8);
			}
		}
	}
	else
	{
		temp=((c-cfont.offset)*((cfont.x_size/8)*cfont.y_size))+4;
		for(j=0;j<cfont.y_size;j++) 
		{
			for (int zz=0; zz<(cfont.x_size/8); zz++)
			{
				ch=pgm_read_byte(&cfont.font[temp+zz]); 
				for(i=0;i<8;i++)
				{   
				
					if((ch&(1<<(7-i)))!=0)   
					{
						setXY(x+i+(zz*8),y+j,x+i+(zz*8)+1,y+j+1);
						setPixel((fch<<8)|fcl);
					} 
				}
			}
			temp+=(cfont.x_size/8);
		}
	}

	clrXY();
}

//********************************************************
//**
//********************************************************
void UTFTESP32::rotateChar(byte c, int x, int y, int pos, int deg)
{
	byte i,j,ch;
	word temp; 
	int newx,newy;
	double radian;
	radian=deg*0.0175;  



	temp=((c-cfont.offset)*((cfont.x_size/8)*cfont.y_size))+4;
	for(j=0;j<cfont.y_size;j++) 
	{
		for (int zz=0; zz<(cfont.x_size/8); zz++)
		{
			ch=pgm_read_byte(&cfont.font[temp+zz]); 
			for(i=0;i<8;i++)
			{   
				newx=x+(((i+(zz*8)+(pos*cfont.x_size))*cos(radian))-((j)*sin(radian)));
				newy=y+(((j)*cos(radian))+((i+(zz*8)+(pos*cfont.x_size))*sin(radian)));

				setXY(newx,newy,newx+1,newy+1);
				
				if((ch&(1<<(7-i)))!=0)   
				{
					setPixel((fch<<8)|fcl);
				} 
				else  
				{
					if (!_transparent)
						setPixel((bch<<8)|bcl);
				}   
			}
		}
		temp+=(cfont.x_size/8);
	}

	clrXY();
}

void UTFTESP32::print(char *st, int x, int y, int deg)
{
	int stl, i;

	stl = strlen(st);

	if (orient==PORTRAIT)
	{
	if (x==RIGHT)
		x=(disp_x_size+1)-(stl*cfont.x_size);
	if (x==CENTER)
		x=((disp_x_size+1)-(stl*cfont.x_size))/2;
	}
	else
	{
	if (x==RIGHT)
		x=(disp_y_size+1)-(stl*cfont.x_size);
	if (x==CENTER)
		x=((disp_y_size+1)-(stl*cfont.x_size))/2;
	}

	for (i=0; i<stl; i++)
		if (deg==0)
			printChar(*st++, x + (i*(cfont.x_size)), y);
		else
			rotateChar(*st++, x, y, i, deg);
}

void UTFTESP32::print(String st, int x, int y, int deg)
{
	char buf[st.length()+1];

	st.toCharArray(buf, st.length()+1);
	print(buf, x, y, deg);
}

void UTFTESP32::printNumI(long num, int x, int y, int length, char filler)
{
	char buf[25];
	char st[27];
	boolean neg=false;
	int c=0, f=0;
  
	if (num==0)
	{
		if (length!=0)
		{
			for (c=0; c<(length-1); c++)
				st[c]=filler;
			st[c]=48;
			st[c+1]=0;
		}
		else
		{
			st[0]=48;
			st[1]=0;
		}
	}
	else
	{
		if (num<0)
		{
			neg=true;
			num=-num;
		}
	  
		while (num>0)
		{
			buf[c]=48+(num % 10);
			c++;
			num=(num-(num % 10))/10;
		}
		buf[c]=0;
	  
		if (neg)
		{
			st[0]=45;
		}
	  
		if (length>(c+neg))
		{
			for (int i=0; i<(length-c-neg); i++)
			{
				st[i+neg]=filler;
				f++;
			}
		}

		for (int i=0; i<c; i++)
		{
			st[i+neg+f]=buf[c-i-1];
		}
		st[c+neg+f]=0;

	}

	print(st,x,y);
}

void UTFTESP32::printNumF(double num, byte dec, int x, int y, char divider, int length, char filler)
{
	char st[27];
	boolean neg=false;

	if (dec<1)
		dec=1;
	else if (dec>5)
		dec=5;

	if (num<0)
		neg = true;

	convert_float(st, num, length, dec);

	if (divider != '.')
	{
		for (int i=0; i<sizeof(st); i++)
			if (st[i]=='.')
				st[i]=divider;
	}

	if (filler != ' ')
	{
		if (neg)
		{
			st[0]='-';
			for (int i=1; i<sizeof(st); i++)
				if ((st[i]==' ') || (st[i]=='-'))
					st[i]=filler;
		}
		else
		{
			for (int i=0; i<sizeof(st); i++)
				if (st[i]==' ')
					st[i]=filler;
		}
	}

	print(st,x,y);
}

void UTFTESP32::setFont(uint8_t* font)
{
	cfont.font=font;
	cfont.x_size=fontbyte(0);
	cfont.y_size=fontbyte(1);
	cfont.offset=fontbyte(2);
	cfont.numchars=fontbyte(3);
}

uint8_t* UTFTESP32::getFont()
{
	return cfont.font;
}

uint8_t UTFTESP32::getFontXsize()
{
	return cfont.x_size;
}

uint8_t UTFTESP32::getFontYsize()
{
	return cfont.y_size;
}

//********************************************************
//**
//********************************************************
void UTFTESP32::drawBitmap(int x, int y, int sx, int sy, bitmapdatatype data, int scale)
{
	unsigned int col;
	int tx, ty, tc, tsx, tsy;

	if (scale==1)
	{
		if (orient==PORTRAIT)
		{
			setXY(x, y, x+sx-1, y+sy-1);
			for (tc=0; tc<(sx*sy); tc++)
			{
				col=pgm_read_word(&data[tc]);
				LCD_Write_DATA(col>>8,col & 0xff);
			}
			
		}
		else
		{
			for (ty=0; ty<sy; ty++)
			{
				setXY(x, y+ty, x+sx-1, y+ty);
				for (tx=sx-1; tx>=0; tx--)
				{
					col=pgm_read_word(&data[(ty*sx)+tx]);
					LCD_Write_DATA(col>>8,col & 0xff);
				}
			}
			
		}
	}
	else
	{
		if (orient==PORTRAIT)
		{
			//cbi(P_CS, B_CS);
			for (ty=0; ty<sy; ty++)
			{
				setXY(x, y+(ty*scale), x+((sx*scale)-1), y+(ty*scale)+scale);
				for (tsy=0; tsy<scale; tsy++)
					for (tx=0; tx<sx; tx++)
					{
						col=pgm_read_word(&data[(ty*sx)+tx]);
						for (tsx=0; tsx<scale; tsx++)
							LCD_Write_DATA(col>>8,col & 0xff);
					}
			}
			//sbi(P_CS, B_CS);
		}
		else
		{
			//cbi(P_CS, B_CS);
			for (ty=0; ty<sy; ty++)
			{
				for (tsy=0; tsy<scale; tsy++)
				{
					setXY(x, y+(ty*scale)+tsy, x+((sx*scale)-1), y+(ty*scale)+tsy);
					for (tx=sx-1; tx>=0; tx--)
					{
						col=pgm_read_word(&data[(ty*sx)+tx]);
						for (tsx=0; tsx<scale; tsx++)
							LCD_Write_DATA(col>>8,col & 0xff);
					}
				}
			}
		
		}
	}
	clrXY();
}

//**************************************************************************************************
//**
//**
//**
//**************************************************************************************************
void UTFTESP32::drawBitmap(int x, int y, int sx, int sy, bitmapdatatype data, int deg, int rox, int roy)
{
	unsigned int col;
	int tx, ty, newx, newy;
	double radian;
	radian=deg*0.0175;  

	if (deg==0)
		drawBitmap(x, y, sx, sy, data);
	else
	{

		for (ty=0; ty<sy; ty++)
			for (tx=0; tx<sx; tx++)
			{
				col=pgm_read_word(&data[(ty*sx)+tx]);

				newx=x+rox+(((tx-rox)*cos(radian))-((ty-roy)*sin(radian)));
				newy=y+roy+(((ty-roy)*cos(radian))+((tx-rox)*sin(radian)));

				setXY(newx, newy, newx, newy);
				LCD_Write_DATA(col>>8,col & 0xff);
			}

	}
	clrXY();
}

//******************************************************************************************************************
//**
//** display 4-bit bitmap. Colours displayed are from table contained within bitmap
//** and converted to 16-bit colours for TFT display. If mask = true, the colour indicated
//** by table entry 0xf will be replaced by current background colour.
//**
//** LANDSCAPE mode only
//**
//** x,y start coordinates
//** sx, sy bitmap x,y, size in pixels
//** byte* data; data array containing 4 bit bitmap data generated by image_convert.exe application
//** unsigned short int* table; 16 colour table containg 16 bit colours generated by image_convert1.exe application
//** bool mask; If true colour in table entry 16 (0f) normally white, will be replaced by current background colour
//**
//******************************************************************************************************************
void UTFTESP32::drawBitmap4(int x, int y, int sx, int sy, const byte* data, const unsigned short int* table, bool mask)
{
	byte col;
	unsigned short int colour;
	int tx, ty, tc, tsx, tsy;
	unsigned char pixel_colour_index;
	
    //** landscape only
	 tc =0;
     for (ty=0; ty<sy; ty++)
        {
        setXY(x, y+ty, x+sx-1, y+ty);
        for (tx=0; tx < (sx/2); tx++)
          {
          col= pgm_read_byte(&data[tc]);
          tc++;
        
          pixel_colour_index = (0xf0 & col ) >> 4;
		  
		  Write4BitData( pixel_colour_index, table, mask );
        
          pixel_colour_index = (0x0f & col );
		  
		  Write4BitData( pixel_colour_index, table, mask );
          }
        }
	
	clrXY();
}
//********************************************************
//**
//** Write4BitData; write pixel from icon bitmap data
//**
//** unsigned char pixel_colour_index; index of colour in table
//** const unsigned short int* table; colour table
//** bool mask; mask backgroung colour
//**
//********************************************************
void UTFTESP32::Write4BitData( unsigned char pixel_colour_index, const unsigned short int* table, bool mask )
{
	unsigned short int colour;
	
	if( mask )
		{
		//** mask background colour
        //** colour table entry 0xf ( entry num 16)
        //** is used as icons background colour.
        //** If mask set then this is replaced with
        //** backgroung colour set by setBackColor function.
		if( pixel_colour_index == 0x0f )
		   {
		   LCD_Write_DATA( bch, bcl ); //** 
		   }
		else
		   {
           colour = pgm_read_word(&table[pixel_colour_index] );
           LCD_Write_DATA(colour>>8, colour & 0xff);
		   }
		}
	else
	   {
       colour = pgm_read_word(&table[pixel_colour_index] );
       LCD_Write_DATA(colour>>8, colour & 0xff);
	   }
    
}


//***********************************************************************************
//**
//** drawOneBitBitmap; this in effect a two colour bitmap
//** 
//** LANDSCAPE mode only
//**
//** x,y start coordinates
//** sx, sy bitmap x,y, size in pixels
//** const byte* data; Each byte has data for 8 pixels, 0,1 reference the  colour table
//** const unsigned short int* table; The 1 bit bitmap table has two entrys    
//** unsigned short int* extcolour; A two colour table which overides original
//** bool tableused; If set the original colour table is used, otherwise the override table
//**
//*************************************************************************************
void UTFTESP32::drawOneBitBitmap(int x, int y, int sx, int sy, const byte* data, const unsigned short int* table, unsigned short int* extcolour, bool tableused)
{
	byte col;
	unsigned short int colour;
	int tx, ty, tc, tsx, tsy;
	unsigned char pixel_colour_index;
	unsigned char mask;
	int i;
	
    //** landscape only
	 tc =0;
     for (ty=0; ty<sy; ty++)
        {
        setXY(x, y+ty, x+sx-1, y+ty);
        for (tx=0; tx < (sx/8); tx++)
          {
          col= pgm_read_byte(&data[tc]);
          tc++;
          mask = 0x01;
		
		  //** each byte has data for 8 pixels
		  
		  for(i=0; i<8; i++ )
		    {
            if( mask & col )
			  pixel_colour_index = 1;
		    else
			  pixel_colour_index = 0;	
		  
	        //** It was found many apps did not fully support one bit
			//** bitmaps with the colour not set as specified, so 
			//** this provides to option to overide and set the required
			//** colour.
			//** 
		    if(tableused)
              colour = pgm_read_word(&table[pixel_colour_index] ); //** bitmap table colour
		    else
			  colour = extcolour[pixel_colour_index]; //** override table colour
				
			LCD_Write_DATA(colour>>8, colour & 0xff);
			mask <<= 1;
			}
          }
        }
	
	clrXY();
}

//**************************************************************************/
//*
//*    Draw triangle 
//*    x0  Vertex 0 x coordinate
//*    y0  Vertex 0 y coordinate
//*    x1  Vertex 1 x coordinate
//*    y1  Vertex 1 y coordinate
//*    x2  Vertex 2 x coordinate
//*    y2  Vertex 2 y coordinate
//*    colour 16-bit colour 
//*
//**************************************************************************/
void UTFTESP32::drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t colour )
 {
	setColor( colour );
    drawLine(x0, y0, x1, y1);
    drawLine(x1, y1, x2, y2);
    drawLine(x2, y2, x0, y0);
}

/**************************************************************************/
//*
//*    Draw filled triangle 
//*    x0  Vertex 0 x coordinate
//*    y0  Vertex 0 y coordinate
//*    x1  Vertex 1 x coordinate
//*    y1  Vertex 1 y coordinate
//*    x2  Vertex 2 x coordinate
//*    y2  Vertex 2 y coordinate
//*    colour 16-bit colour 
//*
//**************************************************************************/
void UTFTESP32::fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t colour )
{

    int16_t a, b, y, last;

	setColor( colour );
	
    //** Sort coordinates by Y order (y2 >= y1 >= y0)
    if (y0 > y1) {
        swap(word, y0, y1); swap(word, x0, x1);
    }
    if (y1 > y2) {
        swap(word, y2, y1); swap(word, x2, x1);
    }
    if (y0 > y1) {
        swap(word, y0, y1); swap(word, x0, x1);
    }

	
    if(y0 == y2) 
		{ 
	    //** Trap and handle same line case 
        a = b = x0;
        if(x1 < a)      a = x1;
        else if(x1 > b) b = x1;
        if(x2 < a)      a = x2;
        else if(x2 > b) b = x2;
		drawHLine(a, y0, b-a+1);
        return;
		}


    int16_t dx01 = x1 - x0;
    int16_t dy01 = y1 - y0;
    int16_t dx02 = x2 - x0;
    int16_t dy02 = y2 - y0;
    int16_t dx12 = x2 - x1;
    int16_t dy12 = y2 - y1;
   
    int32_t sa   = 0;
    int32_t sb   = 0;

    // For upper part of triangle, find scanline crossings for segments
    // 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y1
    // is included here (and second loop will be skipped, avoiding a /0
    // error there), otherwise scanline y1 is skipped here and handled
    // in the second loop...which also avoids a /0 error here if y0=y1
    // (flat-topped triangle).
    if(y1 == y2) last = y1;   // Include y1 scanline
    else         last = y1-1; // Skip it

    for(y=y0; y<=last; y++)
		{
		a   = x0 + sa / dy01;
		b   = x0 + sb / dy02;
		sa += dx01;
		sb += dx02;
				
		if(a > b) swap(word,a,b);
		drawHLine(a, y, b-a+1);
		}

    // For lower part of triangle, find scanline crossings for segments
    // 0-2 and 1-2.  This loop is skipped if y1=y2.
    sa = (int32_t)dx12 * (y - y1);
    sb = (int32_t)dx02 * (y - y0);
	
	//** y declared above
    for(; y<=y2; y++)
		{
        a   = x1 + sa / dy12;
        b   = x0 + sb / dy02;
        sa += dx12;
        sb += dx02;
		
        if(a > b) swap(word,a,b);

		drawHLine(a, y, b-a+1);
		}

}

//************************************************
//**
//** Bezier curve using floating point calculations
//** This is only for providing a comparison with
//** the speed of the fixed point version
//**
//************************************************
void UTFTESP32::bezierCurve(int x[4] , int y[4], uint16_t colour ) 
{ 
    double xu = 0.0 , yu = 0.0 , u = 0.0 ; 
    int i = 0 ; 
	
	setColor( colour );
	
    for(u = 0.0 ; u <= 1.0 ; u += 0.001) 
    { 
        xu = pow(1-u,3)*x[0]+3*u*pow(1-u,2)*x[1]+3*pow(u,2)*(1-u)*x[2]   +pow(u,3)*x[3]; 
        yu = pow(1-u,3)*y[0]+3*u*pow(1-u,2)*y[1]+3*pow(u,2)*(1-u)*y[2]   +pow(u,3)*y[3]; 
        drawPixel( (int)xu, (int)yu) ; 
    } 
}

//********************************************************
//** Four-point Bezier curve using fixed point calculations
//*  Landscape mode
//*
//* int x[4]; x-axis points
//* int y[4]; y-axis points
//* uint16_t colour; colour of curve
//********************************************************
void UTFTESP32::fp_bezierCurve(int x[4] , int y[4], uint16_t colour) 
{
	int64_t ip1, ip2, ip3, ip4;
	int64_t iu;
	int64_t ixu, iyu;

	setColor( colour );


  for(iu = 0; iu <= 131072 ; iu += 128) 
    { 
    ip1 = POW3( FP_VALUE_ONE - iu );
	ip2 = POW2( FP_VALUE_ONE - iu );
	ip3 = POW2( iu);
    ip4 = POW3( iu);

	ixu = ( (ip1*x[0]) + ( (3*iu*ip2*x[1] )>>FIXED_POINT_BITS2 ) + ( (3*ip3*(FP_VALUE_ONE-iu)*x[2])>>FIXED_POINT_BITS2 ) + ip4*x[3] ) >> FIXED_POINT_BITS2;
	iyu = ( (ip1*y[0]) + ( (3*iu*ip2*y[1] )>>FIXED_POINT_BITS2 ) + ( (3*ip3*(FP_VALUE_ONE-iu)*y[2])>>FIXED_POINT_BITS2 ) + ip4*y[3] ) >> FIXED_POINT_BITS2;
	drawPixel( ixu, iyu );
    }

}

//*********************************************************
//** imath_fixmul2
//**
//** Fixed point multiply
//** 
//*********************************************************
int64_t inline UTFTESP32::imath_fixmul2( int32_t a,  int32_t b)
{
    // mult scaled FIXED_POINT_BITS
  return (  (int64_t)a * b) >> FIXED_POINT_BITS2;
}

//**********************************************************
//** Fixed point calculate cube of long a
//** 
//**********************************************************
int64_t UTFTESP32::POW3( long a)
{
 int64_t temp;

 temp = imath_fixmul2(  a, a);
 
 return imath_fixmul2(  temp, a);;
 }
 
 //**********************************************************
//** Fixed point calculate square of long a
//**
//**********************************************************
 int64_t UTFTESP32::POW2( long a)
{
return imath_fixmul2(  a, a);
}


int UTFTESP32::getDisplayXSize()
{
	if (orient==PORTRAIT)
		return disp_x_size+1;
	else
		return disp_y_size+1;
}

int UTFTESP32::getDisplayYSize()
{
	if (orient==PORTRAIT)
		return disp_y_size+1;
	else
		return disp_x_size+1;
}


//****************************************************
//** Direct ESP32 register
//****************************************************
void UTFTESP32::FastDraw16(char hibyte, char lobyte, long pix)
{
	long blocks;
	int d1, d2;
	
	
	d1 =  hibyte;
	d1 =  d1 << 12;
	
	d2 = lobyte;
	d2 =  d2 << 12;
		
	blocks = pix/16;
	
    GPIO.out_w1tc = 0x000FF010;	
	for (int i=0; i<blocks; i++)
	  { 
      GPIO.out_w1ts = d1; GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x000FF010;  
	  GPIO.out_w1ts = d2; GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x000FF010;   

      GPIO.out_w1ts = d1; GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x000FF010;   
	  GPIO.out_w1ts = d2; GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x000FF010;   
	  
      GPIO.out_w1ts = d1; GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x000FF010;   
	  GPIO.out_w1ts = d2; GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x000FF010;   
	  
      GPIO.out_w1ts = d1; GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x000FF010;   
	  GPIO.out_w1ts = d2; GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x000FF010;   
	  
      GPIO.out_w1ts = d1; GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x000FF010;   
	  GPIO.out_w1ts = d2; GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x000FF010;   
	  
      GPIO.out_w1ts = d1; GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x000FF010;   
	  GPIO.out_w1ts = d2; GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x000FF010;   
	  
      GPIO.out_w1ts = d1; GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x000FF010;   
	  GPIO.out_w1ts = d2; GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x000FF010;   
	  
      GPIO.out_w1ts = d1; GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x000FF010;   
	  GPIO.out_w1ts = d2; GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x000FF010;   
	  
      GPIO.out_w1ts = d1; GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x000FF010;   
	  GPIO.out_w1ts = d2; GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x000FF010;   
	  
      GPIO.out_w1ts = d1; GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x000FF010;   
	  GPIO.out_w1ts = d2; GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x000FF010;   
	  
      GPIO.out_w1ts = d1; GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x000FF010;   
	  GPIO.out_w1ts = d2; GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x000FF010;   
	  
      GPIO.out_w1ts = d1; GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x000FF010;   
	  GPIO.out_w1ts = d2; GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x000FF010;   
	  
      GPIO.out_w1ts = d1; GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x000FF010;   
	  GPIO.out_w1ts = d2; GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x000FF010;   
	  
      GPIO.out_w1ts = d1; GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x000FF010;   
	  GPIO.out_w1ts = d2; GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x000FF010;   
	  
      GPIO.out_w1ts = d1; GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x000FF010;   
	  GPIO.out_w1ts = d2; GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x000FF010;   
	  
      GPIO.out_w1ts = d1; GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x000FF010;   
	  GPIO.out_w1ts = d2; GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x000FF010;   
	  }
	  
	if ((pix % 16) != 0)
	  {
	  for (int i=0; i<(pix % 16)+1; i++)
		  {
	      GPIO.out_w1ts = d1; GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x000FF010;   
    	  GPIO.out_w1ts = d2; GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x000FF010;   
		  }
	  }
}

//****************************************************
//** Direct ESP32 register
//****************************************************
void UTFTESP32::FastDraw8(char colbyte, long pix)
{
	long blocks;
	int d1;
		
	d1 =  colbyte;
	d1 =  d1 << 12;
			
	blocks = pix/16;
	
    GPIO.out_w1tc = 0x000FF010;	
	GPIO.out_w1ts = d1;	
	
	for (int i=0; i<blocks; i++)
	  { 
      GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x00000010;   
	  GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x00000010;   
	  
      GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x00000010;   
	  GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x00000010;   
	  
      GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x00000010;   
	  GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x00000010;   
	  
      GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x00000010;   
	  GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x00000010;   
	  
      GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x00000010;   
	  GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x00000010;   
	  
      GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x00000010;   
	  GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x00000010;   
	  
      GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x00000010;   
	  GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x00000010;   
	  
      GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x00000010;   
	  GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x00000010;   
	  
      GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x00000010;   
	  GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x00000010;   
	  
      GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x00000010;   
	  GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x00000010;   
	  
      GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x00000010;   
	  GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x00000010;   
	  
      GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x00000010;   
	  GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x00000010;   
	  
      GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x00000010;   
	  GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x00000010;   
	  
      GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x00000010;   
	  GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x00000010;   
	  
      GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x00000010;   
	  GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x00000010;   
	  
      GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x00000010;   
	  GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x00000010;   
   
	  }
	  
	if ((pix % 16) != 0)
	  {
	  for (int i=0; i<(pix % 16)+1; i++)
		  {
          GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x00000010;   
     	  GPIO.out_w1ts = 0x00000010; GPIO.out_w1tc = 0x00000010;   
		  }
	  }
}

void UTFTESP32::convert_float ( char *buf, double num, int width, byte prec )
{
  dtostrf ( num, width, prec, buf );
}


//************************************************************************
//** Seup scrolling
//** Scrolling only occurs along the wide axis. Thus if in lanscape mode
//** the scrolling will be horizontal.
//**
//************************************************************************
void UTFTESP32::vertScrollSetup( int16_t top_fixed_area, int16_t vert_scroll_start_addr, int16_t bottom_fixed_area )
{
  uint8_t d[6];

  
  d[0] = top_fixed_area >> 8;
  d[1] = top_fixed_area;
  
  d[2] = vert_scroll_start_addr >> 8;
  d[3] = vert_scroll_start_addr;
  
  d[4] = bottom_fixed_area >> 8;;
  d[5] = bottom_fixed_area;

  LCD_Write_COM( 0x33 );  
  LCD_Write_DATA( d[0], d[1] );
  LCD_Write_DATA( d[2], d[3] );
  LCD_Write_DATA( d[4], d[5] );

}

//************************************************************************
//** 
//** Perform scrolling
//**
//************************************************************************
void UTFTESP32::vertScroll( int16_t offset ) 
{
  uint8_t d[2];
  
  d[0] = offset >> 8;
  d[1] = offset;
  LCD_Write_COM( 0x37 );  
  LCD_Write_DATA( d[0], d[1] );
}
	  
