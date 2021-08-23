#include "Button.h";
#include "ConexaoWifi.h";
#include "Configs.h";
#include "WebServer.h";
#include <PubSubClient.h>

//Criação do Botão
Button *button;

//Conexao Wifi
ConexaoWifi *conexao;

//Configs
Configs *config;


//WebServer
WebServer *webserver;

//MQTT
WiFiClient espClient;
PubSubClient client(espClient);

void setup()
{

  /* DEBUG  */
  Serial.begin(115200);
  delay(20);

  config = Configs::getInstance();

  config->read();

  if (config->isSetupMode)
  {
    Serial.println("Setup mode");
    conexao = new ConexaoWifi("Campainha");

    conexao->criarAP();

    webserver = new WebServer();
  }
  else
  {
    Serial.println("Running mode");

    char ssid[config->ssid.length() + 1], pass[config->ssid.length() + 1];

    config->ssid.toCharArray(ssid, config->ssid.length() + 1);

    config->password.toCharArray(pass, config->password.length() + 1);

    conexao = new ConexaoWifi(ssid, pass);

    conexao->conectar();

    button = new Button(Configs::PIN_BUTTON, 350);

    /* Set mqtt server */
    int index1 = config->server.indexOf('.');
    int addr1 = config->server.substring(0, index1).toInt();

    int index2 = config->server.indexOf('.', index1 + 1);
    int addr2 = config->server.substring(index1 + 1, index2).toInt();

    int index3 = config->server.indexOf('.', index2 + 1);
    int addr3 = config->server.substring(index2 + 1, index3).toInt();

    int index4 = config->server.indexOf('.', index3 + 1);
    int addr4 = config->server.substring(index3 + 1, index4).toInt();

    IPAddress ipAddr(addr1, addr2, addr3, addr4);

    client.setServer(ipAddr, 1883);

  }
}

void loop()
{

  if (config->isSetupMode)
  {
    webserver->loop();
  }
  else
  {

    buttonReturn buttonRead = button->read();

    if (buttonRead.pressed)
    {
      client.publish("bellRing", "1");
      Serial.print("Button pressed");
    }

    if (buttonRead.reset)
    {
      Serial.print("Reset");
      config->clear();
      delay(3500);
      ESP.restart();
    }

    if (!client.connected())
    {
        reconnect();
    }
    client.loop();

  }
}


void reconnect()
{

    while (!client.connected())
    {
        Serial.print("Attempting MQTT connection...");

        if (client.connect("campainhaModule"))
        {
            Serial.println("connected");
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 3 seconds");

            delay(3000);
        }

        buttonReturn buttonRead = button->read();

        if (buttonRead.reset)
        {
            Serial.print("Reset");
            config->clear();
            delay(3500);
            ESP.restart();
        }
    }
}
