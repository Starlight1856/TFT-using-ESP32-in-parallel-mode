// UTFT_Demo_480x320
// Copyright (C)2015 Rinky-Dink Electronics, Henning Karlsen. All right reserved
// web: http://www.RinkyDinkElectronics.com/
//
// This program is a demo of how to use most of the functions
// of the library with a supported display modules.
//
// This demo was made for modules with a screen resolution
// of 480x320 pixels.
//
// This program requires the UTFT library.
//

#include <UTFTESP32.h>

// Declare which fonts we will be using
extern uint8_t SmallFont[];
extern uint8_t BigFont[];

#include"hot4.h"
#include"light2.h"
#include"raingauge1.h"
#include"weather03b.h"
#include"weather08d.h"
#include"rooster2.h"
#include"cold3c.h"
#include"tractor2.h"
#include"cow1.h"

extern const unsigned short int cold3ctable[16];
extern const byte cold3c[0x0800];

extern const unsigned short int hot4table[16];
extern const byte hot4[0x0800];

extern const unsigned short int raingauge1table[16];
extern const byte raingauge1[0x0800];

extern const unsigned short int rooster2table[16];
extern const byte rooster2[0x0800];


extern const unsigned short int weather03btable[16];
extern const byte weather03b[0x0800];

extern const unsigned short int weather8dtable[16];
extern const byte weather08d[0x0800];

extern  const unsigned short int  tractor2table[16];
extern  const  byte  tractor2[0x0800];

extern  const unsigned short int  cow1table[16];
extern  const  byte  cow1[0x0800];


UTFTESP32 myGLCD;

void setup()
{
  randomSeed(analogRead(0));

  // Setup the LCD
  myGLCD.InitLCD();
  myGLCD.setFont(SmallFont);
}

void loop()
{
  int buf[478];
  int x, x2;
  int y, y2;
  int r;

  // Clear the screen and draw the frame
  myGLCD.setFont(SmallFont);
  myGLCD.clrScr();

  myGLCD.setColor(255, 0, 0);
  myGLCD.fillRect(0, 0, 479, 13);
  myGLCD.setColor(64, 64, 64);
  myGLCD.fillRect(0, 306, 479, 319);
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(255, 0, 0);
  myGLCD.print("* Universal Color TFT Display Library *", CENTER, 1);
  myGLCD.setBackColor(64, 64, 64);
  myGLCD.setColor(255, 255, 0);
  myGLCD.print("<http://www.RinkyDinkElectronics.com/>", CENTER, 307);

  myGLCD.setColor(0, 0, 255);
  myGLCD.drawRect(0, 14, 479, 305);

  // Draw crosshairs
  myGLCD.setColor(0, 0, 255);
  myGLCD.setBackColor(0, 0, 0);
  myGLCD.drawLine(239, 15, 239, 304);
  myGLCD.drawLine(1, 159, 478, 159);
  for (int i = 9; i < 470; i += 10)
    myGLCD.drawLine(i, 157, i, 161);
  for (int i = 19; i < 220; i += 10)
    myGLCD.drawLine(237, i, 241, i);

  // Draw sin-, cos- and tan-lines
  myGLCD.setColor(0, 255, 255);
  myGLCD.print("Sin", 5, 15);
  for (int i = 1; i < 478; i++)
  {
    myGLCD.drawPixel(i, 159 + (sin(((i * 1.13) * 3.14) / 180) * 95));
  }

  myGLCD.setColor(255, 0, 0);
  myGLCD.print("Cos", 5, 27);
  for (int i = 1; i < 478; i++)
  {
    myGLCD.drawPixel(i, 159 + (cos(((i * 1.13) * 3.14) / 180) * 95));
  }

  myGLCD.setColor(255, 255, 0);
  myGLCD.print("Tan", 5, 39);
  for (int i = 1; i < 478; i++)
  {
    myGLCD.drawPixel(i, 159 + (tan(((i * 1.13) * 3.14) / 180)));
  }

  delay(2000);

  myGLCD.setColor(0, 0, 0);
  myGLCD.fillRect(1, 15, 478, 304);
  myGLCD.setColor(0, 0, 255);
  myGLCD.setBackColor(0, 0, 0);
  myGLCD.drawLine(239, 15, 239, 304);
  myGLCD.drawLine(1, 159, 478, 159);

  // Draw a moving sinewave
  x = 1;
  for (int i = 1; i < (478 * 15); i++)
  {
    x++;
    if (x == 479)
      x = 1;
    if (i > 479)
    {
      if ((x == 239) || (buf[x - 1] == 159))
        myGLCD.setColor(0, 0, 255);
      else
        myGLCD.setColor(0, 0, 0);
      myGLCD.drawPixel(x, buf[x - 1]);
    }
    myGLCD.setColor(0, 255, 255);
    y = 159 + (sin(((i * 0.7) * 3.14) / 180) * (90 - (i / 100)));
    myGLCD.drawPixel(x, y);
    buf[x - 1] = y;
  }

  delay(2000);

  myGLCD.setColor(0, 0, 0);
  myGLCD.fillRect(1, 15, 478, 304);

  // Draw some filled rectangles
  for (int i = 1; i < 6; i++)
  {
    switch (i)
    {
      case 1:
        myGLCD.setColor(255, 0, 255);
        break;
      case 2:
        myGLCD.setColor(255, 0, 0);
        break;
      case 3:
        myGLCD.setColor(0, 255, 0);
        break;
      case 4:
        myGLCD.setColor(0, 0, 255);
        break;
      case 5:
        myGLCD.setColor(255, 255, 0);
        break;
    }
    myGLCD.fillRect(150 + (i * 20), 70 + (i * 20), 210 + (i * 20), 130 + (i * 20));
  }

  delay(2000);

  myGLCD.setColor(0, 0, 0);
  myGLCD.fillRect(1, 15, 478, 304);

  // Draw some filled, rounded rectangles
  for (int i = 1; i < 6; i++)
  {
    switch (i)
    {
      case 1:
        myGLCD.setColor(255, 0, 255);
        break;
      case 2:
        myGLCD.setColor(255, 0, 0);
        break;
      case 3:
        myGLCD.setColor(0, 255, 0);
        break;
      case 4:
        myGLCD.setColor(0, 0, 255);
        break;
      case 5:
        myGLCD.setColor(255, 255, 0);
        break;
    }
    myGLCD.fillRoundRect(270 - (i * 20), 70 + (i * 20), 330 - (i * 20), 130 + (i * 20));
  }

  delay(2000);

  myGLCD.setColor(0, 0, 0);
  myGLCD.fillRect(1, 15, 478, 304);

  // Draw some filled circles
  for (int i = 1; i < 6; i++)
  {
    switch (i)
    {
      case 1:
        myGLCD.setColor(255, 0, 255);
        break;
      case 2:
        myGLCD.setColor(255, 0, 0);
        break;
      case 3:
        myGLCD.setColor(0, 255, 0);
        break;
      case 4:
        myGLCD.setColor(0, 0, 255);
        break;
      case 5:
        myGLCD.setColor(255, 255, 0);
        break;
    }
    myGLCD.fillCircle(180 + (i * 20), 100 + (i * 20), 30);
  }

  delay(2000);

  myGLCD.setColor(0, 0, 0);
  myGLCD.fillRect(1, 15, 478, 304);

  // Draw some lines in a pattern
  myGLCD.setColor (255, 0, 0);
  for (int i = 15; i < 304; i += 5)
  {
    myGLCD.drawLine(1, i, (i * 1.6) - 10, 304);
  }
  myGLCD.setColor (255, 0, 0);
  for (int i = 304; i > 15; i -= 5)
  {
    myGLCD.drawLine(478, i, (i * 1.6) - 11, 15);
  }
  myGLCD.setColor (0, 255, 255);
  for (int i = 304; i > 15; i -= 5)
  {
    myGLCD.drawLine(1, i, 491 - (i * 1.6), 15);
  }
  myGLCD.setColor (0, 255, 255);
  for (int i = 15; i < 304; i += 5)
  {
    myGLCD.drawLine(478, i, 490 - (i * 1.6), 304);
  }

  delay(2000);

  myGLCD.setColor(0, 0, 0);
  myGLCD.fillRect(1, 15, 478, 304);

  // Draw some random circles
  for (int i = 0; i < 100; i++)
  {
    myGLCD.setColor(random(255), random(255), random(255));
    x = 32 + random(416);
    y = 45 + random(226);
    r = random(30);
    myGLCD.drawCircle(x, y, r);
  }

  delay(2000);

  myGLCD.setColor(0, 0, 0);
  myGLCD.fillRect(1, 15, 478, 304);

  // Draw some random rectangles
  for (int i = 0; i < 100; i++)
  {
    myGLCD.setColor(random(255), random(255), random(255));
    x = 2 + random(476);
    y = 16 + random(289);
    x2 = 2 + random(476);
    y2 = 16 + random(289);
    myGLCD.drawRect(x, y, x2, y2);
  }

  delay(2000);

  myGLCD.setColor(0, 0, 0);
  myGLCD.fillRect(1, 15, 478, 304);

  // Draw some random rounded rectangles
  for (int i = 0; i < 100; i++)
  {
    myGLCD.setColor(random(255), random(255), random(255));
    x = 2 + random(476);
    y = 16 + random(289);
    x2 = 2 + random(476);
    y2 = 16 + random(289);
    myGLCD.drawRoundRect(x, y, x2, y2);
  }

  delay(2000);

  myGLCD.setColor(0, 0, 0);
  myGLCD.fillRect(1, 15, 478, 304);

  for (int i = 0; i < 100; i++)
  {
    myGLCD.setColor(random(255), random(255), random(255));
    x = 2 + random(476);
    y = 16 + random(289);
    x2 = 2 + random(476);
    y2 = 16 + random(289);
    myGLCD.drawLine(x, y, x2, y2);
  }

  delay(2000);

  myGLCD.setColor(0, 0, 0);
  myGLCD.fillRect(1, 15, 478, 304);

  for (int i = 0; i < 10000; i++)
  {
    myGLCD.setColor(random(255), random(255), random(255));
    myGLCD.drawPixel(2 + random(476), 16 + random(289));
  }

  delay(2000);
  AdditionalFunctions();

  myGLCD.fillScr(0, 0, 255);
  myGLCD.setColor(255, 0, 0);
  myGLCD.fillRoundRect(160, 70, 319, 169);

  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(255, 0, 0);
  myGLCD.print("That's it!", CENTER, 93);
  myGLCD.print("Restarting in a", CENTER, 119);
  myGLCD.print("few seconds...", CENTER, 132);

  myGLCD.setColor(0, 255, 0);
  myGLCD.setBackColor(0, 0, 255);
  myGLCD.print("Runtime: (msecs)", CENTER, 290);
  myGLCD.printNumI(millis(), CENTER, 305);

  delay (10000);
}

void AdditionalFunctions(void)
{
  myGLCD.setFont(BigFont);
  myGLCD.fillScr(0, 0, 0);
  myGLCD.setColor(0, 255, 0);
  myGLCD.print("Additional Features: Triangles", CENTER, 93);
  delay (2000);
  testTriangles();
  delay (2000);
  test_ellipse();
  delay (2000);
  test_beziercurve();
  delay (2000);
  test_bitmaps();

}


unsigned long testTriangles()
{
  unsigned short colour16;
  int i;
  int x[7] = {60, 160, 120, 80, 280, 300, 340};
  int y[7] = {80, 100, 120, 100, 80, 100, 200};

  int x2[7] = {20, 120, 220, 40, 220, 440, 420};
  int y2[7] = {120, 200, 140, 180, 300, 100, 180};

  int x3[7] = {100, 180, 200, 120, 320, 300, 420};
  int y3[7] = {120, 220, 100, 180, 280, 140, 220};


  myGLCD.fillScr(0, 0, 0);
  for ( i = 0; i < 7; i++)
  {
    myGLCD.CalcColour(random(255), random(255), random(255), &colour16);
    //x[i]=2+random(476);
    //y[i]=16+random(289);
    //x2[i]=2+random(476);
    //y2[i]=16+random(289);
    //x3[i]= 2+random(476);
    //y3[i]= 16+random(289);
    myGLCD.drawTriangle( x[i], y[i], x2[i], y2[i], x3[i], y3[i],  colour16 );
  }

  delay (2000);
  myGLCD.fillScr(0, 0, 0);
  myGLCD.setColor(0, 255, 0);
  myGLCD.print("Additional: Filled Triangles", CENTER, 93);
  delay (2000);
  myGLCD.fillScr(0, 0, 0);

  for ( i = 0; i < 7; i++)
  {
    myGLCD.CalcColour(random(255), random(255), random(255), &colour16);
    myGLCD.fillTriangle( x[i], y[i], x2[i], y2[i], x3[i], y3[i],  colour16 );
  }


  /*
    for (i = 0; i < n; i += 5)
     {
      myGLCD.CalcColour(random(255), random(255), random(255), &colour16);
      myGLCD.drawTriangle(
          cx    , cy - i, // peak
          cx - i, cy + i, // bottom left
          cx + i, cy + i, // bottom right
          colour16);
    }
  */


  return 0;
}

void test_ellipse(void)
{
  int x, y;
  int a, b;
  int i;

  myGLCD.fillScr(0, 0, 0);
  myGLCD.setColor(0, 255, 0);
  myGLCD.print("Additional Features: Ellipses", CENTER, 93);
  delay (2000);
  myGLCD.fillScr(0, 0, 0);

  for (  i = 0; i < 100; i++ )
  {
    myGLCD.setColor(random(255), random(255), random(255));
    x = 32 + random(416);
    y = 45 + random(226);
    a = 2 + random(30);
    b = 2 + random(30);
    myGLCD.drawEllipse(x, y, a, b);
  }

  delay (2000);
  myGLCD.fillScr(0, 0, 0);
  myGLCD.setColor(0, 255, 0);
  myGLCD.print("Additional: Filled Ellipses", CENTER, 93);
  delay (2000);
  myGLCD.fillScr(0, 0, 0);


  for ( i = 0; i < 100; i++ )
  {
    myGLCD.setColor(random(255), random(255), random(255));
    x = 32 + random(416);
    y = 45 + random(226);
    a = 2 + random(30);
    b = 2 + random(30);
    myGLCD.drawFilledEllipse(x, y, a, b);
  }

}

void test_beziercurve(void)
{
  int i;
  unsigned short colour16;
  int x[4];
  int y[4];
  int a, b;
  unsigned long start_time;
  unsigned long end_time;
  double time_secs;

  //** For these examples the outer points of the curve will be fixed,
  //** and the inner two positions will vary
  x[0] = 10; y[0] = 160;
  x[1] = 160; y[1] = 10;
  x[2] = 320; y[2] = 10;
  x[3] = 470; y[3] = 160;

  myGLCD.fillScr(0, 0, 0);
  myGLCD.setColor(0, 255, 0);
  myGLCD.print("100 4-point Bezier curves", 50, 100);
  myGLCD.print("using floating-point", 50, 120);
  myGLCD.print("calculations", 50, 140);
  delay (3000);
  myGLCD.fillScr(0, 0, 0);


  start_time = millis();

  for ( i = 0; i < 100; i++ )
  {
    myGLCD.CalcColour(random(255), random(255), random(255), &colour16);
    myGLCD.bezierCurve( x, y, colour16);
    y[1] += 3;
    y[2] += 3;
  }
  end_time = millis();

  time_secs = (double)(end_time - start_time) / 1000.0;
  myGLCD.setColor(0, 255, 0);
  myGLCD.print("Time Taken =", CENTER, 305);
  myGLCD.printNumF( time_secs, 3, CENTER + 50, 305);
  delay (3000);

  x[0] = 10; y[0] = 160;
  x[1] = 160; y[1] = 10;
  x[2] = 320; y[2] = 10;
  x[3] = 470; y[3] = 160;

  myGLCD.fillScr(0, 0, 0);
  myGLCD.setColor(0, 255, 0);
  myGLCD.print("100 4-point Bezier curves", 50, 100);
  myGLCD.print("using fixed-point", 50, 120);
  myGLCD.print("calculations", 50, 140);
  delay (3000);
  myGLCD.fillScr(0, 0, 0);


  start_time = millis();
  for ( i = 0; i < 100; i++ )
  {
    myGLCD.CalcColour(random(255), random(255), random(255), &colour16);
    myGLCD.fp_bezierCurve( x, y, colour16);
    y[1] += 3;
    y[2] += 3;
  }
  end_time = millis();

  time_secs = (double)(end_time - start_time) / 1000.0;
  myGLCD.setColor(0, 255, 0);
  myGLCD.print("Time Taken =", CENTER, 305);
  myGLCD.printNumF( time_secs, 3, CENTER + 50, 305);
  delay (3000);


}

void test_bitmaps(void)
{

  myGLCD.fillScr(0, 0, 0);
  myGLCD.setColor(0, 255, 0);
  myGLCD.print("64x64 ICONS derived from", 50, 100);
  myGLCD.print("4-bit bitmaps", 50, 120);
  delay (3000);
  myGLCD.fillScr(0, 0, 0);

  myGLCD.drawBitmap4(20, 20, 64, 64, cold3c, cold3ctable, false);

  myGLCD.drawBitmap4(120, 20 , 64, 64, hot4, hot4table, false);

  myGLCD.drawBitmap4(220, 20 , 64, 64, raingauge1, raingauge1table, false);

  myGLCD.drawBitmap4(320, 20 , 64, 64, tractor2, tractor2table, false);

  myGLCD.drawBitmap4(20, 120 , 64, 64, rooster2, rooster2table, false);

  myGLCD.drawBitmap4(120, 120 , 64, 64, weather03b, weather03btable, false);

  myGLCD.drawBitmap4(220, 120 , 64, 64, weather08d, weather08dtable, false);

  myGLCD.drawBitmap4(320, 120 , 64, 64, cow1, cow1table, false);



  delay(3000);

  myGLCD.fillScr(0, 0, 0);
  myGLCD.setColor(0, 255, 0);
  myGLCD.print("64x64 ICONS derived from", 50, 100);
  myGLCD.print("4-bit bitmaps", 50, 120);
  myGLCD.print("background masked", 50, 140);
  delay (3000);
  myGLCD.fillScr(0, 0, 0);

  myGLCD.drawBitmap4(20, 20, 64, 64, cold3c, cold3ctable, true);

  myGLCD.drawBitmap4(120, 20 , 64, 64, hot4, hot4table, true);

  myGLCD.drawBitmap4(220, 20 , 64, 64, raingauge1, raingauge1table, true);

  myGLCD.drawBitmap4(320, 20 , 64, 64, tractor2, tractor2table, true);

  myGLCD.drawBitmap4(20, 120 , 64, 64, rooster2, rooster2table, true);

  myGLCD.drawBitmap4(120, 120 , 64, 64, weather03b, weather03btable, true);

  myGLCD.drawBitmap4(220, 120 , 64, 64, weather08d, weather08dtable, true);

  myGLCD.drawBitmap4(320, 120 , 64, 64, cow1, cow1table, true);

  delay (3000);

}
