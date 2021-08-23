/*
    Configs.h - Libary to store and get configs from EEPROM
    Created by Gabriel de Carvalho Souza
*/

#ifndef Configs_H
#define Configs_H

#include <EEPROM.h>
#include "Arduino.h";

class Configs
{

  private:
    int addrSetup = 0, 
    addrR = 1, 
    addrG = 2, 
    addrB = 3, 
    addrSsid[2] = {4, 26}, 
    addrPassword[2] = {27, 49}, 
    addrServer[2] = {50, 72}, 
    addrAnimation[2] = {73, 85};
    
    static Configs* instance;
    Configs();

  public:
    static Configs* getInstance();
    static const int PIN_BUTTON = 12,  PIN_LEDS = 13, PIN_MOTOR = 14;
    void read();
    void write();
    void clear();
    bool isSetupMode;
    String ssid;
    String password;
    String server;
    int RColor;
    int GColor;
    int BColor;
    String animation;
};

#endif
