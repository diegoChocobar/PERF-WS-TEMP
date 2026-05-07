#include <Arduino.h>

#include <ESP8266HTTPClient.h>

void EnviarDataCorriente(Corrientes dataI);
void EnviarStatus(String status);


void EnviarStatus(String status)
{
  client.publish("Perf_TP/Perf_C/Status", status.c_str());
}

void EnviarTemperatura(Temperaturas temp)
{
  if (bandHold) return;

  // VALUE
  client.publish(
    "Perf_TP/Perf_C/Temperatura/Value",
    String(temp.valor, 2).c_str()
  );

  // FULL (estructura completa)
  String json = "{";
  json += "\"valor\":" + String(temp.valor, 2) + ",";
  json += "\"promedio\":" + String(temp.promedio, 2) + ",";
  json += "\"desvio_standar\":" + String(temp.desvio_standar, 2) + ",";
  json += "\"tamano\":" + String(temp.tamaño) + ",";
  json += "\"n\":" + String(temp.n) + ",";
  json += "\"tiempo_individual\":" + String(temp.tiempo_individual) + ",";
  json += "\"offset\":" + String(temp.offset, 2);
  json += "}";

  client.publish("Perf_TP/Perf_C/Temperatura/Full", json.c_str());
}

void EnviarProfundidad(Profundidad prof)
{
  if (bandHold) return;

  // VALUE
  client.publish(
    "Perf_TP/Perf_C/Profundidad/Value",
    String(prof.valor, 3).c_str()
  );

  // FULL
  String json = "{";
  json += "\"valor\":" + String(prof.valor, 3) + ",";
  json += "\"offset\":" + String(prof.offset, 3) + ",";
  json += "\"pulsos\":" + String(prof.pulsos);
  json += "}";

  client.publish("Perf_TP/Perf_C/Profundidad/Full", json.c_str());
}
