ESP8266-2-TFT
=============

ESP8266 output debug messages to TFT display.

For original TFT code / licensing please refer to
https://github.com/adafruit/TFTLCD-Library

For original ESP8266 code, please refer to
https://www.zybuluo.com/kfihihc/note/31135 (may not be original origin)

TFT Wiring
define LCD_CS A3 // Chip Select goes to Analog 3
define LCD_CD A2 // Command/Data goes to Analog 2
define LCD_WR A1 // LCD Write goes to Analog 1
define LCD_RD A0 // LCD Read goes to Analog 0

define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

When using the BREAKOUT BOARD only, use these 8 data lines to the LCD:
For the Arduino Uno, Duemilanove, Diecimila, etc.:
D0 connects to digital pin 8  (Notice these are
D1 connects to digital pin 9   NOT in order!)
D2 connects to digital pin 2
D3 connects to digital pin 3
D4 connects to digital pin 4
D5 connects to digital pin 5
D6 connects to digital pin 6
D7 connects to digital pin 7
For the Arduino Mega, use digital pins 22 through 29
(on the 2-row header at the end of the board).

ESP8266 wiring
ESP8266 pin    Arduino Uno pin
GND            GND
UTXD           TRD
UTRD           TXD
VCC            3.3v
CH_PD          3.3V
