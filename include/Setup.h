#include <Arduino.h>

//#include <Variables.h>
#include <PrintNumber.h>

#include <Conectar_WiFi.h>

void SaludoInicial();
void setearDataRateADS(int escala);

void setup(void)
{
  pinMode(pulsador_escala, INPUT_PULLUP);//Configuramos el pin como entrada pullup
  digitalWrite(pulsador_escala, HIGH);

  pinMode(pulsador_zero, INPUT_PULLUP);//Configuramos el pin como entrada pullup
  digitalWrite(pulsador_zero, HIGH);

  pinMode(pulsador_hold, INPUT_PULLUP);//Configuramos el pin como entrada pullup
  digitalWrite(pulsador_hold, HIGH);

  pinMode(pulsador_disparo, INPUT_PULLUP);//Configuramos el pin como entrada pullup
  digitalWrite(pulsador_disparo, HIGH);


  pinMode(output_led, OUTPUT);
  digitalWrite(output_led, LOW);

  pinMode(output_zumbador, OUTPUT);
  digitalWrite(output_zumbador, LOW);

  pinMode(output_disparo, OUTPUT);
  digitalWrite(output_disparo, LOW);
  
  delay(10);

////////////////// ENTRAMOS EN MODO CALIBRACION? ////////////////////////////////////////////////////
  if(digitalRead(pulsador_zero) == 0){
    //entramos en el modo calibracion (desactivamos la funcion calibrar)
    bandModoADS = true;
  }else{
    //entramos en el modo normal (activamos la funcion calibrar)
    bandModoADS = false; 
  }
////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////CONFIGURACION DE ADS1115 ///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
  // The ADC input range (or gain) can be changed via the following
  // functions, but be careful never to exceed VDD +0.3V max, or to
  // exceed the upper and lower limits if you adjust the input range!
  // Setting these values incorrectly may destroy your ADC!
  //                                                                ADS1015  ADS1115
  //                                                                -------  -------
  //ads.setGain(GAIN_TWOTHIRDS);constanteADS=0.1875;escala =0;  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
  //ads.setGain(GAIN_ONE);constanteADS=0.125;escala =1;        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  ads.setGain(GAIN_TWO);constanteADS=0.0625;escala =2;        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  //ads.setGain(GAIN_FOUR);constanteADS=0.03125;escala =4;       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
  //ads.setGain(GAIN_EIGHT);constanteADS=0.015625;escala =8;      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
  //ads.setGain(GAIN_SIXTEEN);constanteADS=0.0078125;escala =16;    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV

  setearDataRateADS(ADS_Frec);
  ads.begin();
///////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////CONFIGURACION DEL LCD ////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
  lcd.init();             //Inicializa o LCD
  lcd.display();          //Enciende el muestreo de las Letras
  lcd.setBacklight(1);    //Enciende la luz de fondo (0:off;1:on)


  //Associa cada segmento criado, a um número
  lcd.createChar(0,LT);
  lcd.createChar(1,UB);
  lcd.createChar(2,RT);
  lcd.createChar(3,LL);
  lcd.createChar(4,LB);
  lcd.createChar(5,LR);
  lcd.createChar(6,UMB);
  lcd.createChar(7,LMB);

  SaludoInicial();

  Conectar_WiFi();


  client.setServer(mqtt_server, mqtt_port);
  client.setKeepAlive(60);  // <-- Aumenta el intervalo para mantener la conexión viva (60 segundos)
  client.setCallback(callback);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

void SaludoInicial(){
   
    lcd.setCursor(0, 0);
    lcd.print("***CDC Elctronics***");
    lcd.setCursor(0, 1);
    lcd.print(" PERF-WS-I -> v2.05 ");
    lcd.setCursor(0, 2);
    lcd.print("Serie: ");
    lcd.print(nSerie);
    lcd.print(" Cliente");
    lcd.setCursor(0, 3);
    lcd.print("Calibracion:");
    if(bandCalibracion==true){lcd.print("TRUE");}else{lcd.print("FALSE");}
    ///*
      for (size_t i = 0; i < 5; i++)
      {
        digitalWrite(output_led, HIGH);
        digitalWrite(output_zumbador, HIGH);
        delay(250);
        digitalWrite(output_led, LOW);
        digitalWrite(output_zumbador, LOW);
        delay(250);
      }
    
    //*/

    //delay(2500);

}
void setearDataRateADS(int escala) {

  switch (escala) {

    case 8:
      ads.setDataRate(RATE_ADS1115_8SPS);
      break;

    case 16:
      ads.setDataRate(RATE_ADS1115_16SPS);
      break;

    case 32:
      ads.setDataRate(RATE_ADS1115_32SPS);
      break;

    case 64:
      ads.setDataRate(RATE_ADS1115_64SPS);
      break;

    case 128:
      ads.setDataRate(RATE_ADS1115_128SPS);
      break;

    case 250:
      ads.setDataRate(RATE_ADS1115_250SPS);
      break;

    case 475:
      ads.setDataRate(RATE_ADS1115_475SPS);
      break;

    case 860:
      ads.setDataRate(RATE_ADS1115_860SPS);
      break;

    default:
      ads.setDataRate(RATE_ADS1115_128SPS); // valor seguro por defecto
      break;
  }
}
