#include "LCD.h"

LCD::LCD(int p1, int p2, int p3, int p4, int p5, int p6):lcd(p1, p2, p3, p4, p5, p6){
  
}

void LCD::initialize(){
  lcd.begin(16,2);
}
void LCD::display(float x, float y){
  lcd.setCursor(0,0);
  lcd.print("X:");
  lcd.print(x);
  lcd.print(" Y:");
  lcd.print(y);

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

