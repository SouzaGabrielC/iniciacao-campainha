/*
    ConexaoWifi.h - Libary to control the wifi connection
    Created by Gabriel de Carvalho Souza
*/

#ifndef ConexaoWifi_H
#define ConexaoWifi_H

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include "Arduino.h";

class ConexaoWifi{

private:
    char *ssid, *password;


public:
    ConexaoWifi(char *ssid);
    ConexaoWifi(char *ssid, char *password);
    void conectar();
    void criarAP();

};

#endif