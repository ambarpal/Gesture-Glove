#include <stdio.h>

void setup(){
  Serial.begin(9600);
}

int s0, s1, s2, s3, s4;          // Digital states
int sA0, sA1, sA2, sA3, sA4;     // Analog readings

void printDigitalLog();          // Prints Digital readings
void calculateState();           // Calculate states for all fingers
void printAnalogLog();           // Prints Analog readings
int state(int , int );           // Calculates States from Analog Input

void loop() {
  readAnalogSensors();
  calculateState();
  
  printAnalogLog();
  printDigitalLog();
  
  delay(500);
}

void printDigitalLog(){
  char line[100];
  int i = sprintf(line, "%d\t%d\t%d\t%d\t%d\n", s0, s1, s2, s3, s4);
  int l; for (l = 0; l <= i; l++) Serial.print(line[l]); 
}

void printAnalogLog(){
  char line[100];
  int i = sprintf(line, "%d\t%d\t%d\t%d\t%d\n", sA0, sA1, sA2, sA3, sA4);
  int l; for (l = 0; l <= i; l++) Serial.print(line[l]); 
}

void readAnalogSensors(){
  s0 = analogRead(A0);
  s1 = analogRead(A1);
  s2 = analogRead(A2);
  s3 = analogRead(A3);
  s4=-1;
}

int state(int reading, int threshold){
  if (reading > threshold) return 1; //1 is bent
  else return 0; //0 is ....
}

void calculateState(){
  sA0 = state(s0, 600);
  sA1 = state(s1, 610);
  sA2 = state(s2, 500);
  sA3 = state(s3, 550);
  sA4=-1;
}
