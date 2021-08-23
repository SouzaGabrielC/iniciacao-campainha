/*
    Led.cpp - Libary to control Alert led NeoPixel
    Created by Gabriel de Carvalho Souza
*/

#include <Adafruit_NeoPixel.h>;
#include <Arduino.h>;

#include "Led.h";


Led::Led(int pin)
{
    Led::pin = pin;
    pixelsNum = 7;
    alerting = false;
    pixels = Adafruit_NeoPixel(pixelsNum, pin, NEO_GRB + NEO_KHZ800);
    pixels.begin();
    pixels.show();
    
}

Led::Led(int pin, int r, int g, int b)
{
    Led::pin = pin;
    pixelsNum = 7;
    alerting = false;
    Led::r = r;
    Led::g = g;
    Led::b = b;
    pixels = Adafruit_NeoPixel(pixelsNum, pin, NEO_GRB + NEO_KHZ800);
    pixels.begin();
    pixels.show();
}

void Led::loop()
{

    if (alerting)
    {
        executeCurrentAnimation();
    }
}

void Led::alertOn()
{
    alerting = true;
}

void Led::alertOff()
{
    alerting = false;
    Led::clear();
}

void Led::setAnimation(String animationName)
{
    Led::currentAnimation = animationName;
}

void Led::setColor(int r, int g, int b)
{
    Led::r = r;
    Led::g = g;
    Led::b = b;
}

void Led::clear()
{

    if(currentAnimation == "loading"){
        animationLoading(true);
    }
    else if(currentAnimation == "blink_all"){
        animationBlinkAll(true);
    }
    else if(currentAnimation == "blink_outer"){
        animationBlinkOuter(true);
    }
    else{
        animationBlinkCenter(true);
    }

    for (int i = 0; i < pixelsNum; i++)
    {
        pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    }

    pixels.show();
}

void Led::executeCurrentAnimation()
{

    if(currentAnimation == "loading"){
        animationLoading(false);
    }
    else if(currentAnimation == "blink_all"){
        animationBlinkAll(false);
    }
    else if(currentAnimation == "blink_outer"){
        animationBlinkOuter(false);
    }
    else{
        animationBlinkCenter(false);
        Serial.println("Execute animation center");
    }

}

void Led::animationLoading(bool clear)
{

    static unsigned long int lastTime = 0;
    static unsigned int animationTime = 1200;
    static unsigned int ledAtivo = 1;

    if (millis() > lastTime + animationTime || !clear)
    {
        pixels.setPixelColor(ledAtivo > 1 ? ledAtivo - 1 : pixelsNum - 1, pixels.Color(0, 0, 0));
        pixels.setPixelColor(ledAtivo, pixels.Color(Led::r, Led::g, Led::b));
        pixels.setBrightness(40);
        pixels.show();

        ledAtivo = ledAtivo == pixelsNum - 1 ? 1 : ledAtivo + 1;

        lastTime = millis();
    }

    if (clear)
    {
        ledAtivo = 1;
    }
}

void Led::animationBlinkAll(bool clear)
{

    static unsigned long int lastTime = 0;
    static unsigned int animationTime = 1000;
    static bool isLedsAtivo = false;

    if (millis() > lastTime + animationTime && !clear)
    {

        for (int i = 0; i < pixelsNum; i++)
        {
            pixels.setPixelColor(i, pixels.Color(isLedsAtivo ? 0 : Led::r, isLedsAtivo ? 0 : Led::g, isLedsAtivo ? 0 : Led::b));
        }
        pixels.setBrightness(60);
        pixels.show();

        isLedsAtivo = !isLedsAtivo;

        lastTime = millis();
    }

    if (clear)
    {
        isLedsAtivo = false;
    }
}

void Led::animationBlinkOuter(bool clear)
{

    static unsigned long int lastTime = 0;
    static unsigned int animationTime = 1000;
    static bool isLedsAtivo = false;

    if (millis() > lastTime + animationTime && !clear)
    {

        for (int i = 0; i < pixelsNum; i++)
        {
            if (i == 0)
            {
                pixels.setPixelColor(i, pixels.Color(0, 0, 0));
            }

            pixels.setPixelColor(i, pixels.Color(isLedsAtivo ? 0 : Led::r, isLedsAtivo ? 0 : Led::g, isLedsAtivo ? 0 : Led::b));
        }
        pixels.setBrightness(40);
        pixels.show();

        isLedsAtivo = !isLedsAtivo;

        lastTime = millis();
    }

    if (clear)
    {
        isLedsAtivo = false;
    }
}

void Led::animationBlinkCenter(bool clear)
{

    static unsigned long int lastTime = 0;
    static unsigned int animationTime = 1000;
    static bool isLedsAtivo = false;
    if (millis() > lastTime + animationTime && !clear)
    {

        for (int i = 0; i < pixelsNum; i++)
        {
            if (i != 0)
            {
                pixels.setPixelColor(i, pixels.Color(0, 0, 0));
            }

            pixels.setPixelColor(i, pixels.Color(isLedsAtivo ? 0 : Led::r, isLedsAtivo ? 0 : Led::g, isLedsAtivo ? 0 : Led::b));
        }
        pixels.setBrightness(40);
        pixels.show();

        isLedsAtivo = !isLedsAtivo;

        lastTime = millis();
    }

    if (clear)
    {
        isLedsAtivo = false;
    }
}
