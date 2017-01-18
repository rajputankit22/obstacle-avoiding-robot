

#include <AFMotor.h> //import your motor shield library
#include <NewPing.h> //import your new ping library

#define trigPinF 50 // define the pins of your sensor
#define echoPinF 51 
#define trigPinL 48// define the pins of your sensor
#define echoPinL 49
#define trigPinR 46 // define the pins of your sensor
#define echoPinR 47
#define trigPinLow 44 // define the pins of your sensor
#define echoPinLow 45
#define trigPinBck 42
#define echoPinBck 43
#define trigPinFF 40
#define echoPinFF 41
#define MaxDistance 100


AF_DCMotor motor1(4,MOTOR12_64KHZ); // set up motors.
AF_DCMotor motor2(3,MOTOR12_8KHZ);


NewPing sonarF(trigPinF,echoPinF,MaxDistance);
NewPing sonarL(trigPinL,echoPinL,MaxDistance);
NewPing sonarR(trigPinR,echoPinR,MaxDistance);
NewPing sonarLow(trigPinLow,echoPinLow,MaxDistance);
NewPing sonarB(trigPinBck,echoPinBck,MaxDistance);
NewPing sonarFF(trigPinFF,echoPinFF,MaxDistance);

//Below we are creating unsigned integer variables which we will use later on in the code. They are unsigned as they will only have postive values
unsigned int duration;
unsigned int distance;
unsigned int distanceL;
unsigned int distanceR;
unsigned int distanceB;
unsigned int distanceFF;
unsigned int FrontDistance;
unsigned int LeftDistance;
unsigned int RightDistance;
unsigned int LOWDistance;
unsigned int distanceLOW;
unsigned int FFDistance;
unsigned int ctr;
unsigned int bck;

void setup()
{
  Serial.begin(9600); // begin serial communitication  
  Serial.println("Motor test!");
  pinMode(trigPinF, OUTPUT);// set the trig pin to output (Send sound waves)
  pinMode(echoPinF, INPUT);// set the echo pin to input (recieve sound waves)
  pinMode(trigPinL, OUTPUT);// set the trig pin to output (Send sound waves)
  pinMode(echoPinL, INPUT);// set the echo pin to input (recieve sound waves)
  pinMode(trigPinR, OUTPUT);// set the trig pin to output (Send sound waves)
  pinMode(echoPinR, INPUT);// set the echo pin to input (recieve sound waves)
   pinMode(trigPinLow, OUTPUT);// set the trig pin to output (Send sound waves)
  pinMode(echoPinLow, INPUT);// set the echo pin to input (recieve sound waves)
  pinMode(trigPinBck, OUTPUT);
  pinMode(echoPinBck, INPUT);
  pinMode(trigPinFF, OUTPUT);
  pinMode(echoPinFF, INPUT);
  
  motor1.setSpeed(150); //set the speed of the motors, between 0-255
  motor2.setSpeed (180);  
}
 
void loop() 
{
 
  scanF();  //Go to the scan function
  FrontDistance = distance;  //Set the variable FrontDistance to the value of the distance returned from the scan function
  Serial.println("Front 1 distance = ");
  Serial.print(distance);
  scanLOW();
  LOWDistance = distanceLOW;
  Serial.println("Front 2 Distance = ");
  Serial.println(distanceLOW);
  scanFF();
  FFDistance = distanceFF;
  Serial.println("Front 3 Distance = ");
  Serial.println(FFDistance);
   scanL();
   scanR();
  
  if(((FrontDistance > 15) && (LOWDistance > 15) && (FFDistance > 15)) || ((FrontDistance > 15) && (LOWDistance == 0) && (FFDistance == 0)) || ((LOWDistance > 15) && (FrontDistance == 0) && (FFDistance == 0)) || ((FFDistance > 15) && (LOWDistance == 0) && (FrontDistance == 0)) || ((LOWDistance == 0) && (FrontDistance == 0) && (FFDistance == 0)) || ((FFDistance > 15) && (FrontDistance > 15) && (LOWDistance == 0)) || ((FFDistance > 15) && (FrontDistance == 0) && (LOWDistance > 15)) || ((FFDistance == 0) && (FrontDistance > 15) && (LOWDistance == 0)))
  { 
    if((distanceR > 3 || distanceR == 0) && (distanceL > 3 || distanceL == 0))
    {
	 ctr == 0;
     moveForward();
    }
    else if(distanceR <= 3 && distanceL <= 3)
    {
      moveStop();
      Rescue();
    }
   else 
    {
      moveStop();
      if(distanceR < 3 && distanceR != 0)
      {
        if(distanceL > 7)
        {
        moveLeft();
        }
        else 
        { 
          Rescue();
        } 
      }
     else if(distanceL < 3 && distanceL != 0)
      { 
        if(distanceR > 7)
        {
          moveRight();
        }
        else
        {
           Rescue();
        }
      }
    }
  }
  else     
  {
    
    moveStop();     //Go to the moveStop function
    navigate();
  }
}
 
void moveForward()                                    //This function tells the robot to go forward 
{
  Serial.println("");
  Serial.println("Moving forward");
  motor1.run(FORWARD); 
  motor2.run (FORWARD);
}
 
void moveRight()                                    //This function tells the robot to turn right
{
  Serial.println("");
  Serial.println("Moving right");
  motor1.run(FORWARD); 
  motor2.run (BACKWARD);
  delay(800);
}

void moveLeft()                                      //This function tells the robot to turn left
{
  Serial.println("");
  Serial.println("Moving left");
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  delay(800);
  
}

void moveBackward()                                  //This function tells the robot to move backward
{
  Serial.println("");
  Serial.println("Moving backward");
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
 
}
void moveStop()
{
  Serial.println("");
  Serial.println("Stopping...");
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  delay(1000);
}
void scanF()                                         //This function determines the distance of the front object
{
  Serial.println("");
  Serial.println("Scanning");
  distance = sonarF.ping_cm();
 
}
void scanL()                                         //This function determines the distance of the left object
{
  Serial.println("");
  Serial.println("Scanning");
  distanceL = sonarL.ping_cm();
  
}
void scanR()                                         //This function determines the distance of the right object
{
  Serial.println("");
  Serial.println("Scanning");
  distanceR = sonarR.ping_cm();
  
}
void scanLOW()
{
  Serial.println("");
  Serial.println("Scanning");
  distanceLOW = sonarLow.ping_cm();
  
}
void scanB()
{
  distanceB = sonarB.ping_cm();
  
} 
void scanFF()
{
  Serial.println("");
  Serial.println("Scanning");
  distanceFF = sonarFF.ping_cm();
} 

void navigate()
{
    ctr++;
    Serial.println("There's an obstacle!");
    scanL();    //Go to the scan function
    LeftDistance = distanceL;                          //Set the variable LeftDistance to the distance on the left
    Serial.println("Left distance = ");
    Serial.print(LeftDistance);
    scanR();                                           //Go to the scan  function
    RightDistance = distanceR;                         //Set the variable RightDistance to the distance on the right
    Serial.println("Right distance = ");
    Serial.print(RightDistance);
	

    
    if(ctr < 4)
	{
    if ((RightDistance < 7 && LeftDistance < 7) && (RightDistance != 0 && LeftDistance !=0))
    {
      scanB();
      if(distanceB > 5)
      {
       moveBackward();
       delay(500); 
       Rescue();
      }
     else 
     {
        moveStop();
        Rescue(); 
     }
    }
    
    else if((RightDistance == 0 && LeftDistance == 0))
    {
       moveRight();
       delay(100);
    } 
    else if(RightDistance == 0 && LeftDistance > 0)
    {
      moveRight();
      delay(100);
    }
    else if(RightDistance > 0 && LeftDistance == 0) 
    {
     moveLeft();
     delay(100)   ;
    }
    else if((RightDistance > 7) && (LeftDistance > 7))
      {    
        if((RightDistance <= LeftDistance))
          {
           moveLeft();
           delay(100);
          }
        else if((LeftDistance <  RightDistance))
           {
            moveRight();
            delay(100);
           }
      }
    else if((RightDistance > 7) && (LeftDistance < 7))
     {
        moveRight();
        delay(100);
     }
    else if((RightDistance <7) && (LeftDistance > 7))
   {
     moveLeft();
    delay(100);
   }
   }
   else
   {
     changeSTR();
   } 
} 
   
void Rescue()
{
  ctr++;
  scanL();
  scanR();
  if(distanceR <= 7 && distanceL <= 7 && distanceR != 0 && distanceL!= 0)
  {  
     scanB();
     if(distanceB > 5)
     {
       moveBackward();
       delay(100);
       Rescue();
     }
    else
     {
      moveStop();
      Rescue();
     } 
  }
  else if(distanceL == 0 || distanceR == 0)
  {
    if(distanceR >= distanceL)
    {
       moveLeft();
    }
   else 
    {
      moveRight();
    } 
  } 
    
  else if(distanceR > 7 || distanceL > 7 )
  {
    if(distanceR >= distanceL)
    {
       moveRight();
    }
   else 
    {
      moveLeft();
    } 
  
  }
} 
void changeSTR()
{
 bck = 0;
 scanL();
 scanR(); 
 scanB();
 if(distanceB > 7)
  {
   do
   {
    moveBackward();
    delay(100);
	scanB(); bck++;
   }while(distanceB > 7 && bck < 3);
   ctr = 0;
   navigate();
  }
else if(distanceL > 5 || distanceL== 0)
 {
   ctr = 0;
   if((distanceR > distanceL && distanceL != 0) || (distanceR == 0))
   {
    moveRight();
   }
   else
   {
   moveLeft();
   }
 }
else if (distanceR > 5 || distanceR == 0)
{
 ctr = 0;
 if((distanceL > distanceR  && distanceR != 0) || (distanceL == 0))
 {
  moveLeft();
 }
 else
 {
  moveRight();
  }
}
else
{
 changeSTR();
}
} 

 
   
   
    
 







