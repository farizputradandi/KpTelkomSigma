#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
 
//sad = a4
//scl = a5
LiquidCrystal_I2C lcd(0x27 , 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 
Servo servo;
int angle = 180;
//coklat ke gnd
//merah ke 5v
//oren ke 8

int in0 = 1;
int in1 = 2;
int in2 = 3;
int in3 = 4;

int tanah_pin = A0;
int tanah_value ;
#include "DHT.h"

const int pTrig = 6;
const int pEcho = 5;

#define DHTPIN 7     // what digital pin the DHT22 is conected to
#define fan 5
#define DHTTYPE DHT22   // there are multiple kinds of DHT sensors

DHT dht(DHTPIN, DHTTYPE);
 
//di relay nya,, kalo pin obengnya ngadep kita,, yg dipake tu yg 2 dari kiri


void setup() {
   Serial.begin(9600);
 Serial.println("CLEARDATA");//clear excel sheet
 Serial.println("LABEL,current time,data1");//label for ms-excel
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
lcd.begin(20, 4); 

  servo.attach(8);
  servo.write(angle);

  
 
pinMode(fan, OUTPUT); 
  pinMode(in0, OUTPUT);
  digitalWrite(in0, HIGH);
  pinMode(in1, OUTPUT);
  digitalWrite(in1, HIGH);
  pinMode(in2, OUTPUT);
  digitalWrite(in2, HIGH);
  pinMode(in3, OUTPUT);
  digitalWrite(in3, HIGH);

  
 pinMode(pTrig,OUTPUT);
 pinMode(pEcho,INPUT);
}

long durasi = 0;
float hasil;
void loop() {
//Serial.print("DATA,TIME,");
////------------------
 
// //-------------------------------------------------
  tanah_value= analogRead(tanah_pin);
//   Serial.println(tanah_value);
   
   if(tanah_value>1000){ 
          digitalWrite(in1, 0); 
          delay(5000);
         digitalWrite(in1, 1); 
          delay(500);
     } 
//
// //-------------------------------------------------
//// lampu taman  
  int sensorValue0 = analogRead(A1); 
//       Serial.println(sensorValue0);
   if(sensorValue0<200){
//       Serial.println(sensorValue0);
//       Serial.println("lampu taman nyala"); 
      lcd.setCursor(0, 3);
      lcd.print("lamput taman nyala");
       digitalWrite(in2, 0);
        delay(500); 
 
    }else{
      
        digitalWrite(in2, 1);
        delay(500);
      lcd.setCursor(0, 3);
//       Serial.println("lampu taman mati"); 
      lcd.print("lamput taman mati");
      } 
 //-------------------------------------------------
  //sensor jarak
  
  
  digitalWrite(pTrig,HIGH);
  delayMicroseconds(10);
  digitalWrite(pTrig,LOW);

  durasi = pulseIn(pEcho,HIGH); 
  hasil = (durasi * 0.034)/2; 
// Serial.println("jarak"); 
// Serial.println(hasil);
  delay(1000);
  
   if(hasil<10){
               for(angle = 180; angle >= 90; angle--)  
          {                                  
            servo.write(angle);               
            delay(2);                   
          } 
          // now scan back from 180 to 0 degrees
          
      lcd.setCursor(0, 3);
      lcd.print("palang parkir buka");
//       Serial.println("palang parkir buka"); 
 
          delay(1000);
          for(angle = 90; angle < 180; angle++)    
          {                                
            servo.write(angle);           
            delay(2);       
          } 
      lcd.setCursor(0, 3);
      lcd.print("palang parkir tutup");
//       Serial.println("palang parkir tutup");
 
    }
  

// 
//-------------------------------------------------
//suhu
 

      float h = dht.readHumidity();
     float t = dht.readTemperature();
     float f = dht.readTemperature(true);

     float hif = dht.computeHeatIndex(f, h);
     float hic = dht.computeHeatIndex(t, h, false);


 
lcd.setCursor(0, 0);
lcd.print("humidity = ");
lcd.print(h); 
lcd.setCursor(0, 1);
lcd.print("temp = ");
lcd.print(t); 
lcd.print("*C"); 

       Serial.println("humidity");
       Serial.println(t);
       Serial.println("temp");
       Serial.println(t);
       Serial.println("*C");
//-------------------------------------------------
//co2

  int sensorValueco2 = analogRead(A2); 

lcd.setCursor(0, 2);
lcd.print("c02 = ");
lcd.print(sensorValueco2 * 6);
if(sensorValueco2*6>1000){

//       Serial.println(sensorValueco2*4);
//       Serial.println("ppm");    
lcd.setCursor(11, 2);
lcd.print("danger!");
  } 
 //--------------------------
 
}

int getState(int aValue)
{
  return (int(aValue/128));
}
