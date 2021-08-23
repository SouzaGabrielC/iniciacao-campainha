/*
    Motor.h - Libary to control Vibration Motor
    Created by Gabriel de Carvalho Souza
*/

#ifndef Motor_H
#define Motor_H

#include "Arduino.h";

class Motor
{

  private:
    int pin; 
    unsigned int alertTimeOn, alertTimeOff;
    bool alerting;

  public:
    Motor(int pin, unsigned int TimeOn, unsigned int TimeOff);
    void loop();
    void turnOn();
    void turnOff();
    void alertOn();
    void alertOff();
  
};

#endif