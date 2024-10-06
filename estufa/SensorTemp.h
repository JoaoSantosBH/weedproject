

float checkTemp(DeviceAddress ds18b20sensor, DallasTemperature sensors, int LED)
{
  sensors.requestTemperatures();
  float currentTemp = sensors.getTempC(ds18b20sensor);
  Serial.println("");
  Serial.print("Current Temp: ");
  Serial.println(currentTemp);
  return currentTemp;
}

void showAddressSensor(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16)
      Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}
void initSensor(DeviceAddress ds18b20sensor, DallasTemperature sensors)
{
  sensors.begin();
  Serial.println("Locating DS18B20 sensor...");
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" sensors found.");
  if (!sensors.getAddress(ds18b20sensor, 0))
    Serial.println("Sensors not found!");
  Serial.print("Sensor address: ");
  showAddressSensor(ds18b20sensor);
  Serial.println();
  Serial.println();
}
