/*
    Led.h - Libary to control Alert led NeoPixel
    Created by Gabriel de Carvalho Souza
*/

#ifndef Led_H
#define Led_H

#include <Adafruit_NeoPixel.h>;
#include <Arduino.h>;


class Led
{

  private:
    int pin;
    bool alerting;
    String currentAnimation;
    int r, g, b;
    int pixelsNum;
    Adafruit_NeoPixel pixels;

    void executeCurrentAnimation();
    void animationLoading(bool clear);
    void animationBlinkAll(bool clear);
    void animationBlinkCenter(bool clear);
    void animationBlinkOuter(bool clear);

  public:
    Led(int pin);
    Led(int pin, int r, int g, int b);
    void loop();
    void setColor(int r, int g, int b);
    void setAnimation(String animationName);
    void alertOn();
    void alertOff();
    void clear();

};

#endif;
