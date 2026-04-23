#include <Arduino.h>

Corrientes AjusteValores(ValueADS data_ads, int y){//x:tension_ads y:escala

    boolean negativo = false;
    Corrientes data_corriente;//
    ////////Asociacion de valores 1a1////////////////
      data_corriente.valor = data_ads.valor;
      data_corriente.desvio_standar = data_ads.desvio_standar;
      data_corriente.n = data_ads.n;
      data_corriente.promedio = data_ads.promedio;
      data_corriente.tamaño = data_ads.tamaño;
      data_corriente.tiempo_individual = data_ads.tiempo_individual;
      data_corriente.offset = offset_1.valor;
    ////////////////////////////////////////////////  


  if(data_ads.valor < 0){
    data_ads.valor = data_ads.valor * -1;
    negativo = true;
  }

  if(y == 2){//tension maxima a medir son +/- 2.048V con resolucion de 0.0625mV

  }

  if(y == 4){//tension maxima a medir son +/- 1.024V con resolucion de 0.03125mV

  }

  if(y == 16){//tension maxima a medir son +/- 0.256V con resolucion de 0.0078125mV

  }

    if(negativo == true){
        data_ads.valor = data_ads.valor*-1;
    }

    return data_corriente;
}
