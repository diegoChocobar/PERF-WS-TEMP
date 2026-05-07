#include <Arduino.h>

void parseConfigI(String msg);

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
  if (t == "Perf_C/Perf_TP/Hold/Write" || t == "Perf_I/Perf_TP/Hold/Write")
  {
    bandHold = (msg == "ON");
    event[HOLD].estado = true;

    pulsoPin(output_led, output_zumbador, -1, -1, 250);
    return;
  }

  // =========================
  // STATUS CHECK
  // =========================
  if (t == "Perf_C/Perf_TP/Status/Read")
  {
    EnviarStatus("ON");

    pulsoPin(output_led, output_zumbador, -1, -1, 250);
    return;
  }

  // =========================
  // PROFUNDIDAD CONTROL
  // =========================
  if (t == "Perf_C/Perf_TP/Profundidad/Write")
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

  // =========================
  // (OPCIONAL) CONFIG
  // =========================
  if (t == "Perf_C/Perf_TP/Config/Values")
  {
    parseConfigI(msg);
    isEnvieDataFull = true;
    return;
  }

  if (t == "Perf_C/Perf_TP/Config/OFF")
  {
    isEnvieDataFull = false;
    return;
  }
}

void parseConfigI(String msg) {
  int pos1, pos2;

  // Buscar y extraer Iteraciones (entero)
  pos1 = msg.indexOf("\"Iteraciones\":") + 14;
  pos2 = msg.indexOf(",", pos1);
  int iteraciones = msg.substring(pos1, pos2).toInt();
  Iteraciones = iteraciones;

  // Buscar y extraer Frecuencia_ADS (entero)
  pos1 = msg.indexOf("\"Frecuencia_ADS\":") + 17;
  pos2 = msg.indexOf(",", pos1);
  int frecuencia = msg.substring(pos1, pos2).toInt();
  ADS_Frec = frecuencia;
  //*
  if (ADS_Frec==8){ads.setDataRate(RATE_ADS1115_8SPS);}//8;16;32;64;128;250;475;860
  if (ADS_Frec==16){ads.setDataRate(RATE_ADS1115_16SPS);}//8;16;32;64;128;250;475;860
  if (ADS_Frec==32){ads.setDataRate(RATE_ADS1115_32SPS);}//8;16;32;64;128;250;475;860
  if (ADS_Frec==64){ads.setDataRate(RATE_ADS1115_64SPS);}//8;16;32;64;128;250;475;860
  if (ADS_Frec==128){ads.setDataRate(RATE_ADS1115_128SPS);}//8;16;32;64;128;250;475;860
  //*/

  // Buscar y extraer Escala (entero)
  pos1 = msg.indexOf("\"Escala\":") + 9;
  pos2 = msg.indexOf(",", pos1);
  int escale = msg.substring(pos1, pos2).toInt();
  
  //*
  if (escale==2000){escala =4;}
  if (escale==1000){escala =16;}
  if (escale==250){escala =2;}
  EscalaSwitch(escala);
  //*/

  // Buscar y extraer Confianza (float)
  pos1 = msg.indexOf("\"Confianza\":") + 12;
  pos2 = msg.indexOf("}", pos1);
  float confianza = msg.substring(pos1, pos2).toFloat();
  confianza_h = confianza;

  // Aquí podés asignarlos a variables globales o usarlos
}
