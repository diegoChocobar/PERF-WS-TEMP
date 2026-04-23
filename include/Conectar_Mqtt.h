#include <Arduino.h>


//------------------------CONNECT-----------------------------
void conectMqtt() {

  event[TEST_CONECT_MQTT].estado = false;
  // Loop hasta que estamos conectados
  if (WiFi.status() != WL_CONNECTED) return;
  if (WiFi.localIP() == IPAddress(0,0,0,0)) return;

  // Loop hasta que estamos conectados
  if(WiFi.status()== WL_CONNECTED){
      if(!client.connected()){

          // Crea un ID de cliente al azar
          String clientId = "Esp_SEV_I_";
          String numero_serie_topic = (String)nSerie + "/#";
          //String topic_string = (String)numero_serie+"/Dispositivo/Saludo/Sensor Temperatura/Msg";
          String topic_subscribe_i = "SEV_C/SEV_I/#";
          String topic_subscribe_x = "SEV_C/SEV_X/#";
          String topic_subscribe_v = "SEV_V/SEV_I/#";
          String topic_public_string = "SEV_I/SEV_C/Inicio/Inicio";


          String mensajeincial = "hello world. I'm ESP_SEV_I. Serie: "+ (String)nSerie;
          String mensajereconectmqtt = "Reconect MQTT ESP_SEV_I. Serie: "+ (String)nSerie;
          clientId += String(random(0xffff),HEX);


          if (client.connect(clientId.c_str())) {
                client.subscribe(topic_subscribe_i.c_str());
                client.subscribe(topic_subscribe_x.c_str());
                client.subscribe(topic_subscribe_v.c_str());
                //client.subscribe("SEV_C/SEV_I/#");
                if(mqtt_reconect == 0){client.publish(topic_public_string.c_str(), mensajeincial.c_str());mqtt_reconect = 1;}
                else{client.publish(topic_public_string.c_str(), mensajereconectmqtt.c_str());}
                
                  lcd.setCursor(0, 3);
                  lcd.print("**Conexion Exitosa**");
                  delay(250);
                //*/
          }
      }
  }

}
