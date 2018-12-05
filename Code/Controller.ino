/*
 * Function to read the controller
 * 
 *   Notes:
 *    L2 Button not functioning correctly, constantly giving fause readings.
 *    
 * Keywords
 *
 * ButtonDataByte 
 * NewButtonState  
 * ButtonPressed 
 * ButtonReleased 
 * read_gamepad  
 * config_gamepad 
 * enableRumble  
 * enablePressures 
 * Analog  
 * 
 * 
 *   Example...
 *  
 *     if(ps2x.Button(PSB_START))         //will be TRUE as long as button is pressed
 *     Serial.println("Start is being held");
 * 
 */


void processController(){
  
  if(error == 1) //skip loop if no controller found
    return; 
  

  else { //DualShock Controller


 // D Pad Buttons
    if (ps2x.Button(PSB_PAD_UP) && walkCount == 0) {      //will be TRUE as long as up button is pressed and isn't alread in walk routine.
      Serial.println("Up button pressed");
      walkCount ++;
      walkForward();
     }
    if (ps2x.Button(PSB_PAD_DOWN) && walkCount == 0) {
      Serial.println("Down button pressed");
      walkCount ++;
      walkBackwards();
     }
    if (ps2x.Button(PSB_PAD_LEFT)) {
      Serial.println("Left button pressed");
      turnLeft();
     }
    if (ps2x.Button(PSB_PAD_RIGHT)) {
      Serial.println("Right button pressed");
      turnRight();
     }

 // Shape buttons
    if (ps2x.Button(PSB_CROSS) && sitCount == 0) {
      Serial.println("X button pressed");
      sit();
     }
    if (ps2x.Button(PSB_CROSS) && sitCount == 1) {
      Serial.println("X button pressed");
    //  stand();
     }

 
     
  }
  delay(100); 

}
