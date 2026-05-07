#include <Arduino.h>

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_ADS1X15.h>
// #include <Adafruit_ADS1015.h>

#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include <Variables.h>
#include <Setup.h>
#include <PinControl.h>
#include <EnviarDatos.h>
#include <Ajustar.h>
#include <LeerADS1115.h>
#include <MedirTemperatura.h>
#include <EscalaSelect.h>
// #include <OffSetZero.h>
#include <PrintGeneral.h>
#include <ActivarHold.h>
#include <ActivarDisparo.h>
#include <Conectar_Mqtt.h>
#include <RecepcionMqtt.h>
#include <EstadoBanderas.h>
#include <Encoder.h>
#include <Pulsadores.h>
//#include <MedirTemperatura.h>

void loop(void)
{
  conectMqtt();

  tiempo_LCD = millis();
  tiempo_Ping = millis();
  tiempo_pulsadores = millis();
  tiempo_MedirTemperatura = millis();
  tiempo_EnvioDatos = millis();
  tiempo_testConectMqtt = millis();
  tiempo_MedirProfundidad = millis();

  delay(250);
  lcd.home();
  lcd.clear();
  lcd.setCursor(0, 0);
  if (!bandModoADS)
  {
    PrintValoresLCD(deltaI, Temp, Prof);
  }
  else
  {
    PrintADS(Temp);
  }

  while (1)
  {

    tiempo_actual = millis();

    client.loop();

    /////chequeo de pulsadores, acciones o eventos //////
    EstadoMedirTemperatura();
    EstadoPrint();
    EstadoBanderasPulsadores();
    EstadoEnvioDatos();
    EstadoTestConectMqtt();
    EstadoMedirProfundidad();
    //////////////////////////////

    if (event[MEDIRTEMPERATURA].estado)
    {
      event[MEDIRTEMPERATURA].estado = false;
      Temp = MedirTemperatura();
    }
    if (event[MEDIRPROFUNDIDAD].estado)
    {
      calcularProfundidad();
    }
    if (event[PRINT].estado)
    {
      if (!bandModoADS)
      {
        PrintValoresLCD(deltaI, Temp, Prof);
      }
      else
      {
        PrintADS(Temp);
      }
    }
    if (event[PROFUNDIDAD_MAS].estado)
    {
      ProfundidadMas();
    }

    if (event[PROFUNDIDAD_MENOS].estado)
    {
      ProfundidadMenos();
    }

    if (event[OFFSET_PROF].estado)
    {
      ResetProfundidad();
    }

    if (event[HOLD].estado)
    {
      ActivarHold();
    }
    if (event[ENVIODATOS].estado)
    {
      event[ENVIODATOS].estado = false;

      EnviarTemperatura(Temp);
      EnviarProfundidad(Prof);
    }
    if (event[TEST_CONECT_MQTT].estado)
    {
      conectMqtt();
    }

    delay(1);
  }
}
