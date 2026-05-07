void conectMqtt() {

  event[TEST_CONECT_MQTT].estado = false;

  if (WiFi.status() != WL_CONNECTED) return;
  if (WiFi.localIP() == IPAddress(0,0,0,0)) return;

  if (!client.connected()) {

    String clientId = "Perf_TP_";
    clientId += String(random(0xffff), HEX);

    String topic_subscribe = "Perf_C/Perf_TP/#";
    String topic_public = "Perf_TP/Status/Init";

    String msg_init = "Device Perf_TP online. Serie: " + (String)nSerie;
    String msg_reconnect = "MQTT reconnect Perf_TP. Serie: " + (String)nSerie;

    if (client.connect(clientId.c_str())) {

      client.subscribe(topic_subscribe.c_str());

      if (mqtt_reconect == 0) {
        client.publish(topic_public.c_str(), msg_init.c_str());
        mqtt_reconect = 1;
      } else {
        client.publish(topic_public.c_str(), msg_reconnect.c_str());
      }

      lcd.setCursor(0, 3);
      lcd.print("MQTT OK");
    }
  }
}