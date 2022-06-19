#include "Arduino.h"
#include "SonarEZ0pw.h"

SonarEZ0pw::SonarEZ0pw(int SonarPin)
{
  
  pinMode(SonarPin,INPUT);
  Sonar_Pin=SonarPin;
}
 float SonarEZ0pw::Distance(int Mode)
 {
    signal = pulseIn(Sonar_Pin, HIGH);
     Inch = signal/147; 
     Cm=Inch*2.54;
     if( Mode)
     return Cm ;
     else
     return Inch;
 }
