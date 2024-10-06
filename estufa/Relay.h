#define RELAY_BUS_A 14
#define RELAY_BUS_B 12
boolean relayIsOn = false;
boolean lightIsOn = false;
float lumino;
void powerOnThermostatRelay()
{
  digitalWrite(RELAY_BUS_A, HIGH);
  relayIsOn = true;
}

void powerOffThermostatRelay()
{
  digitalWrite(RELAY_BUS_A, LOW);
  relayIsOn = false;
}

void powerOnLightRelay()

{
  digitalWrite(RELAY_BUS_B, HIGH);
  lightIsOn = true;
}

void powerOffLightRelay()
{
  digitalWrite(RELAY_BUS_B, LOW);
  lightIsOn = false;
}

float shouldTurnOnTheLight()
{
  int sensorLdrValue = analogRead(A0);
  lumino = sensorLdrValue * (5.0 / 1023.0);
  if (lumino >= LUMINOSITY)
  {
    powerOnLightRelay();
  }
  else
  {
    powerOffLightRelay();
  }
  return lumino;
}

void shouldTurnOnThermostat(float currentTemp)
{
  if (currentTemp <= LIMIAR_DOWN)
  {
    powerOnThermostatRelay();
  }
  else
  {
    powerOffThermostatRelay();
  }
}

boolean getRelayStatus() {
  return relayIsOn;
}

boolean getLightStatus() {
  return lightIsOn;
}
