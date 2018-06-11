#include<CapacitiveSensor.h>
#include<LedControl.h>
#define DIN 2
#define CS 3
#define CLK 4
#define trPin 12
#define ecPin 13
int speakerPin = 8;
char notes[] = "ccggaagffeeddc ";
unsigned long beats[] = {1,1,1,1,1,1,2,1,1,1,1,1,1,2,4}; 
int length = sizeof(notes); 
int tempo = 300;
CapacitiveSensor cs= CapacitiveSensor(A0,A1);
LedControl lc= LedControl(DIN,CLK,CS,2);
int touched=0,sensor=0,sen;
byte mood1[16]={B00000000,B00001000,B00011100,B00110010,
B01101001,B11100101,B00010011,B00001110,
  //2
  B00000000,B00000000,B01000000,B00110000,B00011000,
  B00001111,B00000000,B00000000};
byte  mood2[16]={B00000000,B00000000,
  B00000000,
  B00100000,
  B11100000,
  B11000000,
  B00000000,
  B00000000,
  //2
  B00000000,
  B00000000,
  B00000000,
  B00000100,
  B00000111,
  B00000011,
  B00000000,
  B00000000};
byte   mood3[16]={B00000011,
  B00000111,
  B00001110,
  B00011100,
  B00111000,
  B11110000,
  B11100000,
  B11000000,
  //2
  B11000000,
  B11100000,
  B01110000,
  B00111000,
  B00011100,
  B00001111,
  B00000111,
  B00000011};
  
byte mood4[16]={B10000000,
  B11000000,
  B11100000,
  B00010000,
  B00001000,
  B00000100,
  B00000010,
  B00000001,
  //2
  B00000001,
  B00000011,
  B00000111,
  B00001000,
  B00010000,
  B00100000,
  B01000000,
  B10000000};
  
 byte mood5[16]={B00000100,
  B00000010,
  B00000101,
  B00000010,
  B00011001,
  B11110000,
  B00100000,
  B11000000,
  //2
  B00100000,
  B01000000,
  B10100000,
  B01000000,
  B10011000,
  B00001111,
  B00000100,
  B00000011};
  
byte  mood6[16]={B10000000,
  B11000000,
  B00011100,
  B11111110,
  B00001111,
  B11110111,
  B11100011,
  B11000001,
  //2
  B00000001,
  B00000011,
  B00111000,
  B01111111,
  B11110000,
  B11101111,
  B11000111,
  B10000011};
void setup(){
  pinMode(speakerPin, OUTPUT);
   Serial.begin(115200);
  pinMode(trPin,OUTPUT);
  pinMode(ecPin,INPUT);
  lc.shutdown(0,false);
  lc.shutdown(1,false);
  lc.setIntensity(0,1);
  lc.setIntensity(1,1);
  lc.clearDisplay(0);
  lc.clearDisplay(1);
  cs.set_CS_AutocaL_Millis(0xFFFFFFF);
  Serial.begin(9600);
}
void loop(){
  digitalWrite(trPin,LOW);
  delayMicroseconds(5);
  digitalWrite(trPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trPin,LOW);
  long microsec = pulseIn(ecPin,HIGH);
  float cmMsec=(microsec/2)/29.1;
  long total=cs.capacitiveSensor(50);
 if(cmMsec<=12){
sensor+=1;
sen=1;
if(sensor==1){
for (int i = 0; i < length; i++) {
    if (notes[i] == ' ') {
      delay(beats[i] * tempo); 
    } else {
      playNote(speakerPin,notes[i], beats[i] * tempo);
    } 
    delay(tempo/10); 
  }
}
 }
 if(sen==1)
 {
   if(total>1000){
      touched ++;
      delay(250);
    }
    if(touched==6)
    touched=0;
      
if(touched==1){
  for(int i=0;i<8;i++){
      lc.setColumn(0,7-i,mood1[i]);
      lc.setColumn(1,7-i,mood1[i+8]); 
}
delay(1000);
}
else if(touched==2){
  for(int i=0;i<8;i++){
      lc.setColumn(0,7-i,mood2[i]);
      lc.setColumn(1,7-i,mood2[i+8]);     
    }delay(1000);
}
else if(touched==3){
  for(int i=0;i<8;i++){
      lc.setColumn(0,7-i,mood3[i]);
      lc.setColumn(1,7-i,mood3[i+8]);     
    }delay(1000);
}
else if(touched==4){
  for(int i=0;i<8;i++){
      lc.setColumn(0,7-i,mood4[i]);
      lc.setColumn(1,7-i,mood4[i+8]);     
    }delay(1000);
}
else if(touched==5){
  for(int i=0;i<8;i++){
      lc.setColumn(0,7-i,mood5[i]);
      lc.setColumn(1,7-i,mood5[i+8]);     
    }delay(1000);
}
else if(touched==0){
  for(int i=0;i<8;i++){
      lc.setColumn(0,7-i,mood6[i]);
      lc.setColumn(1,7-i,mood6[i+8]);     
    }delay(1000);
}}}
void playNote(int OutputPin, char note, unsigned long duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 261, 294, 330, 349, 392, 440, 494, 523 };
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      tone(OutputPin,tones[i], duration);
      delay(duration);
      noTone(OutputPin);
    }
  }
}

