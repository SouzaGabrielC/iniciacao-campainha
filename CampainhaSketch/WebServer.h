/*
    WebServer.h - Libary to manage the WebServer
    Created by Gabriel de Carvalho Souza
*/

#ifndef WebServer_H
#define WebServer_H

#include <ESP8266WebServer.h>
#include "Arduino.h";

class WebServer{

public:
    WebServer();
    void loop();
};

#endif