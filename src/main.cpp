#include <Arduino.h>

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_ADS1X15.h>
//#include <Adafruit_ADS1015.h>

#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include <Variables.h>
#include <Setup.h>
#include <PinControl.h>
#include <EnviarDatos.h>
#include <Ajustar.h>
#include <LeerADS1115.h>
#include <LeerCorriente.h>
#include <EscalaSelect.h>
#include <OffSetZero.h>
#include <PrintGeneral.h>
#include <ActivarHold.h>
#include <ActivarDisparo.h>
#include <Conectar_Mqtt.h>
#include <RecepcionMqtt.h>
#include <EstadoBanderas.h>


void loop(void)
{
  conectMqtt();

  tiempo_LCD = millis();
  tiempo_Ping = millis();
  tiempo_pulsadores = millis();
  tiempo_MedirCorriente = millis();
  tiempo_EnvioDatos = millis();
  tiempo_testConectMqtt = millis();


  delay(250);
  lcd.home();lcd.clear();
  lcd.setCursor(0, 0);
  if(!bandModoADS){PrintValoresLCD(deltaI, Temp_t, Prof_p);}else{PrintADS(deltaI);}
  

  while (1){

    tiempo_actual = millis();

      client.loop();

    /////chequeo de pulsadores, acciones o eventos //////
      EstadoMedirCorriente();
      EstadoPrint();
      EstadoBanderasPulsadores();
      EstadoEnvioDatos();
      EstadoTestConectMqtt();
    //////////////////////////////

    if(event[MEDIRCORRIENTE].estado){
      deltaI = MedirCorriente();
    }
    if(event[PRINT].estado){
      if(!bandModoADS){PrintValoresLCD(deltaI, Temp_t, Prof_p);}else{PrintADS(deltaI);}
    }
    if(event[OFFSET_I].estado){
      OffSetZero();
    }
    if(event[ESCALA_I].estado){
      EscalaSelect();
    }
    if(event[DISPARO].estado){
      ActivarDisparo();
    }
    if(event[HOLD].estado){
      ActivarHold();
    }
    if(event[ENVIODATOS].estado){
      event[ENVIODATOS].estado = false;
      EnviarDataCorriente(deltaI);
    }
    if(event[TEST_CONECT_MQTT].estado){
      conectMqtt();
    }
    
    delay(1);



  }


}
