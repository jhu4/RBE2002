#include "Fan.h"

Fan::Fan(int p):pin(p){

}

void Fan::initialize(){
  pinMode(pin,OUTPUT);
}

void Fan::on(){
  digitalWrite(pin,HIGH);
}

void Fan::off(){
  digitalWrite(pin,LOW);
}
