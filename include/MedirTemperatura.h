#include <Arduino.h>



Temperaturas MedirTemperatura(){
  
  
  Temperaturas data_temperatura = {0,0,0,0,0,0,0};//
  ValueADS data_ads = {0,0,0,0,0,0};//

  event[MEDIRTEMPERATURA].estado = false;

      if(bandHold ==true){//si el hold esta activo, no permitimos medir la corriente.
        return Temp;
      }

  data_ads = MedirADS1115();//canal, Iteraciones son variables globales.
  //data_temperatura 
  data_temperatura = AjusteValores(data_ads);//deltaI es una variable global

  return data_temperatura;
}
