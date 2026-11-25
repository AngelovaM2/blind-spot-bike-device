#include <TinyGPSPlus.h>
#include <U8g2lib.h>
#include <Arduino.h>
#include <Wire.h>
#include <TimeLib.h>

TinyGPSPlus gps;
HardwareSerial MySerial1(1);
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
//TimeChangeRule *tcr;

int satellites;
float hdop;
float ownSpeed = 0;
char ownSpeedString[5];
const int offset = 2; //timezone +2


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  MySerial1.begin(9600, SERIAL_8N1, 9, 10);
  u8g2.begin();
//  setTime(myTZ.toUTC(compileTime()));
}

void loop() {
  // put your main code here, to run repeatedly:
  satellites = gps.satellites.value();
  hdop = gps.hdop.hdop();
  int ownSpeed = gps.speed.kmph();
  u8g2.clearBuffer();					// clear the internal memory

  char sz[32];
  u8g2.setFont(u8g2_font_profont17_mn);
  u8g2.setCursor(42, 12);
  sprintf(sz, "%02d:%02d ", (gps.time.hour())+2, gps.time.minute());
  u8g2.print(sz);

  u8g2.setFont(u8g2_font_logisoso16_tr);	// choose a suitable font
  u8g2.setCursor(74, 40);
  u8g2.print(hdop);

  if (hdop >= 2.5){ //signal quality check
    u8g2.setFont(u8g2_font_logisoso42_tf);	// choose a suitable font
    u8g2.setCursor(16, 60);
    u8g2.print("??");
  }
  
  else{
    char sp[2];
    u8g2.setFont(u8g2_font_logisoso38_tf);	// choose a suitable font
    u8g2.setCursor(16, 60);
    sprintf(sp, "%02i\n", ownSpeed);
    u8g2.print(sp);
  }

  u8g2.setFont(u8g2_font_logisoso16_tr);	// choose a suitable font
  u8g2.setCursor(66, 60);
  u8g2.print("kmph");
  u8g2.sendBuffer();					// transfer internal memory to the display

  smartDelay(1000);
}

static void smartDelay(unsigned long ms){
  unsigned long start = millis();
  do 
  {
    while (MySerial1.available())
      gps.encode(MySerial1.read());
  } while (millis() - start < ms);
}
