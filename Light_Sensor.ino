/* ========================================================================================================

// CODE BY @vignolin on GIThub

======================================================================================================== */

// --- Libraries ---
#include <virtuabotixRTC.h>                    //RTC DS1302      
#include <Wire.h>
#include <Arduino.h>
#include <TM1637Display.h>



// --- Hardware Mapping ---
#define   clk   6   // RTC
#define   dat   7   // RTC
#define   rst   8   // RTC
#define CLK 2   // 7 segment display
#define DIO 3   7 segment display
int green = 13;
int red = 12;


// --- Constants  ---
#define   segL       00 // set the time (secs, min, hours, dayWeek, dMonth, month, year)
#define   minL       14
#define   horL       16
#define   d_semL      7
#define   d_mesL     20
#define   mesL        4
#define   anoL     2024
int points = 0;


// --- Objets ---
virtuabotixRTC   myRTC(clk, dat, rst);         //RTC
TM1637Display display(CLK, DIO);


// --- Functions ---
void DS1302();
void week(int dayW);



// --- Configurations ---
void setup()  
{   
   display.setBrightness(0x0f);
  pinMode(verde, OUTPUT);
  pinMode(vermelho, OUTPUT);

  
  Serial.begin(9600);

  //Upload once for setting the time 
  //Then, comment the line below and re-upload the code 
  myRTC.setDS1302Time(segL, minL, horL, d_semL, d_mesL, mesL, anoL);
  
} 




void loop()  
{
   DS1302();
} 


// ========================================================================================================
// --- Functions 2 ---
void DS1302()
{
  myRTC.updateTime();         //RTC DS1302

  // Prints data
  Serial.println(" -> ");
  Serial.print(myRTC.dayofweek);
  Serial.print(" | ");
  Serial.print(myRTC.dayofmonth);
  Serial.print("/");
  Serial.print(myRTC.month);
  Serial.print("/");
  Serial.print(myRTC.year);
  Serial.print(" | ");
  if(myRTC.hours < 10) Serial.print("0");
  Serial.print(myRTC.hours);
  Serial.print(":");
  if(myRTC.minutes < 10) Serial.print("0");
  Serial.print(myRTC.minutes);
  Serial.print(":");
  if(myRTC.seconds < 10) Serial.print("0");
  Serial.println(myRTC.seconds);
  int analogValue = analogRead(A0);
  Serial.print(" | ");
  Serial.print(analogValue);
   Serial.print(" | ");
  Serial.print(pontos);
// nivelli della luce
 Serial.print(" | ");
  if(analogValue > 900){
    Serial.print(" - light");
  } 
  if(800 <analogValue< 900){
    Serial.print(" - AMBIENT");
  } else if(analogValue < 800){
    Serial.print("DARK");
  }
  
  display.showNumberDec(pontos, true);
  if(analogValue < 820){
    digitalWrite(green, HIGH); // accendere il LED
    pontos++;
    digitalWrite(red, LOW);
  }
  
  if(analogValue > 900){
    digitalWrite(red, HIGH); // accendere il LED
    digitalWrite(green, LOW);
  }
  delay(500);
  
} 

 
void week(int dayW)
{
  
  switch(dayW)
  {
    case 1: Serial.print("Sun"); break;
    case 2: Serial.print("Mon"); break;
    case 3: Serial.print("Tue"); break;
    case 4: Serial.print("Wed"); break;
    case 5: Serial.print("Thu"); break;
    case 6: Serial.print("Fri"); break;
    case 7: Serial.print("Sat"); break;
   
  } //end switch
  
} //end week













