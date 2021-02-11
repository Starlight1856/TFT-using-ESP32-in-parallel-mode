
This was a project to drive a 3.5inch 480x320 ILI9486 based TFT display
using an ESP32 development board in 8-bit parallel mode. It uses an
extensively modified UTFT library to drive the display. It is not
compatible with other boards.

Paul Byrne
   
   
More detailed information can be obtained from
documents in the 'doc' folder.

Folders
----------
The folders are;
4biticons,
examples,
docs,
icon_conversions,
UTFTESP32,
Windows Apps.

The contents of the folders are as listed
-------------------------------------------

4biticons
---------
This contains a series of 4 bit bitmap files which were used
to produce icons for the TFT display. Also include are .h files
which were produced using the image_convert1.exe application
(in folder Windows Apps) and are used are to generate the icons
on the TFT display.

examples
--------
This folder contains an extended version of the original Arduino 
UTFT 4800x320 demonstration code, with the new graphics functionality
in the UTFTESP32 library added to it.

A video showing the demonstration code in operation is included.


docs
-----
Datasheet ILI9486.pdf - This is the datasheet for the ILI9846 chip which
                        drives the TFT display.   


TFTESP32System.pdf - Information on the system, including circuit of TFT to ESP32,
                     supporting applications, arduino setup.
	
icon_conversions
-----------------
The bitmaps in this folder demonstrate the efficiency of using 4-bit bitmaps
which have their palette tables edited to reproduce the same colours present
in the original 24-bit bitmap.

irain-gauge-24bit.bmp size 12kB
rain-gauge-4bit.bmp size 2.1kB


	
UTFTESP32
----------
This folder contains the modified UTFT library. This has been optimised for the
ESP32 driving the ILI9846 contolled TFT display. It uses direct ESP32 register
control and in not compatible with othe boards.

Windows Apps
------------
Two windows apps were procuced to support the use of 4-bit bitmaps for icons.

image_convert1.exe - This converts the 4 bit bitmap file to a .h file containing
                     the data required to display the bitmap as an icon on the TFT
					 display.

palette4.exe - This is used to assist the developemt of 4-bit bitmap by
                     editing the files 16 colour pallet table.

More details are in the TFTESP32System.pdf document.



					 












