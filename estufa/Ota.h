
void setupOTA()
{
  WiFi.mode(WIFI_STA);
  ArduinoOTA.onStart([]()
  {
    Serial.println("Starting OTA");
  });
  ArduinoOTA.onEnd([]()
  {
    Serial.println("Ending OTA");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total)
  {
    Serial.printf("Progresso: %u%%r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error)
  {
    Serial.printf("Erro [%u]: ", error);
    if (error == OTA_AUTH_ERROR)
      Serial.println("OTA Authentication Failure");
    else if (error == OTA_BEGIN_ERROR)
      Serial.println("OTA initialization failed");
    else if (error == OTA_CONNECT_ERROR)
      Serial.println("OTA Connection Failed");
    else if (error == OTA_RECEIVE_ERROR)
      Serial.println("OTA RX failure");
    else if (error == OTA_END_ERROR)
      Serial.println("OTA End Failure");
  });
  ArduinoOTA.begin();
  Serial.println("OTA initialized");
}
