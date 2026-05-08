#include <Arduino.h>

Temperaturas AjusteValores(ValueADS data_ads){

    boolean negativo = false;
    Temperaturas data_temperatura;//
    float a = 1.0;
    float b = 0.0;
    ////////Asociacion de valores 1a1////////////////
      data_temperatura.valor = data_ads.valor;
      data_temperatura.desvio_standar = data_ads.desvio_standar;
      data_temperatura.n = data_ads.n;
      data_temperatura.promedio = data_ads.promedio;
      data_temperatura.tamaño = data_ads.tamaño;
      data_temperatura.tiempo_individual = data_ads.tiempo_individual;
    ////////////////////////////////////////////////  


  if(data_ads.valor < 0){
    data_ads.valor = data_ads.valor * -1;
    negativo = true;
  }

  if( bandCalibracion == true){//si estamos en modo calibrado, aplicamos el ajuste a la tension medida, segun la escala y el canal seleccionado
        if(escala == 2){//tension maxima a medir son +/- 2.048V con resolucion de 0.0625mV
            if(data_ads.valor>0.02 && data_ads.valor<=600){
              a=1.0141;b=-0.0435;
            }
            if(data_ads.valor>600 && data_ads.valor<=1500){
              a=1.01481;b=-0.615;
            }
            if(data_ads.valor>1500){
              a=1.07641;b=-97.1808;
            }
        }

        if(escala == 4){//tension maxima a medir son +/- 1.024V con resolucion de 0.03125mV
            if(data_ads.valor>0.02 && data_ads.valor<=600){
              a=1.01509;b=-0.0601;
            }
            if(data_ads.valor>600){
              a=1.01514;b=0.0303;
            }
        }

        if(escala == 16){//tension maxima a medir son +/- 0.256V con resolucion de 0.0078125mV
            if(data_ads.valor>0.02){
              a=0.05124;b=-0.0189;
            }
        }
  }


  data_temperatura.valor = (data_ads.valor * a) + b;
  data_temperatura.promedio = (data_ads.promedio * a) + b;
  data_temperatura.desvio_standar = data_ads.desvio_standar * a;

  if(negativo == true){
      data_temperatura.valor = data_temperatura.valor * -1;
  }


    return data_temperatura;
}
