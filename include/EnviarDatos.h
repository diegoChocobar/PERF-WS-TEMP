#include <Arduino.h>

#include <ESP8266HTTPClient.h>


void EnviarStatus(String status)
{
  client.publish("PERF_TP/PERF_C/STATUS/WRITE", status.c_str());
  event[TEST_CONECT_MQTT].print_status = true;
}

void EnviarTemperatura(Temperaturas temp)
{
  if (bandHold) return;

  // VALUE
  client.publish(
    "PERF_TP/PERF_X/TEMPERATURA/VALUE",
    String(temp.valor, 2).c_str()
  );

  // FULL (estructura completa)
  String json = "{";
  json += "\"valor\":" + String(temp.valor, 2) + ",";
  json += "\"promedio\":" + String(temp.promedio, 2) + ",";
  json += "\"desvio_standar\":" + String(temp.desvio_standar, 2) + ",";
  json += "\"tamano\":" + String(temp.tamaño) + ",";
  json += "\"n\":" + String(temp.n) + ",";
  json += "\"tiempo_individual\":" + String(temp.tiempo_individual);
  json += "}";

  client.publish("PERF_TP/PERF_C/TEMPERATURA/FULL", json.c_str());
}

void EnviarProfundidad(Profundidad prof)
{
  if (bandHold) return;

  // VALUE
  client.publish(
    "PERF_TP/PERF_X/PROFUNDIDAD/VALUE",
    String(prof.valor, 3).c_str()
  );

  // FULL
  String json = "{";
  json += "\"valor\":" + String(prof.valor, 3) + ",";
  json += "\"offset\":" + String(prof.offset, 3) + ",";
  json += "\"pulsos\":" + String(prof.pulsos);
  json += "}";

  client.publish("PERF_TP/PERF_C/PROFUNDIDAD/FULL", json.c_str());
}
