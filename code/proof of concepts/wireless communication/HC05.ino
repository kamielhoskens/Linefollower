void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
  while(!Serial);
  Serial.println("Klaar");
}

void loop()
{
  if(Serial.available())
  {
    String message = Serial.readStringUntil('\r\n');
    Serial1.println(message);
  }
  if(Serial1.available())
  {
    String message = Serial1.readStringUntil('\r\n');
    Serial.println(message);
  }
}
