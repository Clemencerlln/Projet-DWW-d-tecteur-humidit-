// ADAFRUIT IO Setup
#include "config.h"
AdafruitIO_Feed *temperature = io.feed("temperature");
AdafruitIO_Feed *humidity = io.feed("humidity");

// Components Setup
#include "Adafruit_seesaw.h"
Adafruit_seesaw ss;
//LED
int ledPinR = 27;   // the number of the LED R pin
int ledPinG = 33;   // the number of the LED G pin
int ledPinB = 32;   // the number of the LED B pin



void setup() {
  // ######## start the serial connection
  Serial.begin(115200);

  // ######## components setup
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

  // ######## connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // wait for a connection
  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
}

void loop() {
  io.run();

  // on recupere les temperatures et l'humidité
  float tempC = ss.getTemp();
  uint16_t capread = ss.touchRead(0);

  //la led est connectée au detecteur d'humiditée et change de couleur en fonction du taux d'humité
  if (capread > 1091){
  rgbLedDisplay(0, 255, 0);
  }else if (capread<=1091 && capread>642){
  rgbLedDisplay(235, 158, 0);
  }else {
  rgbLedDisplay(255, 0, 0);
}



  // save the current state to the 'digital' feed on adafruit io
  Serial.print("Temperature: "); Serial.print(tempC); Serial.println("*C");
  Serial.print("Capacitive: "); Serial.println(capread);

  temperature->save(tempC);
  humidity->save(capread);

  delay(10000);

}

// déterminer la couleur de la led rgd (rouge, vert ou bleu)
void rgbLedDisplay(int red, int green, int blue) {
  // Set three ledPin to output the PWM duty cycle
  analogWrite(ledPinR, constrain(red, 0, 255));
  analogWrite(ledPinG, constrain(green, 0, 255));
  analogWrite(ledPinB, constrain(blue, 0, 255));
}

