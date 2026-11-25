#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
const uint8_t WS_font[194] U8G2_FONT_SECTION("WS_font") = 
  "\1\0\6\5\6\6\1\1\7<;\0\0\0\0\0\0\0\0\0\0\0\245 \243\374>\277\23r\2'"
  "n\303\66j\204FfEVb\6&\10\342%\14\302%\14\242-\214\202-\214b\65\14C\65\14#"
  "=\214\3=\214\343D\14\304D\14\244L\214\204L\214dT\14ET\14%\134\214\5\134\214\345c\14"
  "\306c\14\246k\214\206k\214fs\14Gs\14'{\214\7{\214\347\202\14\310\202\14\250\212\214\210\212"
  "\214h\222\14I\222\14)\232\214\11\232\214\351\241\14\312\241\14\252\261\10\213\371\200h\371\200I\371\200)"
  "\301\10\14\271\214\353\300\14\274\42\63\62\42\63\262a#\66\341\3\266\340\3~\300\6\0\0\0\4\377\377"
  "\0";

void setup(void) {
  u8g2.begin();
  u8g2.enableUTF8Print();
}

void loop(void) {
  u8g2.clearBuffer();					 
}

void oledWarning() {
  u8g2.setFont(WS_font);	
  u8g2.drawGlyph(34,62,32);
  u8g2.sendBuffer();					
  delay(1000); 
}
