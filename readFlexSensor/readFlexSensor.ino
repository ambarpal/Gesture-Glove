#include <stdio.h>

void setup(){
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
}

int s0, s1, s2, s3, s4;          // Digital states for the flex Sensors
int sA0, sA1, sA2, sA3, sA4;     // Analog readings
int c7, c8, c9, c10;             // Digital readings for the contact sensors

void printDigitalLog();          // Prints Digital readings
void calculateFlexStates();      // Calculate states for all fingers
void readAnalogSensors();        // reads the Analog Flex Sensors
void printAnalogLog();           // Prints Analog readings
void printContactLog();          // Prints the contact sensors readings  
int state(int , int );           // Calculates States from Analog Input

void loop() {
  readAnalogSensors();
  calculateFlexStates();
  readDigitalSensors();
  
  printAnalogLog();
  printDigitalLog();
  printContactLog();
  delay(500);
}

void printDigitalLog(){
  char line[100];
  int i = sprintf(line, "Flex:\t%d\t%d\t%d\t%d\t%d\n", s0, s1, s2, s3, s4);
  int l; for (l = 0; l <= i; l++) Serial.print(line[l]); 
}

void printAnalogLog(){
  char line[100];
  int i = sprintf(line, "Flex:\t%d\t%d\t%d\t%d\t%d\n", sA0, sA1, sA2, sA3, sA4);
  int l; for (l = 0; l <= i; l++) Serial.print(line[l]); 
}

void readAnalogSensors(){
  s0 = analogRead(A0);
  s1 = analogRead(A1);
  s2 = analogRead(A2);
  s3 = analogRead(A3);
  s4 = -1;
}

int state(int reading, int threshold){
  if (reading > threshold) return 1; //1 is bent
  else return 0; //0 is relaxed
}

void calculateFlexStates(){
  sA0 = state(s0, 600);
  sA1 = state(s1, 610);
  sA2 = state(s2, 500);
  sA3 = state(s3, 550);
  sA4 = -1;
}

void readDigitalSensors(){
  c7 = digitalRead(7);
  c8 = digitalRead(8);
  c9 = digitalRead(9);
  c10 = digitalRead(10); 
}

void printContactLog(){
  char line[100];
  int i = sprintf(line, "Contact:\t%d\t%d\t%d\t%d\t%d\n", c7, c8, c9, c10);
  int l; for (l = 0; l <= i; l++) Serial.print(line[l]);
}
