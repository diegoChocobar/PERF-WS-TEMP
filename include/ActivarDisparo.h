#include <Arduino.h>

void ActivarDisparo(void){

    /////////////////////////////////////////////////////////////
    event[DISPARO].estado = false;
    event[PRINT].estado = true;
    event[DISPARO].print_status = true;
    if(bandDisparo==true){EnviarDisparo("ON");}else{EnviarDisparo("OFF");}
    
    pulsoPin(output_zumbador,output_led,-1,-1,100);
    digitalWrite(output_disparo, bandDisparo);
    digitalWrite(output_zumbador, bandDisparo);
    digitalWrite(output_led, bandDisparo);
    /////////////////////////////////////////////////////////////

}
