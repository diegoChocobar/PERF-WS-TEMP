#include <Arduino.h>

void OffSetZero(void){

  event[OFFSET_I].estado = false;

  if(bandHold ==true){//si el hold esta activo, no permitimos cambiar la escala.
    return;
  }
      if (bandZero == true) {
        bandZero = false;
        pulsoPin(output_zumbador,output_led,-1,-1,100);
        offset_1.valor = deltaIPrint.valor;//guardamos el valor actual de deltaIPrint.valor como offset_1.valor para restarlo posteriormente a las mediciones de corriente
        event[PRINT].estado = true;
        event[OFFSET_I].print_status = true;
        while(digitalRead(pulsador_zero) == 0){delay(10);} //mientras tenememos presionado el pulsador de zero off set

      }else{
        bandZero = true;
        pulsoPin(output_zumbador,output_led,-1,-1, 100);
        event[PRINT].estado = true;
        event[OFFSET_I].print_status = true;
        while(digitalRead(pulsador_zero) == 0){delay(10);} //mientras tenememos presionado el pulsador de zero off set
        offset_1 = {0,0,0,0,0,0,0};
        offset_2 = {0,0,0,0,0,0,0};
      }


}