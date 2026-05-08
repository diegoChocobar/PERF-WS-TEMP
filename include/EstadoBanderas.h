#include <Arduino.h>

bool delayMillis(unsigned long &tiempoAnterior, unsigned long intervalo);
void EstadoMedirTemperatura(void);
void EstadoPrint(void);
void EstadoEnvioDatos(void);
void EstadoTestConectMqtt(void);
void EstadoMedirProfundidad(void);

void EstadoBanderasPulsadores(void)
{
  // --- lectura SIEMPRE (no depende de delay) ---
  bool mas = (digitalRead(pulsador_mas) == LOW);
  bool menos = (digitalRead(pulsador_menos) == LOW);

  static bool last_mas = false; //las clausulas static significan que la variable se inicializa una sola vez y luego mantiene su valor entre llamadas a la funcion.
  static bool last_menos = false;

  static unsigned long t_repeat_mas = 0;
  static unsigned long t_repeat_menos = 0;

  static unsigned long t_reset = 0;
  static bool reset_en_proceso = false;

  //PRIORIDAD: RESET (ambos botones)
  if (mas && menos)
  {
    if (!reset_en_proceso)
    {
      t_reset = millis();
      reset_en_proceso = true;
    }

    if (millis() - t_reset >= 2000)
    {
      event[OFFSET_PROF].estado = true;
    }

    // mientras están ambos, no procesamos nada más
    last_mas = mas;
    last_menos = menos;
    return;
  }
  else
  {
    reset_en_proceso = false;
  }

  //FLANCO + REPETICIÓN MAS

  // flanco (click corto)
  if (mas && !last_mas)
  {
    event[PROFUNDIDAD_MAS].estado = true;
    t_repeat_mas = millis(); // reinicia repetición
  }

  // repetición al mantener
  if (mas && (millis() - t_repeat_mas > 300))
  {
    event[PROFUNDIDAD_MAS].estado = true;
    t_repeat_mas = millis();
  }

  //FLANCO + REPETICIÓN MENOS

  if (menos && !last_menos)
  {
    event[PROFUNDIDAD_MENOS].estado = true;
    t_repeat_menos = millis();
  }

  if (menos && (millis() - t_repeat_menos > 300))
  {
    event[PROFUNDIDAD_MENOS].estado = true;
    t_repeat_menos = millis();
  }

  // ACTUALIZAR ESTADOS
  last_mas = mas;
  last_menos = menos;
}

void EstadoMedirTemperatura(void)
{

  if (delayMillis(tiempo_MedirTemperatura, 250))
  {
    event[MEDIRTEMPERATURA].estado = true;
  }
}

void EstadoPrint(void)
{

  if (delayMillis(tiempo_LCD, 500))
  {
    event[PRINT].estado = true;
  }
}

void EstadoEnvioDatos(void)
{

  if (delayMillis(tiempo_EnvioDatos, 1000))
  {
    event[ENVIODATOS].estado = true;
  }
}

void EstadoTestConectMqtt(void)
{

  if (delayMillis(tiempo_testConectMqtt, 15000))
  {
    event[TEST_CONECT_MQTT].estado = true;
  }
}

void EstadoMedirProfundidad(void)
{
  if (delayMillis(tiempo_MedirProfundidad, 250))
  {
    event[MEDIRPROFUNDIDAD].estado = true;
  }
}

bool delayMillis(unsigned long &tiempoAnterior, unsigned long intervalo)
{

  unsigned long ahora = millis();

  if ((unsigned long)(ahora - tiempoAnterior) >= intervalo)
  {
    tiempoAnterior = ahora;
    return true;
  }

  return false;
}