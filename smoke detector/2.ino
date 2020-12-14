int buzzer = 8;
int smokeA0 = A0;
int sensorThres = 100;
void setup() 
{
pinMode(buzzer, OUTPUT);
pinMode(smokeA0, INPUT);
Serial.begin(9600);
}
void loop() {
  int analogSensor = analogRead(smokeA0);
Serial.print("Pin A0: ");
Serial.println(analogSensor);
  if (analogSensor-50 >sensorThres)
  {
tone(buzzer, 1000, 200);
  }
  else
  {
noTone(buzzer);
  }
delay(500);
}
