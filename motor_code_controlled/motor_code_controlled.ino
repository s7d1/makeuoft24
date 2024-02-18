#include <AFMotor.h>


#define enB1 0
#define in11 2
#define in12 3
#define in13 4
#define in14 
#define enA1 5
#define enB2 
#define in21 8
#define in22 9
#define in23 10
#define in24 7
#define enA2 11
//CHANGE
//Is the numbering messed up here?


int M1_Speed = 150; // speed of motor 1
int M2_Speed = 150; // speed of motor 2
int LeftRotationSpeed = 150;  // Left Rotation Speed
int RightRotationSpeed = 150; // Right Rotation Speed

int time = 0;//Track the time for getting around the obstacle
int start = 0;//Setting start and end mode for timer
int end = 0;

long startTime;

LiquidCrystal 1cd(7, 8, 9, 10, 11, 12); //might have to add some library

/*Needs to be changed according to condition of current arduino*/
int checkDistance(){ //detect for obstacle and wall
  digitalWrite(trigPin, LOW); //matching the pin to low, 0V
  delayMicroseconds(2); //time
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  return distance;
}

void forward(){
  digitalWrite(enA1, M1_Speed);
  digitalWrite(enB1, M1_Speed);
  digitalWrite(in11, HIGH);
  digitalWrite(in12, LOW);
  digitalWrite(in13,  HIGH);
  digitalWrite(in14, LOW);
}

void turn_left(){
  digitalWrite(in11,  HIGH);
  digitalWrite(in12, LOW);
  digitalWrite(in13, LOW);
  digitalWrite(in14,  HIGH);

}

void turn_right(){
  
  digitalWrite(in11, LOW);
  digitalWrite(in12,  HIGH);
  digitalWrite(in13, HIGH);
  digitalWrite(in14, LOW);

}

void reverse(){
  digitalWrite(in11, LOW);
  digitalWrite(in12, HIGH);
  digitalWrite(in13,  LOW);
  digitalWrite(in14, HIGH);

}

void stop()
{
  digitalWrite(in11, LOW);
  digitalWrite(in12, LOW);
  digitalWrite(in13, LOW);
  digitalWrite(in14, LOW);

}

void setup(){
  Serial.begin(9600);
  pinMode(in11,OUTPUT);
  pinMode(in12,OUTPUT);
  pinMode(in13,OUTPUT);
  pinMode(in14,OUTPUT);
  pinMode(in21,OUTPUT);
  pinMode(in22,OUTPUT);
  pinMode(in23,OUTPUT);
  pinMode(in24,OUTPUT);

  pinMode(enA1,OUTPUT); // Wheel speed control
  pinMode(enB1,OUTPUT); // Wheel speed control
  pinMode(enA2,OUTPUT); // Wheel speed control
  pinMode(enB2,OUTPUT); // Wheel speed control

  lcd.begin(16,2); //initialize the timer settings
  lcd.clear();



}


void loop(){
  lcd.setCursor(0, 1) //Setting condition for start/end of timer.
  // Will change according to condition
  //Will change "start" and "end"variables conditions here

  forward();
  if(checkDistance() <= 5){ //encoutered an obstacle
    stop();
  //If its a wall:
    turn_left();
    forward(); // TBD (cart width)
    turn_left();

  //If its an obstacle, not a wall
    turn_left();
    // start = LOW(start timer)
    //change right or ldft swith boolean variable
    startTime = millis();
    timerMode++;
    delay (400);

    //end = 1 (no longer has obstacle in certain distance (might have to adjust after experiment))
    lcd.setCursor(0, 1);
    lcd.print((millis() - startTime) / 1000.0);
    turn_right();

    forward(); //next time right wall is detected to be empty
    turn_right();
    forward(); //for measured amount of time
    //then,

    //end > 1 (Timer needs to be reset since obstacle is already passed) 
    //(need to decide if in or outside of check distance <=5)
    turn_left();
    delay(2000);
    timerMode = 0;
    lcd.clear();

  }





}

