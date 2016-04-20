#include "Meow.h"

Meow m1(10);
void* m2 = (void*) new Meow(20);
void* m = (void*) m2;
void setup() {
  
  attachInterrupt(9,m2->Meow_ISR,CHANGE);
}

void loop() {
  // put your main code here, to run repeatedly:

}


void ISRISR(){
  m2.Meow_ISR();
}

