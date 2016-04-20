#include "Meow.h"

Meow::Meow(int p):
	num(p){

	}

void* Meow::Meow_ISR(){
	this->num++;
  return (void*) this->Meow_ISR;
}
