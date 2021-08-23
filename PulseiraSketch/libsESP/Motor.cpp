/*
    Motor.cpp - Libary to control Vibration Motor
    Created by Gabriel de Carvalho Souza
*/

#include "Arduino.h";
#include "Motor.h";

unsigned long int lastTime;
int motorOn = 1;

Motor::Motor(int pin, unsigned int TimeOn, unsigned int TimeOff){
    Motor::pin = pin;
    alerting = false;
    lastTime = 0;
    Serial.println(alertTimeOff);
    alertTimeOn = TimeOn;
    alertTimeOff = TimeOff;
    
    pinMode(pin, OUTPUT);
}

void Motor::loop(){

    if(alerting){
        if(motorOn ==1){
            Serial.println("Motor off var");
            if(millis() > alertTimeOn + lastTime){
                Serial.print(" Antes: ");
                Serial.println(motorOn);
                Motor::turnOff();
                Serial.print("M Offf ");
                Serial.print(lastTime);
                Serial.print(" Despois: ");
                Serial.println(motorOn);
                lastTime = millis();
                Serial.println(lastTime);
            }
        }
        if(motorOn == 0){
            Serial.println("Motor onnn var");
            Serial.println(millis());
            Serial.println(alertTimeOff);
            Serial.println(lastTime);
            if(millis() > alertTimeOff + lastTime){
                Motor::turnOn();
                Serial.println("M Onnnnn ");
                Serial.print(lastTime);
                Serial.print(" ");
                Serial.println(motorOn);
                lastTime = millis();
            }
        }
        

    }

}

void Motor::turnOn(){
    Serial.println("on");
    digitalWrite(pin, HIGH);
    motorOn = 1;
}

void Motor::turnOff(){
    Serial.println("off");
    digitalWrite(pin, LOW);
    motorOn = 0;
}

void Motor::alertOn(){
    Serial.println("alerting motor true");
    alerting = true;
}

void Motor::alertOff(){
    Serial.println("alerting motor false");
    alerting = false;
    turnOff();
}





