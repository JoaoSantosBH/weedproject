void ringingAlarm(int LED, boolean mustPlaySound)
{
  if (mustPlaySound) {
    digitalWrite(LED, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
    delay(500);
    digitalWrite(LED, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
    delay(500);
  }
  Serial.println("APITANDO");
}

void stopAlarm(int LED)
{
  digitalWrite(LED, LOW);
}

void soundInitialized(int LED)
{
  ringingAlarm(LED, true);
  delay(250);
  stopAlarm(LED);
  delay(100);
  ringingAlarm(LED, true);
  delay(500);
  stopAlarm(LED);
  delay(500);
  Serial.println("BIP BIP");

}
