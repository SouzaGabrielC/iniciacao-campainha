/*
    WebServer.h - Libary to manage the WebServer
    Created by Gabriel de Carvalho Souza
*/

#include <ESP8266WebServer.h>
#include "Arduino.h";

#include "Configs.h";
#include "WebServer.h";

ESP8266WebServer server(80);

void handleHome()
{

    server.send(200, "text/html", "<!DOCTYPE html>\
    <html lang=\"pt-br\">\
    <head>\
        <meta charset=\"UTF-8\">\
        <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\
        <meta http-equiv=\"X-UA-Compatible\" content=\"ie=edge\">\
        <title>Configurações</title>\
        <style>\
            html {\
                padding: 0;\
                margin: 0;\
            }\
            body {\
                padding: 0;\
                margin: 0;\
            }\
            header {\
                height: 4em;\
                width: 100%;\
                background-color: #3D9ED6;\
                color: white;\
                padding: 1em 0.5em;\
                box-sizing: border-box;\
            }\
            header h1 {\
                font-size: 1.3em;\
                margin: 0;\
            }\
            section {\
                padding: 1em 4%;\
            }\
            section form {\
                font-size: 14px;\
            }\
            section form label {\
                font-weight: bold;\
                color: #1C5675\
            }\
            section form input {\
                width: 100%;\
                color: #3180AA;\
                font-size: 14px;\
                padding: 0.2em;\
                box-sizing: border-box;\
                margin: 0.4em 0;\
            }\
            section form select {\
                width: 100%;\
                font-size: 14px;\
                padding: 0.2em;\
                margin: 0.4em 0;\
            }\
            section form button {\
                float: right;\
                margin: 0.4em 0;\
                width: 35%;\
                height: 35px;\
                font-size: 14px;\
                font-weight: bold;\
                background-color: #32AC58;\
                color: white;\
                border: 0;\
                border-radius: 4px;\
            }\
        </style>\
    </head>\
    <body>\
        <header>\
            <h1>Configurações da Pulseira</h1>\
        </header>\
        <section>\
            <div>\
                <form action=\"/set\" method=\"POST\" id=\"configForm\">\
                    <label for=\"nm-rede\">Nome da Rede WiFi (ssid): </label>\
                    <input name=\"nm-rede\" type=\"text\" required=\"required\">\
                    <br>\
                    <br>\
                    <label for=\"pw-rede\">Senha da Rede WiFi: </label>\
                    <input name=\"pw-rede\" type=\"password\">\
                    <br>\
                    <br>\
                    <label for=\"ip-server\">IP do servidor: </label>\
                    <input name=\"ip-server\" type=\"text\" required=\"required\">\
                    <br>\
                    <br>\
                    <label for=\"cor\">Cor do alerta: </label>\
                    <input name=\"cor\" type=\"color\" value=\"#ff0000\" required=\"required\">\
                    <input type=\"hidden\" name=\"r-color\">\
                    <input type=\"hidden\" name=\"g-color\">\
                    <input type=\"hidden\" name=\"b-color\">\
                    <br>\
                    <br>\
                    <label for=\"animation\">Animação do alerta: </label>\
                    <select name=\"animation\" required=\"required\">\
                        <option value=\"loading\">Loading</option>\
                        <option value=\"blink_all\">Piscando todos</option>\
                        <option value=\"blink_center\">Piscando centro</option>\
                        <option value=\"blink_outer\">Piscando fora</option>\
                    </select>\
                    <br>\
                    <br>\
                    <button id=\"btn-configurar\" type=\"button\">Configurar</button>\
                </form>\
            </div>\
        </section>\
        <script>\
            var form = document.getElementById(\"configForm\");\
            var btnConfigurar = document.getElementById(\"btn-configurar\");\
            var colorDocument = document.querySelector(\"input[name='cor']\");\
            colorDocument.addEventListener('change', function(){\
                var result = /^#?([a-f\\d]{2})([a-f\\d]{2})([a-f\\d]{2})$/i.exec(colorDocument.value);\
                var rInput = document.querySelector(\"input[name='r-color']\");\
                var gInput = document.querySelector(\"input[name='g-color']\");\
                var bInput = document.querySelector(\"input[name='b-color']\");\
                rInput.value = parseInt(result[1], 16);\
                gInput.value = parseInt(result[2], 16);\
                bInput.value = parseInt(result[3], 16);\
            });\
            btnConfigurar.addEventListener(\"click\", function (event) {\
                var ipInput = document.querySelector(\"input[name='ip-server']\");\
                var ssidInput = document.querySelector(\"input[name='nm-rede']\");\
                var colorInput = colorDocument;\
                var ip = ipInput.value;\
                var ssid = ssidInput.value;\
                var color = colorInput.value;\
                var passed = true;\
                if (ssid.trim() == \"\") {\
                    passed = false;\
                    alert('O nome da rede não pode estar em branco!');\
                }\
                if (!(/^\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}$/.test(ip)) && passed) {\
                    passed = false;\
                    alert('IP do servidor não está em um formato correto!');\
                }\
                if (color.trim() == \"\") {\
                    passed = false;\
                    alert(\"Escolha um cor para o alerta da pulseira!\");\
                }\
                if (passed)\
                    form.submit();\
            });\
        </script>\
    </body>\
    </html>");

}

void handleSet()
{

    if(server.hasArg("nm-rede")){

        /* DEBUG INICIO */
        Serial.println(server.arg("nm-rede"));
        Serial.println(server.arg("pw-rede"));
        Serial.println(server.arg("ip-server"));
        Serial.println(server.arg("r-color"));
        Serial.println(server.arg("g-color"));
        Serial.println(server.arg("b-color"));
        Serial.println(server.arg("animation"));
        /* DEBUG FIM */

        Configs* config = Configs::getInstance();

        config->isSetupMode = false;
        config->ssid = server.arg("nm-rede");
        config->password = server.arg("pw-rede");
        config->server = server.arg("ip-server");
        config->RColor = server.arg("r-color").toInt();
        config->GColor = server.arg("g-color").toInt();
        config->BColor = server.arg("b-color").toInt();
        config->animation = server.arg("animation");

        config->write();

        server.send(200, "text/html", "<h1>Configurado com sucesso!</h1>");

        delay(3300);

        ESP.restart();

    }else{
        server.send(200, "text/html", "<h1>Erro ao enviar!</h1>");
    }

}

WebServer::WebServer()
{
    Serial.println("Create Webserver");
    server.on("/", HTTP_GET, handleHome);
    server.on("/set", HTTP_POST, handleSet);
    server.begin();
}

void WebServer::loop()
{
    server.handleClient();
}