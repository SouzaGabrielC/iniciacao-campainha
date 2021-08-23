
/*
    Button.cpp - Libary to control the main button
    Created by Gabriel de Carvalho Souza
*/

#include "Arduino.h";

#include "Button.h";

Button::Button(int pin)
{

    Button::pin = pin;
    Button::debounce = 200;
    Button::lastTime = 0;
    Button::spentTime = 0;
    Button::previousButton = LOW;
}

Button::Button(int pin, int debounce)
{

    Button::pin = pin;
    Button::debounce = debounce;
    Button::lastTime = 0;
    Button::spentTime = 0;
    Button::previousButton = LOW;
}

buttonReturn Button::read()
{

    buttonReturn readReturn;
    bool readingButton = digitalRead(pin);

    if (readingButton == HIGH && previousButton == LOW && millis() - lastTime > debounce)
    {

        lastTime = millis();
        previousButton = readingButton;
        readReturn.pressed = true;
        readReturn.reset = false;
    }
    else if (readingButton == HIGH && previousButton == HIGH)
    {
        readReturn.reset = false;
        readReturn.pressed = false;
        spentTime = millis() - lastTime;
        if (spentTime > 10000)
        {
            readReturn.reset = true;
        }
        previousButton = readingButton;
    }
    else
    {
        previousButton = readingButton;
        readReturn.pressed = false;
        readReturn.reset = false;
    }

    return readReturn;
}