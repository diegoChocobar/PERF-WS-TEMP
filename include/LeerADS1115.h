#include <Arduino.h>

unsigned long LeerADS1115(int canal, int nMedidas, int16_t *señal_buffer);
ValueADS calculo_valores_ads1115(int16_t x[], int length);


ValueADS MedirADS1115(int canal, int escala){
  
  ValueADS data_ads = {0,0,0,0,0,0};//
  int16_t delta_senal[Iteraciones];
  unsigned long tiempo_medida = 0;
   
  tiempo_medida = LeerADS1115(canal, Iteraciones, delta_senal);//obtenemos en delta_senal lo valores medidos por el ads1115

  data_ads = calculo_valores_ads1115(delta_senal, Iteraciones);
  data_ads.tiempo_individual = tiempo_medida;

  return data_ads;

}

unsigned long LeerADS1115(int canal, int nMedidas, int16_t *senal_buffer){
  
  int16_t diferencia = 0;
  unsigned long tiempo_medida = millis();
  
  int ret=1;

  for (int i = 0; i < nMedidas; i++) {

    if (canal == 1) {
        diferencia = ads.readADC_Differential_0_1();
    } else if (canal == 2) {
        diferencia = ads.readADC_Differential_2_3();
    } else {
        return 0; // canal inválido
    }
    senal_buffer[i] = diferencia;
    delay(ret);//este "delay" es fundamental para que la conexión WEBSOCKET no de caiga. no es lo mismo delayMicroseconds

  }

  tiempo_medida = millis() - tiempo_medida;

  return tiempo_medida;

}

ValueADS calculo_valores_ads1115(int16_t x[], int length){

  float tension[length];
  float sumatoria=0;
  //float result=0;
  ValueADS result;
  result.valor=0;
  result.promedio=0;
  result.desvio_standar=0;

  int n=0;
  float valor=0;
  float Li=0;///limite inferior de h desvio standar
  float Ls=0;///limite superior de h desvio standar
  //float Rango=0;

//////////////Calculo de valor promerio //////////////////////////////
    for (int i = 0; i < length; i++) {
      tension[i] = float( (x[i] ) * constanteADS );
      result.promedio = result.promedio + tension[i];
    }
    result.promedio = result.promedio / length;
    result.tamaño = length;
/////////////////////////////////////////////////////////////////////////

///////////////calculo de desvio standard//////////////////    
    for (int i = 0; i < length; i++) {
        sumatoria = sumatoria + (tension[i]-result.promedio)*(tension[i]-result.promedio);
    }
    result.desvio_standar = sqrt(sumatoria/length);
////////////////////////////////////////////////////////////

//////////////calculos adicionales///////////////////////////////
    Li = result.promedio - confianza_h * result.desvio_standar; //limite inferior de h desvio standar
    Ls = result.promedio + confianza_h * result.desvio_standar; // limite superior de h desvio standar
/////////////////////////////////////////////////////////////////

//////////////Calculo del valor final ////////////////////////////
    for (int i = 0; i < length; i++) {
      
      if(tension[i]<Li || tension[i]>Ls){
        //estamos fuera del rango para tomar como buena una medicion
      }
      else{
        n = n+1;
        valor = valor + tension[i];
      }
      
    }
    result.n = n;
    result.valor = float(valor/n);
    
///////////////////////////////////////////////////////////////////


    return result;
}
