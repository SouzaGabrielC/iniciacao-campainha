/*
    Receiver.h - Libary to create a mqtt subscriber and connect to the broker
    Created by Gabriel de Carvalho Souza
*/

#ifndef Receiver_H
#define Receiver_H

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "Arduino.h";

class Receiver{

private:
    void reconnect();
    PubSubClient client;

public:
    Receiver(String server_ip, void (*callback)(char *topic, byte *payload, unsigned int length));
    void loop();

};

#endif