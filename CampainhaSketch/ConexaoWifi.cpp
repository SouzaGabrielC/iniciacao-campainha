/*
    ConexaoWifi.cpp - Libary to control the wifi connection
    Created by Gabriel de Carvalho Souza
*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include "Arduino.h";
#include "Button.h";
#include "Configs.h";

#include "ConexaoWifi.h";

ConexaoWifi::ConexaoWifi(char *ssid)
{
    ConexaoWifi::ssid = ssid;

    ConexaoWifi::password = "";
}

ConexaoWifi::ConexaoWifi(char *ssid, char *password)
{
    ConexaoWifi::ssid = ssid;

    ConexaoWifi::password = password;
}

void ConexaoWifi::conectar()
{

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    Button btn(Configs::PIN_BUTTON, 350);
    Configs *config = Configs::getInstance();

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
        
        buttonReturn buttonRead = btn.read();

        if(buttonRead.reset){
            Serial.print("Reset");
            config->clear();
            delay(3500);
            ESP.restart();
        }
        
    }

    Serial.println("");
    Serial.println("WiFi conectado");
    Serial.println("IP: ");
    Serial.println(WiFi.localIP());
}

void ConexaoWifi::criarAP()
{   
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid);
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);
}
