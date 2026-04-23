#include <Arduino.h>



Corrientes MedirCorriente(){
  
  
  Corrientes data_corriente = {0,0,0,0,0,0,0};//
  ValueADS data_ads = {0,0,0,0,0,0};//

  event[MEDIRCORRIENTE].estado = false;

      if(bandHold ==true){//si el hold esta activo, no permitimos medir la corriente.
        return deltaIPrint;
      }

  data_ads = MedirADS1115(canal, Iteraciones);//canal, Iteraciones son variables globales.
   
  data_corriente = AjusteValores(data_ads,escala);//deltaI es una variable global

  data_corriente.valor = data_corriente.valor - offset_1.valor;

  

  return data_corriente;
}
