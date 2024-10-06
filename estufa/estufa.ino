//Monitor de temperatura para aquários
//joaomarcelo.ms@gmail.com

#include <U8g2lib.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFiMulti.h>
#include <ArduinoJson.h>
#include <WiFiClientSecure.h>
#include <ESP8266WebServer.h>
#include <WiFiClientSecureBearSSL.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include "Constants.h"
#include "Ota.h"
#include "Oled.h"
#include "Sound.h"
#include "Relay.h"
#include "SensorTemp.h"
#include "Server.h"
#include "Network.h"

#define ONE_WIRE_BUS 0
#define LED 2


OneWire oneWire(ONE_WIRE_BUS);
DeviceAddress ds18b20sensor;
ESP8266WiFiMulti WiFiMulti;
DallasTemperature sensors(&oneWire);
WiFiServer server(80);

float currentTemp = 0.0;
float lumens;
int waitingCounter = 0;
boolean mustPlayAlarm = true;

void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(RELAY_BUS_A, OUTPUT);
  pinMode(RELAY_BUS_B, OUTPUT);
  Serial.begin(115200);
  server.begin();
  initOled();
  initWifi();
  initSensor(ds18b20sensor, sensors);
  setupOTA();
  soundInitialized(LED);
  powerOffThermostatRelay();
  powerOffLightRelay();
}

void loop()
{

  ArduinoOTA.handle();
  drawMyIp();
  currentTemp = checkTemp( ds18b20sensor, sensors, LED);
  lumens = shouldTurnOnTheLight();
  shouldTurnOnThermostat(currentTemp);
  relayIsOn = getRelayStatus();
  lightIsOn = getLightStatus();

  WiFiClient client = server.available();
  String request = client.readStringUntil('\r');
  if (request.indexOf("/SOUND") != -1)
  {
    enableDisableSound();
  }

  showWebPage(client, currentTemp, lumens, mustPlayAlarm);
  drawTemperature(currentTemp);
  drawRelayStatus(relayIsOn);
  drawLightStatus(lightIsOn);
  drawLuminosity(lumens);
  runRoutine();
  delay(3000);
}

void enableDisableSound() {
  mustPlayAlarm = !mustPlayAlarm;
  Serial.println("MUS T PLAY ");
  Serial.println(mustPlayAlarm);
}

void runRoutine() {
  if (currentTemp < MINIMUN_TEMP || currentTemp > MAXIMUM_TEMP)
  {
    if (currentTemp != 85) {
      ringingAlarm(LED, mustPlayAlarm);
      handleNotify();
    }
  }
  else
  {
    stopAlarm(LED);
  }
}

void handleNotify()
{
  if (waitingCounter == 0)
  {
    sendMessageByInternet(WiFiMulti, currentTemp);
    waitingCounter += 1;
  }
  else if (waitingCounter < WAIT_N_TIMES)
  {
    waitingCounter += 1;
  }
  else
  {
    waitingCounter = 0;
  }
  drawTimer(waitingCounter);
}
