#include <Arduino.h>
#include "NMEAGPS.h"
#include <NeoSWSerial.h>

NeoSWSerial mySerial(4, 3); // RX, TX//

NMEAGPS     gps;
gps_fix     fix;
uint8_t     GPSupdates = 0;

void setup()  
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);

  delay(1000);

  Serial.print("Sizeof(gps) = "); Serial.println(sizeof(gps));
  Serial.println();
}

void loop() // run over and over
{
  while (gps.available( mySerial )) {
    fix = gps.read();

    if (fix.valid.speed && (fix.speed_mkn() < 1000)) {
      // Too slow, zero out the speed
      fix.spd.whole = 0;
      fix.spd.frac  = 0;
    }

    GPSupdates++;
  }

  // Print once every 5 seconds
  if (GPSupdates >= 5) {
    Serial.println("Acquired Data");
    Serial.println("-------------");
    gpsdump();
    Serial.println("-------------");
    Serial.println();

    GPSupdates = 0;
  }

}

void gpsdump()
{

  // GPS characters may be lost during lengthy Serial.print()
  //   See the NeoGPS Troubleshooting section.

  Serial.print("Lat/Long(float): ");
  if (fix.valid.location) {
    Serial.print(fix.latitude(), 5); 
    Serial.print(", "); 
    Serial.print(fix.longitude(), 5);
  }
  Serial.println();

  //*

  Serial.print(" Speed(10^-3 knots): ");
  if (fix.valid.speed)
    Serial.print(fix.speed_mkn());
  Serial.println();

  Serial.print(" (kmph): ");
  if (fix.valid.speed)
    Serial.print(fix.speed_kph());
  Serial.println();
}