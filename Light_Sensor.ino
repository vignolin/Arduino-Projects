/* ========================================================================================================



======================================================================================================== */


// ========================================================================================================
// --- Bibliotecas Auxiliares ---
#include <virtuabotixRTC.h>                    //biblioteca para o RTC DS1302      
#include <Wire.h>
#include <Arduino.h>
#include <TM1637Display.h>


// ========================================================================================================
// --- Mapeamento de Hardware ---
#define   clk   6
#define   dat   7
#define   rst   8
#define CLK 2
#define DIO 3
int verde = 13;
int vermelho = 12;

// ========================================================================================================
// --- Constantes Auxiliares ---
#define   segL       00
#define   minL       14
#define   horL       16
#define   d_semL      7
#define   d_mesL     20
#define   mesL        4
#define   anoL     2024

int pontos = 0;

// ========================================================================================================
// --- Declaração de Objetos ---
virtuabotixRTC   myRTC(clk, dat, rst);         //declara objeto para o RTC

TM1637Display display(CLK, DIO);
// ========================================================================================================
// --- Protótipo das Funções ---
void DS1302();
void week(int dayW);


// ========================================================================================================
// --- Configurações Iniciais ---
void setup()  
{   
   display.setBrightness(0x0f);
  pinMode(verde, OUTPUT);
  pinMode(vermelho, OUTPUT);

  //lcd.noBacklight(); // DESLIGA A ILUMINAÇÃO DO DISPLAY
  Serial.begin(9600);

  //Faça upload do código para o Arduino uma vez para carregar os
  //dados iniciai no RTC.
  //Após, comente a linha abaixo e faça upload novamente. 
  myRTC.setDS1302Time(segL, minL, horL, d_semL, d_mesL, mesL, anoL);
  
} //end setup


// ========================================================================================================
// --- Loop Infinito ---
void loop()  
{


   DS1302();
  
} //end loop


// ========================================================================================================
// --- Desenvolvimento das Funções ---
void DS1302()
{
  myRTC.updateTime();         //faz leitura do DS1302

  // Imprime informações
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
    digitalWrite(verde, HIGH); // accendere il LED
    pontos++;
    digitalWrite(vermelho, LOW);
  }
  
  if(analogValue > 900){
    digitalWrite(vermelho, HIGH); // accendere il LED
    digitalWrite(verde, LOW);
  }
  delay(500);
  
} //end DS1302

 
void week(int dayW)
{
  
  switch(dayW)
  {
    case 1: Serial.print("Dom"); break;
    case 2: Serial.print("Seg"); break;
    case 3: Serial.print("Ter"); break;
    case 4: Serial.print("Qua"); break;
    case 5: Serial.print("Qui"); break;
    case 6: Serial.print("Sex"); break;
    case 7: Serial.print("Sab"); break;
   
  } //end switch
  
} //end week













