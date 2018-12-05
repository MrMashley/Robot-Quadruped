/*
 * 
 * Röböt move functions
 * 
 *   Notes:
 *    As of V0.02 none of these function have been tested.
 *    Servo angles are as yet unknown, angles stored for walking routines are wrong!
 *    Currently there is no servo offsets to take into acount misalignment in hardware.
 *    walkBackward() is a copy of walkForwards() with the 'beats' called up in reverse order, no idea if this will work properly.
 *    
 *    'false' statements may need to be changed to 'true' to give time for servos to reach their posisions before moving onto next command,
 *     without having servos to test with, the code hangs if set to 'true', belived to be because it is waiting for non-exsistant servo to reach its posision.
 *    
 *    
 *   To Do:
 *      Remove servo.write out of each function and creat an execute() routine, 
 *      in this new fuction servo offset and move speed can/will be applied to individual servos.
 * 
 * 
 */

void startUpRoutine(){
  
int startUpCount = 0;
  if (startUpCount == 0){  
     servos[1,3,5,7].write(footUp, servoSpeed, false);
     servos[0,2,4,6].write(90, servoSpeed, false);
     servos[1,3,5,7].write(footDown, servoSpeed, false);
     startUpCount = 1;
  }
}


void walkForward(){ 

  if (walkCount == 1){       // While walkCount is 1
     Serial.println("Walking Forward");
     
                       //  Right Front     Left Front       Right Rear        Left Rear
                       //  Hip,  Foot       Hip,  Foot       Hip,  Foot        Hip,  Foot             // Positions for walk routine
int  beat1[servoCount] =  {-15,  footDown,  15,   footDown,  30,  footUp,      0,    footDown};       // 1st Step 
int  beat2[servoCount] =  { 30,  footUp,    0,    footDown,  15,  footDown,   -15,   footDown};       // 2nd 
int  beat3[servoCount] =  { 15,  footDown, -15,   footDown,  0,   footDown,    30,   footUp};         // 3rd
int  beat4[servoCount] =  { 0,   footDown,  30,   footUp,   -15,  footDown ,   15,   footDown};       // 4th

  for (int i = 0; i <= 4; i ++){   // Counter for selecting which 'beat' of walk cycle to use
    switch (i){
      
     case 0:    // Firse 'beat'
      for (int x = 0; x < servoCount; x ++){  
        servos[x].write(beat1[x], servoSpeed, false);
        break;
      }
     case 1:    // Second 'beat'
      for (int x = 0; x < servoCount; x ++){
        servos[x].write(beat2[x], servoSpeed, false);
      }
     case 2:
      for (int x = 0; x < servoCount; x ++){
        servos[x].write(beat3[x], servoSpeed, false);
      }
     case 3:
     for (int x = 0; x < servoCount; x ++){
        servos[x].write(beat4[x], servoSpeed, false);
     }
    }
   }
  }
   walkCount --;   // Reset walkCount so only one walk cycle is executed
   
} // End of walkForward()





void walkBackwards(){       // Same as walk forward but with counter reversed
  while (walkCount == 1){
     Serial.println("Walking Backwards");

                       //  Right Front     Left Front       Right Rear        Left Rear
                       //  Hip,  Foot       Hip,  Foot       Hip,  Foot        Hip,  Foot             // Positions for walk routine
int  beat1[servoCount] =  {-15,  footDown,  15,   footDown,  30,  footUp,      0,    footDown};       // 1st Step 
int  beat2[servoCount] =  { 30,  footUp,    0,    footDown,  15,  footDown,   -15,   footDown};       // 2nd 
int  beat3[servoCount] =  { 15,  footDown, -15,   footDown,  0,   footDown,    30,   footUp};         // 3rd
int  beat4[servoCount] =  { 0,   footDown,  30,   footUp,   -15,  footDown ,   15,   footDown};       // 4th

  for (int i = 4; i > 0; i ++){
    switch (i){
      
     case 0:
      for (int x = 0; x < servoCount; x ++){
        servos[x].write(beat1[x], servoSpeed, false);
        break;
      }
     case 1:
      for (int x = 0; x < servoCount; x ++){
        servos[x].write(beat2[x], servoSpeed, false);
      }
     case 2:
      for (int x = 0; x < servoCount; x ++){
        servos[x].write(beat3[x], servoSpeed, false);
      }
     case 3:
     for (int x = 0; x < servoCount; x ++){
        servos[x].write(beat4[x], servoSpeed, false);
     }
    }
   }
  } 
   
  walkCount --;
  
} // End of WalkBackward()


void turnLeft(){
     Serial.println("Turning Left");
}


void turnRight(){
     Serial.println("Turning Right");
}


void sit(){
    Serial.println("Sitting Down");
    int sit[servoCount] = {90, footUp, 90, footUp, 90, footUp, 90, footUp};
      for (int i = 0; i < servoCount; i ++){
        servos[i].write(sit[90 + i], servoSpeed, false);
        sitCount = 1;
    }
}

void stand(){
    Serial.println("Standing Up");
    int stand[servoCount] = {90,90,90,90,90,90,90,90};
     for (int i = 0; i < servoCount; i ++){
        servos[i].write(stand[i], servoSpeed, false);
        sitCount = 0;
    }
}


  

  
