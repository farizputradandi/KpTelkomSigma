#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//sad = a4
//scl = a5
//LiquidCrystal_I2C lcd(0x27 , 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 
LiquidCrystal_I2C lcd(0x3F , 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 




#define NOTE_C5 523//DO
const int pinSpeaker = 12;

//flame
const int flamePin = 11;
int Flame = HIGH;



const int r[4] = {22,25,28};
const int y[4] = {23,26,29};
const int g[4] = {24,27,30};

//light detector  
byte L1[]={A0,A1,A2};
byte L2[]={A5,A6,A7};
byte L3[]={A8,A9,A10};

int L1Temp[3];
int L2Temp[3];
int L3Temp[3];

int time1=500;
//di relay nya,, kalo pin obengnya ngadep kita,, yg dipake tu yg 2 dari kiri
void setup() {
  pinMode(flamePin, INPUT);
  pinMode(pinSpeaker,OUTPUT);
lcd.begin(16, 2); 
  Serial.begin(9600);
 for (int i = 0; i < 3; i++) {
    pinMode(r[i], OUTPUT);
      digitalWrite(r[i], HIGH);  
    pinMode(y[i], OUTPUT);
      digitalWrite(y[i], HIGH);
    pinMode(g[i], OUTPUT);
      digitalWrite(g[i], HIGH);

    L1Temp[i]=analogRead(L1[i]);
    L2Temp[i]=analogRead(L2[i]);
    L3Temp[i]=analogRead(L3[i]);
    
  } 
}
void loop() { 
        turnOn(0, 1, 2);         
        turnOn(1, 0, 2);         
        turnOn(2, 0, 1);         
        lcd.clear();
   
}

void checkTrafic(int i,int j, int k){  
      //flame
       Flame = digitalRead(flamePin);
        if (Flame== LOW)
        { 
                lcd.setCursor(0, 1);
                lcd.print("fire!! ");
          tone(pinSpeaker,NOTE_C5,500);
        } 
            
      
      
      //for light
      for(int q=0;q<3;q++){
        
          L1Temp[q]=analogRead(L1[q]);
          L2Temp[q]=analogRead(L2[q]);
          L3Temp[q]=analogRead(L3[q]); 
        if(q!=i){
            if(L1Temp[q]<50){
                
                tone(pinSpeaker,NOTE_C5,500); 
                Serial.println("pelanggaran pada simpang " );
                Serial.println(q+1);
                lcd.setCursor(0, 0);
                lcd.print("pelanggaran pada ");
                lcd.print(q+1);
                break;
              }
            if(L2Temp[q]<50){
                tone(pinSpeaker,NOTE_C5,500); 
                Serial.println("pelanggaran pada simpang " );
                Serial.println(q+4);
                lcd.setCursor(0, 0);
                lcd.print("pelanggaran pada ");
                lcd.print(q+4);
                
                break;
              } 
            if(L3Temp[q]<50){
                tone(pinSpeaker,NOTE_C5,500); 
                Serial.println("pelanggaran pada simpang " );
                Serial.println(q+7);
                lcd.setCursor(0, 0);
                lcd.print("pelanggaran pada ");
                lcd.print(q+7);
                
                break;
              }  
          }
        }
         
  }
  
void turnOn(int i, int j, int k){
   for (int a = 0; a < 3 ; a++) {
    if (a != i) {
      digitalWrite(r[j], 0);
      digitalWrite(r[k], 0); 
    }
  }  
  digitalWrite(r[i], 1); // 0 itu nyala // 1 mati
  digitalWrite(y[i], 0); // 0 itu nyala // 1 mati
  for(int p=0;p<time1;p++){delay(1);checkTrafic(i,j,k);}
//delay(1000);
  
  digitalWrite(y[i], 1); // 0 itu nyala // 1 mati
  digitalWrite(g[i], 0); // 0 itu nyala // 1 mati
  for(int p=0;p<time1;p++){delay(1);checkTrafic(i,j,k);}  
//delay(1000);

  digitalWrite(g[i], 1); // 0 itu nyala // 1 mati
  digitalWrite(y[i], 0); // 0 itu nyala // 1 mati
  for(int p=0;p<time1;p++){delay(1);checkTrafic(i,j,k);}
//delay(1000);
  digitalWrite(y[i], 1); // 0 itu nyala // 1 mati
  digitalWrite(r[i], 0); // 0 itu nyala // 1 mati
  for(int p=0;p<time1;p++){delay(1);checkTrafic(i,j,k);}
//  delay(1000);
  }
