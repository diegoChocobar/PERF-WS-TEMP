#include <Arduino.h>

//si usas esp8266
//#include <ESP8266WiFi.h>
//#include <WebSocketsClient.h>
#include <Hash.h>

void Conectar_WiFi(){

    int cont_conexion = 0;

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    
    lcd.clear();lcd.setCursor(0, 0);
    lcd.print("Conectando WIFI...");

  while (WiFi.status() != WL_CONNECTED  and cont_conexion <50) { //Check for the connection
    cont_conexion = cont_conexion +1;
    delay(500);
    //Serial.print(".");
    lcd.print(".");
    if(WiFi.status() == WL_CONNECT_FAILED){
      //contraseña incorrecta, salimos del bucle
      cont_conexion = 100;
    }
    if (digitalRead(pulsador_escala) == 0 || digitalRead(pulsador_zero) == 0){
      /* no deseamos conectarnos con software */
      cont_conexion = 100;
      delay(100);//retardo de antirrebote
      while(digitalRead(pulsador_escala) == 0){delay(10);}//mientras tenemos presionado el pulsador
      while(digitalRead(pulsador_zero) == 0){delay(10);}//mientras tenemos presionado el pulsador

    }
    

  }


  if(WiFi.status()== WL_CONNECTED){
    ///Nos conectamos satisfactoriamente con el soft
    digitalWrite(output_led, HIGH);
    IPAddress IP = WiFi.localIP();

    lcd.clear();
    lcd.setCursor(0, 0) ;
    lcd.print("********************");
    lcd.setCursor(0, 1);
    lcd.print("**Conexion Exitosa**");
    lcd.setCursor(0, 2);
    lcd.print("IP: ");lcd.print(IP);
    lcd.setCursor(0, 3);
    lcd.print("********************");

    delay(2000);
    digitalWrite(output_led, LOW);


    ////Conectando Mqtt////////////////
    
    /////////////////////////////////////////////////////////////////////////////

  }else{
      //No nos pudimos conectar al software
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Equipo NO Conectado!");
        lcd.setCursor(0, 1);
        lcd.print("Error: ");

        ///*
        if(WiFi.status() == WL_NO_SSID_AVAIL){
          lcd.setCursor(0, 2);
          lcd.print("SSID no encontrado");
          lcd.setCursor(0, 3);
          lcd.print("********************");
        }
        if(WiFi.status() == WL_CONNECT_FAILED){
          lcd.setCursor(0, 2);
          lcd.print("Pass faild");
          lcd.setCursor(0, 3);
          lcd.print("********************");
        }
        if(WiFi.status() == WL_DISCONNECTED){
          lcd.setCursor(0, 2);
          lcd.print("Modulo STA faild");
          lcd.setCursor(0, 3);
          lcd.print("Pass faild");
        }
        //*/

        delay(2500);
  }

} 
