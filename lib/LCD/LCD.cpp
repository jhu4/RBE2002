#include "LCD.h"


LCD::LCD(int p1, int p2, int p3, int p4, int p5, int p6):
lcd(p1, p2, p3, p4, p5, p6),
lastTime(0){
  lcd.begin(16,2);
}

bool LCD::delayWrite(){
  unsigned long currTime = millis();
  if ((currTime-lastTime) < 100){
    return true;
  } else {
    lastTime = currTime;
    return false;
  }
}

void LCD::initialize(){
  lcd.begin(16,2);
}
void LCD::display(double x, double y){
  if (!delayWrite()){
    lcd.setCursor(0,0);
    lcd.print("X:");
    lcd.print(x);
    lcd.setCursor(0,1);
    lcd.print("Y:");
    lcd.print(y);
  }
}
void LCD::display(bool x, bool y){
  if (!delayWrite()){
    lcd.setCursor(0,0);
    lcd.print("X:");
    lcd.print(x);
    lcd.setCursor(0,1);
    lcd.print("Y:");
    lcd.print(y);
  }
}

void LCD::display(float z){
  lcd.setCursor(0,1);
  lcd.print("Z:");
  lcd.print(z);
}

void LCD::display(float x, float y, float z){
  lcd.setCursor(0,0);
  lcd.print("X:");
  lcd.print(x);
  lcd.print(" Y:");
  lcd.print(y);
  lcd.setCursor(0,1);
  lcd.print("Z:");
  lcd.print(z);
}

void LCD::display(String message){
  lcd.setCursor(0,0);
  lcd.print(message);
}

void LCD::display(long ticks){
  lcd.setCursor(0,0);
  lcd.print("TICKS: ");
  lcd.print(ticks);
}

void LCD::display(unsigned long ticks){
  lcd.setCursor(0,0);
  lcd.print("TICKS: ");
  lcd.print(ticks);
}

void LCD::display(double x){
  if (!delayWrite()){
    lcd.setCursor(0,0);
    lcd.print("MM: ");
    lcd.print(x);
  }
}
