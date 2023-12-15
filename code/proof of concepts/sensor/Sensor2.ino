#include "SerialCommand.h"
#include <EEPROM.h>
#include "EEPROMAnything.h"

#define SerialPort Serial
#define Baudrate 9600

SerialCommand sCmd(SerialPort);
bool debug;
const int sensor [] = {A5, A4, A3, A2, A1, A0};
unsigned long previous;
unsigned long calculationTime;

struct param_t
{
  unsigned long cycleTime;
  int black[6];
  int white[6];
} params;

void setup()
{
  SerialPort.begin(Baudrate);

  sCmd.addCommand("debug", onDebug);
  sCmd.addCommand("calibrate", onCalibrate);
  

  EEPROM_readAnything(0, params);
  SerialPort.println("ready");
}

void loop()
{
  sCmd.readSerial();
  unsigned long current = micros();
  if (current - previous >= params.cycleTime)
  {
    previous = current;

    int normalised [6];

   SerialPort.print("normalised values: ");
   for (int i = 0; i < 6; i++)
   {
    normalised[i] = map(analogRead(sensor[i]), params.black[i], params.white[i], 0, 1000);
    SerialPort.print(normalised[i]);
    SerialPort.print(" ");
   }
   SerialPort.println();
  }

  unsigned long difference = micros() - current;
  if (difference > calculationTime) calculationTime = difference;
}



void onDebug()
{
  //waarden black
  SerialPort.print("black: ");
  for (int i = 0; i < 6; i++)
  {
      SerialPort.print(params.black[i]);
      SerialPort.print(" ");
  }

  //waarden white
  SerialPort.print("white: ");
  for (int i = 0; i < 6; i++)
  {
      SerialPort.print(params.white[i]);
      SerialPort.print(" ");
  }
  
}

void onCalibrate()
{
  char* param = sCmd.next();

  if (strcmp(param, "black") ==0 )
  {
    SerialPort.print("start met zwart te kalibreren... ");
    for (int i = 0; i < 6; i++) params.black[i]=analogRead(sensor[i]);
    SerialPort.println("klaar");
  }
  else if (strcmp(param, "white") ==0 )
  {
    SerialPort.print("start met wit te kalibreren... ");    
    for (int i = 0; i < 6; i++) params.white[i]=analogRead(sensor[i]);  
    SerialPort.println("klaar");      
  }

  EEPROM_writeAnything(0, params);
}


