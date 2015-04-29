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
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
}
int s0, s1, s2, s3, s4, s5;          // Digital states for the flex Sensors
int sA0, sA1, sA2, sA3, sA4, sA5;     // Analog readings
int c0, c1, c2, c3, c4, c5, c6;  // Digital readings for the contact sensors
int prevLetter;                   // The previous letter that was being read
int num;                         // Number of times the current letter has been read
char letter[10000];              // binary to character mapping

void printDigitalLog();          // Prints Digital readings
void calculateFlexStates();      // Calculate states for all fingers
void readAnalogSensors();        // reads the Analog Flex Sensors
void printAnalogLog();           // Prints Analog readings
void printContactLog();          // Prints the contact sensors readings  
void printLetter();              // Dont you think this is a bit obvious?
int state(int , int );           // Calculates States from Analog Input
char currentLetter();            // Calulates the current letter
int comp(int,int,int,int,int,int,int,int,int,int,int,int,int); // Returns a boolean specifying whether the current sensor readings match the required readings

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
  s4 = analogRead(A4);
  s5 = analogRead(A5);
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
  sA5 = -1;
}

void readDigitalSensors(){
  c0 = digitalRead(2);
  c1 = digitalRead(3);
  c2 = digitalRead(4);
  c3 = digitalRead(5);
  c4 = digitalRead(6);
  c5 = digitalRead(7);
  c6 = digitalRead(8); 
}

void printContactLog(){
  char line[100];
  int i = sprintf(line, "Contact:\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", c0, c1, c2, c3, c4, c5, c6);
  int l; for (l = 0; l <= i; l++) Serial.print(line[l]);
}

// arr[0..5] are flex sensors, little finger(a0), ring(a1), middle(a2), index(a3), thumb(a4),sensor on knuckles (a5)
// arr[6..12] are contact sensors, pinky(d0), ring(d1), upper ring(d2), inner middle right side(d3), middle tip(d4), upper middle(d5), index(d6)
int comp(int arr0, int arr1, int arr2, int arr3, int arr4, int arr5, int arr6, int arr7, int arr8, int arr9, int arr10, int arr11, int arr12){
  int res = 1;
  // checking flex sensors
  if (arr0 != -1 && arr0 != s0) res = 0;  // little
  if (arr1 != -1 && arr1 != s1) res = 0;  // ring
  if (arr2 != -1 && arr2 != s2) res = 0;  // middle
  if (arr3 != -1 && arr3 != s3) res = 0;  // index
  if (arr4 != -1 && arr4 != s4) res = 0;  // thumb
  if (arr5 != -1 && arr5 != s5) res = 0;  // knuckles
  
  // checking contact sensors
  if (arr6 != -1 && arr6!= c0) res = 0;
  if (arr7 != -1 && arr7 != c1) res = 0;
  if (arr8 != -1 && arr8 != c2) res = 0;
  if (arr9 != -1 && arr9 != c3) res = 0;
  if (arr10 != -1 && arr10 != c4) res = 0;
  if (arr11 != -1 && arr11 != c5) res = 0;
  if (arr12 != -1 && arr12 != c6) res = 0;
  
  return res;  
}
char currentLetter(){
    //Bin1: 11111
    if (comp(1,1,1,1,1,0,-1,-1,-1,-1,-1,-1,-1)) return 'C';
    if (comp(1,1,1,1,1,-1,1,-1,-1,-1,-1,-1,-1)) return 'M';
    if (comp(1,1,1,1,1,-1,-1,1,-1,-1,-1,-1,-1)) return 'N';
    if (comp(1,1,1,1,1,-1,1,-1,1,-1,-1,-1,-1)) return 'S';
    if (comp(1,1,1,1,1,-1,1,-1,-1,1,-1,-1,-1)) return 'T';
    if (comp(1,1,1,1,1,-1,1,-1,-1,-1,-1,-1,-1)) return 'O';
    if (comp(1,1,1,1,1,-1,-1,-1,-1,-1,1,-1,-1)) return 'X';
    if (comp(1,1,1,1,1,-1,-1,-1,-1,-1,-1,-1,-1)) return 'E';
    
    //Bin2: 11101
    if (comp(1,1,1,0,1,-1,-1,-1,-1,-1,-1,1,-1)) return 'Z';
    if (comp(1,1,1,0,1,-1,-1,-1,-1,-1,1,-1,-1)) return 'D';
    
    //Bin3: 11001
    if (comp(1,1,0,0,-1,-1,-1,-1,-1,-1,-1,-1,-1)) return 'U'; // or V
    if (comp(1,1,0,0,1,-1,-1,-1,-1,-1,-1,-1,-1)) return 'H';
    
    //Bin4: 11000
    if (comp(1,1,0,0,0,-1,-1,-1,-1,-1,-1,-1,-1)) return 'P'; // or K
    
    //Bin5: 01110
    if (comp(0,1,1,1,0,-1,-1,-1,-1,-1,-1,-1,1)) return 'J';
    if (comp(1,1,1,1,1,-1,-1,-1,-1,-1,-1,-1,-1)) return 'Y';
    
    //Bin6: 11100
    if (comp(1,1,1,0,0,1,-1,-1,-1,-1,-1,-1,-1)) return 'L';
    if (comp(1,1,1,0,0,-1,-1,-1,-1,-1,-1,-1,-1)) return 'G'; // or Q
    
    //Bin7: Fixed
    if (comp(0,0,0,1,1,-1,-1,-1,-1,-1,-1,-1,-1)) return 'F';
    if (comp(1,1,1,1,0,-1,-1,-1,-1,-1,-1,-1,-1)) return 'A';
    if (comp(0,0,0,0,1,-1,-1,-1,-1,-1,-1,-1,-1)) return 'B';
    if (comp(1,1,0,0,1,-1,-1,-1,-1,-1,-1,-1,-1)) return 'H';
    if (comp(1,0,0,0,1,-1,-1,-1,-1,-1,-1,-1,-1)) return 'W';
    if (comp(0,1,1,1,1,-1,-1,-1,-1,-1,-1,-1,-1)) return 'I';
}
void printLetter(){
  char line[10];
  int i = sprintf(line, "%c\n", currentLetter());
  int l; for (l = 0; l <= i; l++) Serial.print(line[l]); 
}
