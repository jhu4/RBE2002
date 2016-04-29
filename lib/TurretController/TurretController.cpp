#include "TurretController.h"
#include "LCD.h"

TurretController::TurretController(int yaw, int pitch,LightSensor& _ls):
  isYawScanFinished(false),isPitchScanFinished(false)
  ,index(0)
  ,_yaw(yaw), _pitch(pitch)
  ,yawMinReading(2000),pitchMinReading(2000)
  ,yawAngle(0),pitchAngle(0)
  ,posPitch(129),posYaw(115)
  ,time(0),buffer(0)
  ,yawDirection(RIGHT),pitchDirection(UP)
  ,ls(_ls){

}

void TurretController::initialize() {
  ls.initialize();
  yawServo.attach(_yaw);
  pitchServo.attach(_pitch);
  yawServo.write(posYaw);
  pitchServo.write(posPitch);
}

float TurretController::getCandleDistance() {
  return ls.getDistance();
}

bool TurretController::findCandleScan() {
  if(millis()>=time){
     if(!isYawScanFinished){
       if(yawDirection==RIGHT){
         right();
       }
       else{
         left();
       }
       ls.sense();
       if(index==0){
         yawMinReading = ls.getReading();
         yawAngle = posYaw;
       }
       if(ls.getReading()<yawMinReading){
         yawMinReading = ls.getReading();
         yawAngle = posYaw;
       }
     }
     if(isYawScanFinished && !isPitchScanFinished){
       if(pitchDirection==UP){
         up();
       }
       else{
         down();
       }
       for(int i=0;i<100;i++){
         ls.sense();
         buffer+=ls.getReading();
       }
       buffer/=100;
       if(index==0){
         pitchMinReading = buffer;
         pitchAngle = posPitch;
       }
       if(buffer<pitchMinReading){
         pitchMinReading = buffer;
         pitchAngle = posPitch;
       }
     }
     if(isPitchScanFinished && isYawScanFinished){
       reset();
       return true;
     }
     index++;
     time = millis()+TICKTIME;
   }

   if(index==360 && !isYawScanFinished){
     index=0;
     isYawScanFinished=true;
     yawServo.write(yawAngle);
     time = millis()+1500;
   }
   if(index==360 && isYawScanFinished && !isPitchScanFinished){
     isPitchScanFinished=true;
     pitchServo.write(pitchAngle+5);
     time = millis()+1500;
   }
   return false;
}


bool TurretController::updownScan(){
  if(millis()>=time){
    if(pitchDirection==UP){
        up();
        if(ls.sense()){
          return true;
        }
    }
    if(pitchDirection==DOWN){
        down();
        if(ls.sense()){
          return true;
        }
    }
    time = millis()+TICKTIME;
  }
  return false;
}


bool TurretController::up() {
    if (posPitch >= 167) {
      pitchDirection=DOWN;
      return false;
    }
    posPitch+=HALFANGLE;
    pitchServo.write(posPitch);
    return true;
}

bool TurretController::down() {
    if (posPitch <= 129) {
      pitchDirection=UP;
      return false;
    }
    posPitch-=HALFANGLE;
    pitchServo.write(posPitch);
    return true;
}

bool TurretController::left() {
    if (posYaw <= 0) {
      yawDirection=RIGHT;
      return false;
    }
    posYaw-=HALFANGLE;
    yawServo.write(posYaw);
    return true;
}

bool TurretController::right() {
    if (posYaw >= 180) {
      yawDirection=LEFT;
      return false;
    }
    posYaw+=HALFANGLE;
    yawServo.write(posYaw);
    return true;
}

int TurretController::getPitchAngle() {
  return (pitchAngle-49);
}

int TurretController::getYawAngle() {
  return (180-yawAngle);
}

void TurretController::reset(){
  time=0;
  index=0;
  isYawScanFinished=false;
  isPitchScanFinished=false;
  ls.reset();
}
