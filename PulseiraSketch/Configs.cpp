/*
    Configs.cpp - Libary to store and get configs from EEPROM
    Created by Gabriel de Carvalho Souza
*/

#include <EEPROM.h>
#include "Arduino.h";

#include "Configs.h";

Configs *Configs::instance = 0;

Configs* Configs::getInstance()
{
    if (instance == 0)
    {
        instance = new Configs();
    }

    return instance;
}

Configs::Configs()
{

    isSetupMode = true;
    ssid = "";
    password = "";
    server = "";
    RColor = 0;
    GColor = 0;
    BColor = 0;
    animation = "";
    EEPROM.begin(512);
}

void Configs::read()
{

    byte value = EEPROM.read(addrSetup);

    int setupValue = (int)value;

    if (setupValue == 0 || setupValue == 255)
        isSetupMode = true;
    else
        isSetupMode = false;

    if (!isSetupMode)
    {

        // Ler ssid
        ssid = "";
        for (int i = addrSsid[0]; i <= addrSsid[1]; i++)
        {
            byte rByte = EEPROM.read(i);
            ssid += rByte == 255 || rByte == 0 ? ' ' : (char)rByte;
        }
        ssid.trim();

        // Ler password
        password = "";
        for (int i = addrPassword[0]; i <= addrPassword[1]; i++)
        {
            byte rByte = EEPROM.read(i);
            password += rByte == 255 || rByte == 0 ? ' ' : (char)rByte;
        }
        password.trim();

        //Ler server
        server = "";
        for (int i = addrServer[0]; i <= addrServer[1]; i++)
        {
            byte rByte = EEPROM.read(i);
            server += rByte == 255 || rByte == 0 ? ' ' : (char)rByte;
        }
        server.trim();

        //Ler RColor

        RColor = (int)EEPROM.read(addrR);

        //Ler GColor

        GColor = (int)EEPROM.read(addrG);

        //Ler BColor

        BColor = (int)EEPROM.read(addrB);

        //Ler animation
        animation = "";
        for (int i = addrAnimation[0]; i <= addrAnimation[1]; i++)
        {
            byte rByte = EEPROM.read(i);
            animation += rByte == 255 || rByte == 0 ? ' ' : (char)rByte;
            ;
        }
        animation.trim();
    }
}

void Configs::write()
{

    EEPROM.put(addrSetup, isSetupMode ? 0 : 1);
    EEPROM.put(addrR, RColor);
    EEPROM.put(addrG, GColor);
    EEPROM.put(addrB, BColor);
    
    int pointer = 0;
    for (int i = addrSsid[0]; i <= addrSsid[1]; i++)
    {

        EEPROM.put(i, ssid[pointer]);

        pointer++;
    }

    pointer = 0;
    for (int i = addrPassword[0]; i <= addrPassword[1]; i++)
    {

        EEPROM.put(i, password[pointer]);

        pointer++;
    }

    pointer = 0;
    for (int i = addrServer[0]; i <= addrServer[1]; i++)
    {

        EEPROM.put(i, server[pointer]);

        pointer++;
    }

    pointer = 0;
    for (int i = addrAnimation[0]; i <= addrAnimation[1]; i++)
    {

        EEPROM.put(i, animation[pointer]);

        pointer++;
    }

    EEPROM.commit();
}

void Configs::clear()
{

    isSetupMode = true;

    ssid = "";
    password = "";
    server = "";
    animation = "";
    RColor = 0;
    GColor = 0;
    BColor = 0;

    EEPROM.put(addrSetup, !isSetupMode);

    for (int i = 0; i < 512; i++)
    {
        EEPROM.write(i, 0);
    }

    EEPROM.commit();
}
