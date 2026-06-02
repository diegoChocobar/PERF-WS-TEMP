void conectMqtt() {

  event[TEST_CONECT_MQTT].estado = false;

  if (WiFi.status() != WL_CONNECTED) return;
  if (WiFi.localIP() == IPAddress(0,0,0,0)) return;

  if (!client.connected()) {

    String clientId = "PERF_TP_";
    clientId += String(random(0xffff), HEX);

    String subscribe_C = "PERF_C/PERF_TP/#";
    String subscribe_X_HOLD_C = "PERF_C/PERF_X/HOLD/WRITE";
    String subscribe_X_HOLD_I = "PERF_I/PERF_X/HOLD/WRITE";
    String topic_public_string = "SEV_V/SEV_C/Inicio/Inicio";

    String mensajeincial = "hello world. I'm ESP_SEV_T. Serie: "+ (String)nSerie;
    String mensajereconectmqtt = "Reconect MQTT ESP_SEV_T. Serie: "+ (String)nSerie;

    if (client.connect(clientId.c_str())) {

      client.subscribe(subscribe_C.c_str());
      client.subscribe(subscribe_X_HOLD_C.c_str());
      client.subscribe(subscribe_X_HOLD_I.c_str());
        if(mqtt_reconect == 0){client.publish(topic_public_string.c_str(), mensajeincial.c_str());mqtt_reconect = 1;}
        else{client.publish(topic_public_string.c_str(), mensajereconectmqtt.c_str());}

      lcd.setCursor(0, 3);
      lcd.print("MQTT OK");
    }
  }
}