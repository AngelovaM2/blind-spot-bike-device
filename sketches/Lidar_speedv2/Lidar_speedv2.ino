#include <HardwareSerial.h>
#include <TFMPlus.h>
#include <movingAvg.h>

int16_t tfDist = 0;
int16_t dist;
int16_t dist2 = 0;
int16_t dist3 = 0;
int16_t dist4 = 0;
int16_t dist5 = 0;
int triggerdist = 100;
double speed;
int led = D10;
int avgspeed;

movingAvg avgSpeed(10);
TFMPlus tfLuna;
HardwareSerial MySerial(0);

void setup() {
  Serial.begin(115200); //set bit rate of serial port connecting Arduino with computer
  Serial.println("initialised");
  MySerial.begin(115200, SERIAL_8N1, -1, -1); //assign UART0 to default pins and begin

  tfLuna.begin(&MySerial);
    if( tfLuna.sendCommand( SET_FRAME_RATE, FRAME_20))
    {
        printf( "%2uHz.\r\n", FRAME_20);
    }
    else tfLuna.printReply();

  avgSpeed.begin();
}

void loop() {// function for LiDAR speed detection
  delay(50);
  if(tfLuna.getData(tfDist)) // Get data from the device
  {
    printf("\n Dist:%04icm ", tfDist);   // display distance
    dist = tfDist;
    speed = (dist - dist2)/0.05; //negative speed = obj. nearing sensor cm/s
    printf("Speed:%fcm/s ", speed);
    dist2 = dist;
    dist3 = dist2;
    dist4 = dist3;
    dist5 = dist4;
    avgspeed = avgSpeed.reading(speed);
    printf("avgSpeed:%icm/s ", avgspeed);
  }
  else                  // If the command fails
  {
    tfLuna.printFrame();  // display the error and HEX data
    dist2 = dist;
    dist3 = dist2;
    dist4 = dist3;
    dist5 = dist4;
  }

  if((avgspeed <= -50) || ((dist <= triggerdist && dist2 <= triggerdist && dist3 <= triggerdist && dist4 <= triggerdist && dist5 <= triggerdist) && avgspeed <= -2)){
    MySerial.println("sensor triggered");
    delay(100);
  }
}

