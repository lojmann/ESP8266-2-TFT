// Code provided by Thomas Loejmann Joergensen
// https://github.com/lojmann/ESP8266-2-TFT

// For original TFT code / licensing please refer to
// https://github.com/adafruit/TFTLCD-Library

// For original ESP8266 code, please refer to
// https://www.zybuluo.com/kfihihc/note/31135 (may not be original origin)

// TFT Wiring
// #define LCD_CS A3 // Chip Select goes to Analog 3
// #define LCD_CD A2 // Command/Data goes to Analog 2
// #define LCD_WR A1 // LCD Write goes to Analog 1
// #define LCD_RD A0 // LCD Read goes to Analog 0

// #define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

// When using the BREAKOUT BOARD only, use these 8 data lines to the LCD:
// For the Arduino Uno, Duemilanove, Diecimila, etc.:
//   D0 connects to digital pin 8  (Notice these are
//   D1 connects to digital pin 9   NOT in order!)
//   D2 connects to digital pin 2
//   D3 connects to digital pin 3
//   D4 connects to digital pin 4
//   D5 connects to digital pin 5
//   D6 connects to digital pin 6
//   D7 connects to digital pin 7
// For the Arduino Mega, use digital pins 22 through 29
// (on the 2-row header at the end of the board).

// ESP8266 wiring
// ESP8266 pin    Arduino Uno pin
//  GND            GND
//  UTXD           TRD
//  UTRD           TXD
//  VCC            3.3v
//  CH_PD          3.3V

#include <Adafruit_GFX.h>    // Core graphics library
#include "SWTFT.h" // Hardware-specific library
#include "Arduino.h"

// WiFi connection credentials
#define SSID "XXXXXXXXXX" // Type in your SSID
#define PASS "XXXXXXXXXX" // Type in your password for SSID
#define DST_IP "195.249.80.32" //google.com

// If using the shield, all control and data lines are fixed, and
// a simpler declaration can optionally be used:
SWTFT tft;

// Assign human-readable names to some common 16-bit color values:
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

void setup(void) {
  Serial.begin(9600);
 
  // Initiate and setup the TFT screen
  tft.reset();
  uint16_t identifier = tft.readID();
  tft.begin(identifier);
  tft.setRotation(3);
  tft.fillScreen(BLACK);

  // WiFi
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  Serial.setTimeout(5000);

  // Write opening message on TFT display
  tft.fillScreen(BLACK);
  tft.setTextSize(2); 
  tft.setCursor(0, 0);
  tft.setTextColor(WHITE);
  tft.println("ESP8266 Demo");

  //test if the module is ready
  Serial.println("AT+RST");
  delay(1000);

  if(Serial.find("ready")) {
    tft.fillScreen(BLACK);
    tft.setTextSize(2); 
    tft.setCursor(0, 0);
    tft.setTextColor(WHITE);
    tft.println("Module is ready!");
  }
  else {
    tft.fillScreen(BLACK);
    tft.setTextSize(2); 
    tft.setCursor(0, 0);
    tft.setTextColor(WHITE);
    tft.println("Module have no response.");
    while(1);
  }

  delay(1000);

  //connect to the wifi
  boolean connected=false;
  for(int i=0;i<5;i++) {
    if(connectWiFi()) {
      connected = true;
      break;
    }
  }

  if (!connected){
     while(1);
  }

  delay(5000);

  //print the ip addr
  /*Serial.println("AT+CIFSR");
  dbgSerial.println("ip address:");
  while (Serial.available())
  dbgSerial.write(Serial.read());*/
  //set the single connection mode

  Serial.println("AT+CIPMUX=0");
}

void loop(void) {
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += DST_IP;
  cmd += "\",80";
  Serial.println(cmd);     

  tft.fillScreen(BLACK);
  tft.setTextSize(2); 
  tft.setCursor(0, 0);
  tft.setTextColor(WHITE);
  tft.println(cmd);
  delay(1000);

  if(Serial.find("Error")) return;

  // Build HTTP request
  cmd = "GET / HTTP/1.0\r\n\r\n";
  Serial.print("AT+CIPSEND=");
  Serial.println(cmd.length());
  if(Serial.find(">")) {
    tft.println(">");
  }
  else {
    Serial.println("AT+CIPCLOSE");
    tft.println("connect timeout");
    delay(1000);
    return;
  }

  Serial.print(cmd);
  delay(2000);
  Serial.find("+IPD");

  while (Serial.available()) {
    char c = Serial.read();
    tft.println(c);

    if(c=='\r') {
      tft.println(" ");
    }
  }

  tft.println("====");

  delay(1000);
}

boolean connectWiFi() {
  Serial.println("AT+CWMODE=1");
  String cmd="AT+CWJAP=\"";
  cmd+=SSID;
  cmd+="\",\"";
  cmd+=PASS;
  cmd+="\"";

  tft.fillScreen(BLACK);
  tft.setTextSize(2); 
  tft.setCursor(0, 0);
  tft.setTextColor(WHITE);
//  tft.println(cmd); // Print command, SSID + PW
  tft.println("Connecting to WiFi...");

  Serial.println(cmd);
  delay(2000);
  if(Serial.find("OK")) {
    tft.println("OK, Connected to WiFi.");
    return true;
  }
  else {
    tft.println("Can not connect to the WiFi.");
    return false;
  }
}
