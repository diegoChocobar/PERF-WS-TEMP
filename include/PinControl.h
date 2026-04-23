#include <Arduino.h>
 
void pulsoPin(int pin1,int pin2, int pin3, int pin4, unsigned long duracion);


void blinkPin(int pin, unsigned long intervalo) {

  static unsigned long t_anterior = 0;
  static bool estado = false;

  if (millis() - t_anterior >= intervalo) {
    t_anterior = millis();

    estado = !estado;
    digitalWrite(pin, estado);
  }
}
void pulsoPin(int pin1,int pin2, int pin3, int pin4, unsigned long duracion) {

    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, HIGH);
    digitalWrite(pin3, HIGH);
    digitalWrite(pin4, HIGH);
    delay(duracion);
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
    digitalWrite(pin3, LOW);
    digitalWrite(pin4, LOW);
}