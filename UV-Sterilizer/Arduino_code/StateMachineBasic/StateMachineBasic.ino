#include <LiquidCrystal.h>
#include <ClickEncoder.h>
#include <TimerOne.h>
#include "functions.h"

int State = 0;
int subState = 0;

#define A            31
#define B            33
#define BTN          35

#define BUZZER       37
#define POWER        8 //pin for relay control


#define LCD_RS       16 //defining LCD pins
#define LCD_RW       9
#define LCD_EN       17
#define LCD_D4       23
#define LCD_D5       25
#define LCD_D6       27
#define LCD_D7       29

#define LCD_CHARS   20 //LCD properties
#define LCD_LINES    4

LiquidCrystal lcd(LCD_RS, LCD_RW, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

ClickEncoder *encoder;
int16_t last, value;
int16_t timer;

void timerIsr() {
  encoder->service();
}


// ********************* SETUP *********************
// *************************************************

void setup() {
  Serial.begin(9600); //serial communication, values can be read from the serial monitor
  pinMode(POWER, OUTPUT); //sets the pin as output
  encoder = new ClickEncoder(A,B,BTN,4);
  pinMode(3,INPUT);
  digitalWrite(3,HIGH);
  pinMode(8, OUTPUT);

  lcd.begin(LCD_CHARS, LCD_LINES);
  lcd.clear();
  lcd.print("** Open-UV**");
  delay(2000);
  lcd.clear();

  Timer1.initialize(1000);
  Timer1.attachInterrupt(timerIsr); 
  
  last = -1;
}


// ********************* LOOP **********************
// *************************************************

void loop() {  
  states();  
}

