U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ 5, /* data=*/ 4);   // ESP32 Thing, HW I2C with pin remapping

void drawTimer(int waitingCounter) {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_helvR14_tr);
  u8g2.setCursor(0, 24);
  u8g2.print(waitingCounter);
  u8g2.print(" Tx..");
  u8g2.sendBuffer();
  delay(1000);
}

void drawTemperature(float currentTemp)
{
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_helvR14_tr);
  u8g2.setCursor(0, 24);
  u8g2.print(currentTemp);
  u8g2.print(" °C");
  u8g2.sendBuffer();
  delay(1000);
}

void initOled()
{
  u8g2.begin();
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_helvR14_tr);
  u8g2.setCursor(0, 24);
  u8g2.print(MY_NAME);
  u8g2.sendBuffer();
  delay(100);
}

void drawMyIp()
{
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_helvR14_tr);
  u8g2.setCursor(0, 24);
  u8g2.print(WiFi.localIP());
  u8g2.sendBuffer();
  delay(100);
}

void drawRelayStatus(boolean isOn)
{
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_helvR14_tr);
  u8g2.setCursor(0, 24);
  if (isOn)
  {
    u8g2.print("Therm is ON");
  }
  else
  {
    u8g2.print("Therm is OFF");
  }
  u8g2.sendBuffer();
  delay(1000);
}

void drawLuminosity(float lumens)
{
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_helvR14_tr);
  u8g2.setCursor(0, 24);
  u8g2.print("Lumen  ");
  u8g2.print(lumens);
  u8g2.sendBuffer();
  delay(1000);
}

void drawLightStatus(boolean lightIsOn)
{
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_helvR14_tr);
  u8g2.setCursor(0, 24);
  if (lightIsOn)
  {
    u8g2.print("Light ON");
  }
  else
  {
    u8g2.print("Light OFF");
  }
  u8g2.sendBuffer();
  delay(1000);
}
