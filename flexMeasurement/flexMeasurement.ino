void setup() {
   Serial.begin(9600);
   pinMode(6, OUTPUT);
}

int c = 0;
void loop() {
  delay(500);
  c++;
  if ( c % 7 == 0) analogWrite(6, 20);
  else analogWrite(6, 1);
  int x = analogRead(0);
  Serial.println(x);
}
