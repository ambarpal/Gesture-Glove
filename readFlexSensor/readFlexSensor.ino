#include <stdio.h>
void setup(){
  Serial.begin(9600);
}
int s0, s1, s2, s3, s4;
void printLog(){
  char line[100];
  int i = sprintf(line, "%d\t%d\t%d\t%d\t%d\n", s0, s1, s2, s3, s4);
  int l; for (l = 0; l <= i; l++) Serial.print(line[l]); 
}
void readSensors(){
  s0 = analogRead(A0);
  s1 = analogRead(A1);
  s2 = analogRead(A2);
  s3 = analogRead(A3);
  s4 = analogRead(A4);
}
void loop() {
  readSensors();
  printLog();
  
  delay(100);
}
