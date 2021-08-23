
/*
    Button.h - Libary to control the main button
    Created by Gabriel de Carvalho Souza
*/

#ifndef Button_H
#define Button_H

#include "Arduino.h";

struct buttonReturn {
    bool pressed;
    bool reset;
  };

class Button{

private:
    bool previousButton;
    unsigned long int lastTime, spentTime;
    int debounce, pin;

public:
    Button(int pin);
    Button(int pin, int debounce);
    buttonReturn read();

};

#endif