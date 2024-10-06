String finalUrl;

void initWifi()
{
  WiFi.begin(ssid, PASS);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print("--");
  }
  Serial.println("");
  Serial.print("Received IP Address : ");
  Serial.print(WiFi.localIP());
  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);
  delay(1000);
}

void sendMessageByInternet(ESP8266WiFiMulti WiFiMulti, float currentTemp)
{

  if (WiFiMulti.run() == WL_CONNECTED)
  {
    std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);
    client->setFingerprint(fingerprint);
    client->setFingerprint(fingerprint);
    Serial.println("connected...");
    HTTPClient http;

    if (currentTemp < MINIMUN_TEMP)
    {
      finalUrl = BASE_URL + BOT_API_KEY + FIRST_SUF + MY_CHANNEL_ID + SEC_SUF + MY_MESSAGE_TEXT_DOWN + " : " 
      + currentTemp + CELSIOR;
    }
    else
    {
      finalUrl = BASE_URL + BOT_API_KEY + FIRST_SUF + MY_CHANNEL_ID + SEC_SUF + MY_MESSAGE_TEXT_UP + " : " 
      + currentTemp + CELSIOR;
    }

    if (http.begin(*client, finalUrl))
    {
      Serial.println("http.begin ok");
    }
    Serial.println(finalUrl.c_str());

    int httpResponseCode = http.GET();

    if (httpResponseCode > 0)
    {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      String payload = http.getString();
      Serial.println(payload);
    }
    else
    {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  }
  else
  {
    Serial.println("WiFi Disconnected");
  }
  delay(1000);
}
