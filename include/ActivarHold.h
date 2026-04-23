#include <Arduino.h>

void ActivarHold(void){

    event[HOLD].estado = false;
    event[PRINT].estado = true;
    event[HOLD].print_status = true;

    pulsoPin(output_zumbador,output_led,-1,-1,100);
    digitalWrite(output_zumbador, bandDisparo);
    digitalWrite(output_led, bandDisparo);

    if(bandHold ==true){//debemos congelar Print, y dejar de medir corriente, pero no debemos dejar de enviar el ping para mantener la conexión mqtt activa
      EnviarHold("ON");
      PrintEvento();
      event[PRINT].estado = false;
      event[HOLD].print_status = false;
    }
    else{
      EnviarHold("OFF");
      event[PRINT].estado = true;
      event[HOLD].print_status = false;
    }


}