#define enable 11
#define mSpeed 10
#define dirA 7
#define dirB 8

void setup() {
  // put your setup code here, to run once
  pinMode(enable, OUTPUT);
  pinMode(mSpeed, OUTPUT);
  pinMode(dirA, OUTPUT);
  pinMode(dirB, OUTPUT);

  
}

void loop() {

  digitalWrite(enable, HIGH);
  // put your main code here, to run repeatedly
  digitalWrite(dirA, HIGH);
  digitalWrite(dirB, LOW);

  analogWrite(mSpeed,50);
}
