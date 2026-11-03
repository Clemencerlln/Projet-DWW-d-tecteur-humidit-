#include "Adafruit_seesaw.h"

Adafruit_seesaw ss;

//LED
int ledPinR = 27;   // the number of the LED R pin
int ledPinG = 33;   // the number of the LED G pin
int ledPinB = 32;   // the number of the LED B pin

 

void setup() {
  //setup Soilsensor 
  Serial.begin(115200);

  Serial.println("seesaw Soil Sensor example!");
  
  if (!ss.begin(0x36)) {
    Serial.println("ERROR! seesaw not found");
    while(1) delay(1);
  } else {
    Serial.print("seesaw started! version: ");
    Serial.println(ss.getVersion(), HEX);
  }
  //setup LED
  pinMode(ledPinR, OUTPUT);
  pinMode(ledPinG, OUTPUT);
  pinMode(ledPinB, OUTPUT);
}

void loop() {
  float tempC = ss.getTemp();
  uint16_t capread = ss.touchRead(0);

  Serial.print("Temperature: "); Serial.print(tempC); Serial.println("*C");
  Serial.print("Capacitive: "); Serial.println(capread);

//la led est connectée au detecteur d'humiditée et change de couleur en fonction du taux d'humité
if (capread > 80){
  rgbLedDisplay(0, 255, 0);
}else if (capread<=80 && capread>50){
  rgbLedDisplay(235, 158, 0);
}else {
  rgbLedDisplay(255, 0, 0);
}

  delay(10000);
}

// déterminer la couleur de la led rgd (rouge, vert ou bleu)
oid rgbLedDisplay(int red, int green, int blue) {
  // Set three ledPin to output the PWM duty cycle
  analogWrite(ledPinR, constrain(red, 0, 255));
  analogWrite(ledPinG, constrain(green, 0, 255));
  analogWrite(ledPinB, constrain(blue, 0, 255));
}

