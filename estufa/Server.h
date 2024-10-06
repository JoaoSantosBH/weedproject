
void renderHtml(WiFiClient client, float currentTemp, int lumens, boolean mustPlayAlarm)
{
  client.println("HTTP/1.1 200 OK");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head>");
  client.println("<meta charset=\"utf-8\"/>");
  client.println("<style type=\"text/css\">");
  client.println("body {");
  client.println("background: black;");
  client.println("margin: 0 auto;");
  client.println("max-width: 56em;");
  client.println("padding: 1em 0;");
  client.println("}");
  client.println(".grid {");
  client.println("display: flex;");
  client.println("flex-wrap: wrap;");
  client.println("display: grid;");
  client.println("grid-template-columns: repeat(auto-fill, minmax(200px, 1fr));");
  client.println("grid-auto-rows: minmax(150px, auto);");
  client.println("grid-gap: 1em;");
  client.println("}");
  client.println(".module {");
  client.println("background: #eaeaea;");
  client.println("display: flex;");
  client.println("align-items: center;");
  client.println("justify-content: center;");
  client.println("height: 200px;");
  client.println("margin-left: 5px;");
  client.println("margin-right: 5px;");
  client.println("flex: 1 1 200px;");
  client.println("}");
  client.println("@supports (display: grid) {");
  client.println(".module {");
  client.println("margin: 0;");
  client.println("}");
  client.println("</style>");
  client.println("<title>Monitor Aquaŕio</title>");
  client.println("</head>");
  client.println("<body>");
  client.println("<div class=\"grid\">");
  if (currentTemp < LIMIAR_DOWN)
  {
    client.println("<div class=\"module\" style=\" background-color: aquamarine;\">");
  }
  else if (currentTemp >= LIMIAR_DOWN && currentTemp < LIMIAR_UP)
  {
    client.println("<div class=\"module\" style=\" background-color: lightsalmon;\">");
  }
  else
  {
    client.println("<div class=\"module\" style=\" background-color: red;\">");
  }
  client.println("<img src=\"https://img.icons8.com/windows/50/000000/temperature-high.png\"/>");
  client.println("<h1>");
  client.print(currentTemp);
  client.println(" °C");
  client.println("</div>");
  if (relayIsOn)
  {
    client.println("<div class=\"module\" style=\" background-color: blue;\">");
  }
  else
  {
    client.println("<div class=\"module\" style=\" background-color: lightgray;\">");
  }
  client.println("<img src=\"https://img.icons8.com/wired/64/000000/relay.png\"/>");
  client.println("<h1>");
  if (relayIsOn)
  {
    client.println("ON");
  }
  else
  {
    client.println("OFF");
  }
  client.println("</div>");
  if (lightIsOn)
  {
    client.println("<div class=\"module\" style=\" background-color: yellow;\">");
  }
  else
  {
    client.println("<div class=\"module\" style=\" background-color: lightgray;\">");
  }
  client.println("<img src=\"https://img.icons8.com/pastel-glyph/64/000000/light--v1.png\"/>");
  client.println("<h1>");
  if (lightIsOn)
  {
    client.println("ON");
  }
  else
  {
    client.println("OFF");
  }
  client.println(" </div>");
  if (lumens >= LUMINOSITY)
  {
    client.println("<div class=\"module\" style=\" background-color: orange;\">");
    client.println("<img src=\"https://img.icons8.com/carbon-copy/100/000000/sun--v1.png\"/>");
  }
  else
  {
    client.println("<div class=\"module\" style=\" background-color: lightgray;\">");
    client.println("<img src=\"https://img.icons8.com/ios/50/000000/moon.png\"/>");
  }
  client.println("<h1>");
  client.println(lumens);
  client.println("</div>");
  client.println("<div class=\"module\" style=\" background-color: green;\">");
  client.println("<img src=\"https://img.icons8.com/dotty/50/000000/ip-address.png\"/>");
  client.println("<h3>");
  client.println(WiFi.localIP());
  client.println("</div>");

  client.println("<div class=\"module\" style=\" background-color: white;\" onclick=\"location.href=\'SOUND\'\"/>");
  if (mustPlayAlarm)
  {
    client.println("<img src=\"https://img.icons8.com/ios/50/000000/room-sound.png\"/>");
  } else
  {
    client.println("<img src=\"https://img.icons8.com/ios/50/000000/no-audio--v1.png\"/>");
  }
  client.println("</div>");
  client.println("</div>");
  client.println("</body>");
  client.println("</html>");
  delay(1);
}

void showWebPage(WiFiClient client , float currentTemp, int lumens, boolean mustPlayAlarm)
{

  if (client)
  {
    Serial.println("\n[Client connected]");
    while (client.connected())
    {
      if (client.available())
      {
        String line = client.readStringUntil('\r');
        Serial.print(line);
        if (line.length() == 1 && line[0] == '\n')
        {
          renderHtml(client, currentTemp, lumens, mustPlayAlarm);
          break;
        }
      }
    }
    while (client.available())
    {
      client.read();
    }
    client.stop();
    Serial.println("[Client disconnected]");
  }
}
