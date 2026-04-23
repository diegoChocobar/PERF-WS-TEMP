#include <Arduino.h>

void EscalaSwitch(int x);

void EscalaSelect(void){

  event[ESCALA_I].estado = false;

  if(bandHold ==true){//si el hold esta activo, no permitimos cambiar la escala.
    return;
  }

  
  event[PRINT].estado = true;
  event[ESCALA_I].print_status = true;
  pulsoPin(output_zumbador,output_led,-1,-1,100);

  while(digitalRead(pulsador_escala) == 0){delay(10);}//mientras tenemos presionado el pulsador
  EscalaSwitch(escala);
}

void EscalaSwitch(int x){

        switch (x) {
          case 2:
            ads.setGain(GAIN_SIXTEEN);constanteADS=0.0078125;escala =16;
          break;

          case 4:
            ads.setGain(GAIN_TWO);constanteADS=0.0625;escala =2;
          break;

          case 16:
            ads.setGain(GAIN_FOUR);constanteADS=0.03125;escala =4;
          break;

          default:
            ads.setGain(GAIN_TWO);constanteADS=0.0625;escala =2;
          break;
        }
}