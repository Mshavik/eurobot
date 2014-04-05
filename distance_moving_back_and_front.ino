#include <HUBeeBMDWheel.h>

HUBeeBMDWheel leftWheel;
HUBeeBMDWheel rightWheel;

int maxLeftSpeed = 150, maxRightSpeed = 150;
int minLeftSpeed = 0, minRightSpeed = 0;

int leftQeiAPin  = 2; //external interrupt 0
int leftQeiBPin  = 4;
int rightQeiAPin = 3; //external interrupt 1
int rightQeiBPin = 7;

int leftQeiCounts = 0, rightQeiCounts = 0;

void setup()
{
  pinMode(leftQeiAPin, INPUT_PULLUP);
  pinMode(rightQeiAPin, INPUT_PULLUP);
  
  pinMode(leftQeiBPin, INPUT_PULLUP);
  pinMode(rightQeiBPin, INPUT_PULLUP);
  
  leftWheel.setupPins(8,11,9); //setup using pins 12 and 2 for direction control, and 3 for PWM speed control
  rightWheel.setupPins(12,13,10);//setup using pins 13 and 4 for direction control, and 11 for PWM speed control
  leftWheel.setDirectionMode(0); //Set the direction mode to 1
  rightWheel.setDirectionMode(1); //set the direction mode to 1
  

  attachInterrupt(0, QEI_LeftWheel, CHANGE);
  attachInterrupt(1, QEI_RightWheel, CHANGE);
  Serial.begin(9600);
}


void loop()

{
 
  driveForward(300, 150);
 delay(5000);
 
 driveBackward(300, 150);
 delay(5000);
  
                //Stop in between each command to prevent momentum causing wheel skid.
 
}



void driveForward(int mm, int power )
{
  leftQeiCounts = 0; // It is good practice to reset encoder values at the start of a function.
 
  //Calculate inches by multiplying the ratio we determined earlier with the amount of 
  //inches to go, then divide by ten as the ratio used is for an inch value.
  //Since we don't want to calculate every iteration of the loop, we will find the clicks needed 
  //before we begin the loop.
  int forwardTickGoal = mm/ 3;
  
  
 
  while(leftQeiCounts < forwardTickGoal)
  {
    Serial.print(forwardTickGoal);
  Serial.print(" ");
  Serial.println(leftQeiCounts);
   
  leftWheel.setMotorPower(power); //full speed ahead
  rightWheel.setMotorPower(power);
  }
  leftWheel.setMotorPower(minLeftSpeed); //full speed ahead
  rightWheel.setMotorPower(minRightSpeed);
}



void driveBackward(int mm, int power )
{
  leftQeiCounts = 0; // It is good practice to reset encoder values at the start of a function.
 
  //Calculate inches by multiplying the ratio we determined earlier with the amount of 
  //inches to go, then divide by ten as the ratio used is for an inch value.
  //Since we don't want to calculate every iteration of the loop, we will find the clicks needed 
  //before we begin the loop.
  int backwardTickGoal = mm/ 3;
  
  
  
 
  while(-leftQeiCounts < backwardTickGoal)
  {
    
    Serial.print(backwardTickGoal);
  Serial.print(" ");
  Serial.println(leftQeiCounts);
   
  leftWheel.setMotorPower(-power); //full speed ahead
  rightWheel.setMotorPower(-power);
  }
  leftWheel.setMotorPower(minLeftSpeed); //full speed ahead
  rightWheel.setMotorPower(minRightSpeed);
}


void QEI_LeftWheel()
{
 
  //ChA has changed state
  //Check the state of ChA
  
  if (digitalRead(leftQeiAPin) == digitalRead(leftQeiBPin))
  {
    leftQeiCounts++;
  }

  else
  {
    leftQeiCounts--;
  }  
}


void QEI_RightWheel()
{
 
  if (digitalRead(rightQeiAPin) == digitalRead(rightQeiBPin))
  {
    rightQeiCounts++;
  }

  else
  {
    rightQeiCounts--;
  }  
}

