#ifndef SonarEZ0pw_h
#define SonarEZ0pw_h

#include "Arduino.h"

#define cm 1
#define inch 0

class SonarEZ0pw
{
  public :
  SonarEZ0pw(int SonarPin);
   float Distance(int Mode);
   
   private:
   int Sonar_Pin;
   float Inch ,Cm ;
   long signal;
};
#endif
