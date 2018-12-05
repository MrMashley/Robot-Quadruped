/*
 * 
 *    Röböt
 *    4 Legged 2DOF quadruped robot
 *    V0.02 03/12/2018
 *
 *  Notes:
 *    L2 button is giving fause readings of being pressed, suspected faulty controller button.
 *    Move_Functions as yet untested.
 *    Servo angles are as yet unknown, angles for footUp, footDown or any of the walk routines are wrong!
 *
 *  To Do:
 *    Servo limits in servos[].attach(pin, lowerLimit, upperLimit); (lines 59-66) need checking and setting correctly.
 *    servoOffsets[] need setting.
 *    Set correct values for footUp, footDown and walk routines
 * 
 * 
 */


#include <VarSpeedServo.h>  // Variable speed servo library by Korman, https://forum.arduino.cc/index.php?topic=61586.0
#include <PS2X_lib.h>       // PS2X Library by Bill Porter, http://www.billporter.info/2010/06/05/playstation-2-controller-arduino-library-v1-0/


const int servoCount = 8;           // Total amount of servos
VarSpeedServo servos[servoCount];   // Creat an array for the servos
int servoOffsets[servoCount] {0, 0, 0, 0, 0, 0, 0, 0};       // holds values for servo offsets to adjust for hardware mis-alignment and servo orientation.


int sitCount = 0;     // Counter for sitting/standing routines
int walkCount = 0;    // Counter for entering walk routines

int servoSpeed = 125;     // Sets speed of servo movement (0 - 255)
const int footUp = 30;    // Foot up angle
const int footDown = 0;   // Foot Down angle  


// Vars for controller functions
int error = 0;
byte type = 0;
byte vibrate = 0;


//Pin decliration for controller
#define PS2_DAT        4    // Data
#define PS2_CMD        3    // Command
#define PS2_SEL        13   // Select / Attention
#define PS2_CLK        2    // Clock


PS2X ps2x; // create PS2 Controller Class



/*
   right now, the library does NOT support hot pluggable controllers, meaning
   you must always either restart your Arduino after you connect the controller,
   or call config_gamepad(pins) again after connecting the controller.

*/



void setup() {

    Serial.begin(57600);    // Begin serial coms

  // Load array with servos, attach to pins and set bottom and top limits (in microseconds)
  servos[0].attach(7, 1000, 2000);  // Right Front Hip
  servos[1].attach(8, 1000, 2000);  // Right Front Foot
  servos[2].attach(5, 1000, 2000);  // Left Front Hip
  servos[3].attach(6, 1000, 2000);  // Left Front Foot
  servos[4].attach(10, 1000, 2000); // Right Rear Hip
  servos[5].attach(9, 1000, 2000);  // Right Rear Foot
  servos[6].attach(12, 1000, 2000); // Left Rear Hip
  servos[7].attach(11, 1000, 2000); // Left Rear Foot



  /******* Controller Setup *******/

  delay(2000);  //delay to give wireless ps2 module some time to startup before configuring it


  //setup pins and settings: GamePad(clock, command, attention, data) check for error
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT);

  if (error == 0) {
    Serial.println("Found Controller, configured successful ");
  }
  else if (error == 1) {
    Serial.println("No controller found.");
    Serial.println("Trying to reconfigure....");
    ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT);
    delay(500);
  }
  else if (error == 2) {
    Serial.println("Controller found but not accepting commands.");
    Serial.println("Trying to reconfigure....");
    ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT);
    delay(500);
  }

  else if (error == 3) {
    Serial.println("Controller refusing to enter Pressures mode, may not support it.");
    Serial.println("Trying to reconfigure....");
    ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT);
    delay(500);
  }

  type = ps2x.readType();
  switch (type) {
    case 0:
      Serial.println("Unknown Controller type found ");
      break;
    case 1:
      Serial.println("DualShock Controller found ");
      break;
    case 2:
      Serial.println("GuitarHero Controller found ");
      break;
    case 3:
      Serial.println("Wireless Sony DualShock Controller found ");
      break;
  }

  /******* End of Controller Setup *******/


}  // END OF SET UP




void loop() {

  startUpRoutine();     // StarUp routine to move legs into centred posision
  ps2x.read_gamepad();  // Should be called at least once a second
  processController();  // Processes button presses and executes move functions

}  // END OF LOOP
