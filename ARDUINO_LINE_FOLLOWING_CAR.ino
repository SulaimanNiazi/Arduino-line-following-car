#include <AFMotor.h>  //header file for using built in functions to control DC motors using motor shield
#include <Servo.h>    //header file to control servo motor through built in functions

//**************************************************************************************************************************************************** */

#define left A0   //left IR sensor signal pin defined at A0
#define right A1  //right IR sensor signal pin defined at A1
#define front A2  //front IR sensor signal pin defined at A2

AF_DCMotor motor1(1, MOTOR12_1KHZ); //defining motor 1
AF_DCMotor motor2(2, MOTOR12_1KHZ); //defining motor 2
AF_DCMotor motor3(3, MOTOR34_1KHZ); //defining motor 3
AF_DCMotor motor4(4, MOTOR34_1KHZ); //defining motor 4

//**************************************************************************************************************************************************** */

Servo my_servo;         // defining servo motor
void setup() {          //setup function
  pinMode(left,INPUT);  //declaring left as input
  pinMode(right,INPUT); //declaring right as input
  pinMode(front,INPUT); //declaring front as input
  my_servo.attach(9);   //defining connection to servo at pin 9
}
void loop(){
  if(digitalRead(front)==0 && (digitalRead(left)==0 || digitalRead(right)==0)){ //if front IR sensor detects object and atleast one of the IR sensors detects line
    my_servo.write(180);                                                        //servo motor closes gripper
  }
  if(digitalRead(left)==0 && digitalRead(right)==0){  // if line is detected by the left and right IR sensors
    motor1.run(FORWARD);    //motor1 set to forward
    motor1.setSpeed(255);   //motor 1 speed set to 255
    motor2.run(FORWARD);    //motor 2 set to forward
    motor2.setSpeed(255);   //motor 2 set to speed 255
    motor3.run(FORWARD);    //motor 3 set to forward
    motor3.setSpeed(255);   // motor 3 speed set to 255
    motor4.run(FORWARD);    //motor 4 set to forward
    motor4.setSpeed(255);   //motor 4 speed set to 255
  }
  else if(digitalRead(left)==0 && !digitalRead(right)==0){ //line detected by left IR sensor only
    motor1.run(FORWARD);
    motor1.setSpeed(255);
    motor2.run(FORWARD);
    motor2.setSpeed(255);
    motor3.run(FORWARD);
    motor3.setSpeed(100); //motor 3 speed set to 100 (almost half)
    motor4.run(FORWARD);
    motor4.setSpeed(100); //motor 4 speed set to 100 (almost half)
  }
  //line detected by right sensor
  else if(!digitalRead(left)==0 && digitalRead(right)==0){  //line detected by right IR sensor only
    motor1.run(FORWARD);
    motor1.setSpeed(100);
    motor2.run(FORWARD);
    motor2.setSpeed(100);
    motor3.run(FORWARD);
    motor3.setSpeed(255);
    motor4.run(FORWARD);
    motor4.setSpeed(255);
  }
  else if(!digitalRead(left)==0 && !digitalRead(right)==0){ //line detected by none of the IR sensors
    motor1.run(RELEASE);  // motor 1 set to release (to stop the motor)
    motor1.setSpeed(0);   //motor 1 speed set to 0
    motor2.run(RELEASE);
    motor2.setSpeed(0);
    motor3.run(RELEASE);
    motor3.setSpeed(0);
    motor4.run(RELEASE);
    motor4.setSpeed(0);
    my_servo.write(45);  //servo motor gripper opens
  }
}
