#include <Arduino.h>

bool delayMillis(unsigned long &tiempoAnterior, unsigned long intervalo);
void EstadoMedirCorriente(void);
void EstadoPrint(void);
void EstadoEnvioDatos(void);
void EstadoTestConectMqtt(void);



void EstadoBanderasPulsadores(void){

  if (delayMillis(tiempo_pulsadores, 25)){
    /////// Check estado de pulsadores cada 25ms para actualizar las banderas de eventos correspondientes //////////
    if(digitalRead(pulsador_zero) == 0){
      event[OFFSET_I].estado = true;
    }
    if(digitalRead(pulsador_escala) == 0){
      event[ESCALA_I].estado = true;
    }
    if(digitalRead(pulsador_disparo) != bandPulsadorDisparo){//si el estado del pulsador de disparo cambio
      bandPulsadorDisparo = digitalRead(pulsador_disparo);
      if(bandPulsadorDisparo==false){bandDisparo=true;}else{bandDisparo=false;}
      event[DISPARO].estado = true;
    }
    if(digitalRead(pulsador_hold) != bandPulsadorHold){//si el estado del pulsador de hold cambio
      bandPulsadorHold = digitalRead(pulsador_hold);
      if(bandPulsadorHold == true){bandHold=false;}else{bandHold=true;}
      event[HOLD].estado = true;
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  }


}
void EstadoMedirCorriente(void){

  if (delayMillis(tiempo_MedirCorriente, 100)){
    event[MEDIRCORRIENTE].estado = true;
  }

}

void EstadoPrint(void){

  if (delayMillis(tiempo_LCD, 750)){
    event[PRINT].estado = true;
  }

}

void EstadoEnvioDatos(void){

  if (delayMillis(tiempo_EnvioDatos, 1000)){
    event[ENVIODATOS].estado = true;
  }

}

void EstadoTestConectMqtt(void){

  if (delayMillis(tiempo_testConectMqtt, 15000)){
    event[TEST_CONECT_MQTT].estado = true;
  }

}

bool delayMillis(unsigned long &tiempoAnterior, unsigned long intervalo) {

  unsigned long ahora = millis();

  if ((unsigned long)(ahora - tiempoAnterior) >= intervalo) {
    tiempoAnterior = ahora;
    return true;
  }

  return false;
}