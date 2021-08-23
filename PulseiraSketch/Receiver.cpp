/*
    Receiver.h - Libary to create a mqtt subscriber and connect to the broker
    Created by Gabriel de Carvalho Souza
*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "Receiver.h";
#include "Button.h";
#include "Configs.h";

#include "Arduino.h";

WiFiClient wifi;

Receiver::Receiver(String ip, void (*callback)(char *topic, byte *payload, unsigned int length))
{
    int index1 = ip.indexOf('.');
    int addr1 = ip.substring(0, index1).toInt();

    int index2 = ip.indexOf('.', index1 + 1);
    int addr2 = ip.substring(index1 + 1, index2).toInt();

    int index3 = ip.indexOf('.', index2 + 1);
    int addr3 = ip.substring(index2 + 1, index3).toInt();

    int index4 = ip.indexOf('.', index3 + 1);
    int addr4 = ip.substring(index3 + 1, index4).toInt();

    IPAddress ipAddr(addr1, addr2, addr3, addr4);

    client = PubSubClient(wifi);

    client.setServer(ipAddr, 1883);
    client.setCallback(callback);
}

void Receiver::reconnect()
{

    Button btn(Configs::PIN_BUTTON, 350);
    Configs *config = Configs::getInstance();

    while (!client.connected())
    {
        Serial.print("Attempting MQTT connection...");

        if (client.connect("pulseiraModule"))
        {
            Serial.println("connected");
            client.subscribe("bellRing");
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 3 seconds");

            delay(3000);
        }

        buttonReturn buttonRead = btn.read();

        if (buttonRead.reset)
        {
            Serial.print("Reset");
            config->clear();
            delay(3500);
            ESP.restart();
        }
    }
}

void Receiver::loop()
{

    if (!client.connected())
    {
        reconnect();
    }
    client.loop();
}
