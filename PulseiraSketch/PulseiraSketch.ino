#include "Led.h";
#include "Button.h";
#include "ConexaoWifi.h";
#include "Configs.h";
#include "WebServer.h";
#include "Receiver.h";

//Motor Vibra
bool motorAlerting, motorOn;
int motorState= LOW;
const long alertTimeOn = 2000, alertTimeOff = 3000;
unsigned long lastTimeMotor = 0;

//Led Neo Pixel ( 7 leds rgb )
Led *led;

//Botão(dasativa alerta e reset)
Button *button;

//Conexao Wifi
ConexaoWifi *conexao;

//Configs Gerais
Configs *config;

//WebServer página de configurações
WebServer *webserver;

//Receiver MQTT
Receiver *receiver;

void setup()
{

  /* DEBUG  */
  Serial.begin(115200);
  delay(20);
  /* DEBUG */

  config = Configs::getInstance();

  config->read();

  if (config->isSetupMode)
  {
    Serial.println("Setup mode");
    conexao = new ConexaoWifi("Pulseira");

    conexao->criarAP(); // criação do Acess Point para acesso as configurações

    webserver = new WebServer(); // cria o webserver que servirá as paginas de configuração
  }
  else
  {
    Serial.println("Running mode");

    char ssid[config->ssid.length() + 1], pass[config->ssid.length() + 1];

    config->ssid.toCharArray(ssid, config->ssid.length() + 1);

    config->password.toCharArray(pass, config->password.length() + 1);

    conexao = new ConexaoWifi(ssid, pass);

    conexao->conectar(); // conectar a rede previamente configurada no modo setup
    delay(10);
    Serial.print("Server: ");
    Serial.println(config->server);
    receiver = new Receiver(config->server, alert); // handler do recebimento de mensagens MQTT
    delay(10);
    led = new Led(Configs::PIN_LEDS, config->RColor, config->GColor, config->BColor);
    led->setAnimation(config->animation);

    button = new Button(Configs::PIN_BUTTON, 350);

    //Configs Motor
    motorAlerting = false;
    motorOn = false;
    pinMode(14, OUTPUT);
    digitalWrite(14, motorState);

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

      Serial.print("Button pressed");
      
      motorAlerting = false;
      motorState = LOW;
      digitalWrite(14, motorState);
      
      led->alertOff();
    }

    if (buttonRead.reset)
    {
      Serial.print("Reset esp");
      config->clear();
      delay(3500);
      ESP.restart();
    }

    led->loop();
    receiver->loop();

    motorLoop();
  }
}

void alert(char *topic, byte *payload, unsigned int length)
{
  if (strcmp(topic, "bellRing") == 0)
  {
    Serial.print("Alert On!");
    motorAlerting = true;
    led->alertOn();
  }
}

void motorLoop()
{

  if (motorAlerting)
  {
    unsigned long currentMillis = millis();

    if (currentMillis - lastTimeMotor >= alertTimeOn) {
      // save the last time you blinked the LED
      lastTimeMotor = currentMillis;
  
      // if the LED is off turn it on and vice-versa:
      if (motorState == LOW) {
        motorState = HIGH;
      } else {
        motorState = LOW;
      }
  
      // set the LED with the ledState of the variable:
      digitalWrite(14, motorState);
    }
  }
}
