#include <Arduino.h>

//////////////////////////////////////////////////////////////////////
/////////////// Recepcion de Datod MQTT /////////////////////////////
/////////////////////////////////////////////////////////////////////
//void callback(char* topic, byte* payload, unsigned int length) {}
///*
void callback(char* topic, byte* payload, unsigned int length)
{
  String t = String(topic);

  String msg;
  msg.reserve(length);

  for (unsigned int i = 0; i < length; i++) {
    msg += (char)payload[i];
  }

  // =========================
  // HOLD (desde C o desde I)
  // =========================
  if (t == "PERF_C/PERF_X/HOLD/WRITE" || t == "PERF_I/PERF_TP/HOLD/WRITE")
  {
    bandHold = (msg == "ON");
    event[HOLD].estado = true;

    pulsoPin(output_led, output_zumbador, -1, -1, 250);
    return;
  }

  // =========================
  // STATUS CHECK
  // =========================
  if (t == "PERF_C/PERF_TP/STATUS/READ")
  {
    EnviarStatus("ON");

    pulsoPin(output_led, output_zumbador, -1, -1, 250);
    return;
  }

  // =========================
  // PROFUNDIDAD CONTROL
  // =========================
  if (t == "PERF_C/PERF_TP/PROFUNDIDAD/WRITE")
  {
    if (msg == "+") {
      event[PROFUNDIDAD_MAS].estado = true;
    }
    else if (msg == "-") {
      event[PROFUNDIDAD_MENOS].estado = true;
    }
    else if (msg == "RESET") {
      event[OFFSET_PROF].estado = true;
    }

    pulsoPin(output_led, output_zumbador, -1, -1, 250);
    return;
  }

}
