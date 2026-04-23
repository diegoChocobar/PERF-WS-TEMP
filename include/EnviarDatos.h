#include <Arduino.h>

#include <ESP8266HTTPClient.h>

void EnviarDisparo(String statusDisparo);
void EnviarHold(String hold);
void EnviarDataCorriente(Corrientes dataI);
void EnviarStatus(String status);


void EnviarDisparo(String statusDisparo)
{
  String str_final = statusDisparo;
  client.publish("SEV_I/SEV_C/Disparo/Status", str_final.c_str());
}

void EnviarHold(String hold)
{
  String str_final = hold;
  client.publish("SEV_I/SEV_C/Hold/Status", str_final.c_str());
}

void EnviarStatus(String status)
{

  String str_final = status;
  client.publish("SEV_I/SEV_C/Check/Status", str_final.c_str());
}

void EnviarDataCorriente(Corrientes dataI)
{

  int Escala = 0;
  event[ENVIODATOS].estado = false;

  if (bandHold ==true)
  { // si el hold esta activo, no permitimos cambiar la escala.
    return;
  }

  if (escala == 1)
  {
    Escala = 4000;
  }
  if (escala == 2)
  {
    Escala = 2000;
  }
  if (escala == 4)
  {
    Escala = 1000;
  }
  if (escala == 8)
  {
    Escala = 1000;
  }
  if (escala == 16)
  {
    Escala = 250;
  }

  String str_final = "{";
  str_final += "\"valor\":" + String(dataI.valor, 3) + ",";
  str_final += "\"promedio\":" + String(dataI.promedio, 3) + ",";
  str_final += "\"desvio_standar\":" + String(dataI.desvio_standar, 3) + ",";
  str_final += "\"tamano\":" + String(dataI.tamaño) + ",";
  str_final += "\"nmedidas\":" + String(dataI.n) + ","; // tamaño del array que queda despues de tratar la señal
  str_final += "\"tiempo_total\":" + String(dataI.tiempo_individual) + ",";
  str_final += "\"offset\":" + String(dataI.offset, 3) + ",";
  str_final += "\"ADS_Frec\":" + String(ADS_Frec) + ",";
  str_final += "\"Iteraciones\":" + String(Iteraciones) + ",";
  str_final += "\"Escala\":" + String(Escala) + ",";
  str_final += "\"Confianza\":" + String(confianza_h, 2);
  str_final += "}";

  // delay(10);

  client.publish("SEV_I/SEV_C/Config/Config", str_final.c_str());
}
