#include <HUBeeBMDWheel.h>

HUBeeBMDWheel leftWheel;
HUBeeBMDWheel rightWheel;

int maxLeftSpeed = 150, maxRightSpeed = 150;
int minLeftSpeed = 0, minRightSpeed = 0;
int long interval = 88000;
int leftQeiAPin  = 2; //external interrupt 0
int leftQeiBPin  = 4;
int rightQeiAPin = 3; //external interrupt 1
int rightQeiBPin = 7;

int leftQeiCounts = 0, rightQeiCounts = 0;
int sensorPin = A0;
int val = analogRead(sensorPin);

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


void loop(){
unsigned long millis();
unsigned long currentMillis = millis();
if (currentMillis < interval) 
{
  
 driveForwardTillWall(420,200);
 delay(100);
 turnLeft(60,150);
 delay(100);
 driveForwardTillWall(580,200);
 delay(100);
 turnRight(155,150);
 delay(100);
 driveForwardTillWall(350,200);
 delay(100);
 turnLeft(65,150);
 delay(100);
 driveForwardTillWall(300,200);
 delay(100);
 turnLeft(65,150);
 delay(100);
 driveForwardTillWall(150,200);
 delay(100);
 turnRight(65,150);
 delay(100);
 driveForwardTillWall(300,200);
 delay(100);
 turnLeft(65,150);
 delay(100);
  driveForwardTillWall(190,200);
 delay(90000);

 
  

}
 
   leftWheel.setMotorPower(minLeftSpeed); //full speed ahead
  rightWheel.setMotorPower(minRightSpeed);             //Stop in between each command to prevent momentum causing wheel skid.
 
}

void driveForward(int mm, int power )
{
  leftQeiCounts = 0; // It is good practice to reset encoder values at the start of a function.
 
  //Calculate inches by multiplying the ratio we determined earlier with the amount of 
  //inches to go, then divide by ten as the ratio used is for an inch value.
  //Since we don't want to calculate every iteration of the loop, we will find the clicks needed 
  //before we begin the loop.
  int forwardTickGoal = mm/3 ;
  
  
 
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



void driveForwardTillWall(int mm, int power )
{
  leftQeiCounts = 0; // It is good practice to reset encoder values at the start of a function.
 
  //Calculate inches by multiplying the ratio we determined earlier with the amount of 
  //inches to go, then divide by ten as the ratio used is for an inch value.
  //Since we don't want to calculate every iteration of the loop, we will find the clicks needed 
  //before we begin the loop.
  int forwardTickGoal = mm/ 3;
  
 
  while(leftQeiCounts < forwardTickGoal)
  {
    val = analogRead(A0);
    if(val < 140){
    Serial.print(val);
  Serial.print(" ");
  Serial.println(val);
   
  leftWheel.setMotorPower(power); //full speed ahead
  rightWheel.setMotorPower(power);
    }
  else{
    leftWheel.setMotorPower(minLeftSpeed); //full speed ahead
  rightWheel.setMotorPower(minRightSpeed); 
    }
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
    
   
  leftWheel.setMotorPower(-power); //full speed ahead
  rightWheel.setMotorPower(-power);
  }
  leftWheel.setMotorPower(minLeftSpeed); //full speed ahead
  rightWheel.setMotorPower(minRightSpeed);
}

void turnRight(int degree, int power )
{
  leftQeiCounts = 0; // It is good practice to reset encoder values at the start of a function.
 rightQeiCounts = 0;
  //Calculate inches by multiplying the ratio we determined earlier with the amount of 
  //inches to go, then divide by ten as the ratio used is for an inch value.
  //Since we don't want to calculate every iteration of the loop, we will find the clicks needed 
  //before we begin the loop.
  int forwardTickGoal =  (33 * degree) / 90;
  
    
  
  
 
  while(-leftQeiCounts < forwardTickGoal)
  {
    
   
  leftWheel.setMotorPower(power); //full speed ahead
  rightWheel.setMotorPower(-power);
  }
  leftWheel.setMotorPower(minLeftSpeed); //full speed ahead
  rightWheel.setMotorPower(minRightSpeed);
}



void turnLeft(int degree, int power )
{
  leftQeiCounts = 0; // It is good practice to reset encoder values at the start of a function.
 rightQeiCounts = 0;
  //Calculate inches by multiplying the ratio we determined earlier with the amount of 
  //inches to go, then divide by ten as the ratio used is for an inch value.
  //Since we don't want to calculate every iteration of the loop, we will find the clicks needed 
  //before we begin the loop.
  int forwardTickGoal =  (33 * degree) / 90;
  
    
  
  
 
  while(rightQeiCounts < forwardTickGoal)
  {
    
   
  leftWheel.setMotorPower(-power); //full speed ahead
  rightWheel.setMotorPower(power);
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


