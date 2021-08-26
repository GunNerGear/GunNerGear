/*         นำเข้า library            */
#define BLYNK_PRINT Serial
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

int Pino_Direccao_Motor_1 = 2;
int Pino_Direccao_Motor_2 = 3;
int Pino_Sensor_RPM = 7;
int Count_Pulses = 0; //Variable for pulse counting.
int Reading_RPM;  //Variable for calculating the engine rotation speed.
int disk_Num = 1;  //Variable for designating the number of perforations on the Sensor RPM disc.

int dir;
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "oC4J6xHPhKWudn9sfA6i0ldiu8bCOc6l";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Virus warning";
char pass[] = "louisza2547";   
//--------------------------------------------------------------

//Two motors controlled with a joystick connected to the virtual pin V2

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);

  pinMode(5, OUTPUT); // motor A speed
  pinMode(4, OUTPUT); // motor B speed
  pinMode(0, OUTPUT); //  motor A direction
  pinMode(2, OUTPUT); //  motor B direction
  pinMode(Pino_Sensor_RPM, INPUT);
}

void loop()
{
  Blynk.run();
  //Counting the duration of each pulse in High level and Low level.
  Count_Pulses = (pulseIn(Pino_Sensor_RPM, HIGH) + pulseIn(Pino_Sensor_RPM, LOW));
  //Counting the number of pulses per second (1Sec = 1000000µSec).
  Reading_RPM = 1000000/Count_Pulses;
  //Converts Revolutions Per Second (RPS) to Revolutions Per Minute (RPM):
  Reading_RPM = Reading_RPM * 60;
  //Adjust the reading to the perforation number of the sensor disc;
  Reading_RPM = Reading_RPM / disk_Num;
  
  //Condition so that when the motor is stopped the value is 0 "zero":
  if (Reading_RPM < 0){
    Reading_RPM = 0;
  }
  else{
    Reading_RPM = Reading_RPM;
  }

  //Write the calculated RPM value in the caption:
  Blynk.virtualWrite(V2, Reading_RPM);
  
  //Delay for the next step.
  delay(10);
}
