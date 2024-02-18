#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

// motor A
#define in11 4
#define in12 3
#define in13 2
#define in14 1
#define en1A 5
#define en1B 0
// motor B
#define in21 10
#define in22 9
#define in23 8
#define in24 7
#define en2A 11
#define en2B 6


int M1_Speed = 80; // speed of motor 1
int M2_Speed = 80; // speed of motor 2
int LeftRotationSpeed = 150;  // Left Rotation Speed
int RightRotationSpeed = 150; // Right Rotation Speed
int left_or_right = 0;  // left 0 by default, right 1 


void setup() {
  Serial.begin(9600);

  pinMode(in11,OUTPUT);
  pinMode(in12,OUTPUT);
  pinMode(in13,OUTPUT);
  pinMode(in14,OUTPUT);

  pinMode(en1A,OUTPUT); // Wheel speed control
  pinMode(en1B,OUTPUT); // Wheel speed control
  mySerial.begin(9600);

}

void loop() {
  //mySerial.println("Hello world");
  if (mySerial.available()) { // if data is available to read
    char receivedChar = mySerial.read(); // read it
    //Serial.write(receivedChar);


    if (receivedChar == '0') {
      Serial.println("Straight");
      forward();
    } 
    else if (receivedChar == '1') { 
      Serial.println("Left"); 
      left();
    }
    else if (receivedChar == '2') 
    { 
      Serial.println("Right");
      right();
    }
    else if (receivedChar == '3') { 
      Serial.println("Stop");  
      stop();
    }
    else if (receivedChar == '5') { 
      Serial.println("Move until obstacle");  
      moveUntilObstacle();
      // simpler case for now, assuming no obstacles until camera module works
      if (left_or_right == 0) {
        left_or_right = 1;
        left();
        forward();
      }
      else {
        left_or_right = 0;
        right();
        forward();
      }
    }
  }


}


void forward()
{
  digitalWrite(in11, HIGH); 
  digitalWrite(in12, LOW);
  digitalWrite(in13, LOW);
  digitalWrite(in14, HIGH);

  analogWrite(en1A, LeftRotationSpeed);
  analogWrite(en1B, RightRotationSpeed);

  digitalWrite(in21, HIGH); 
  digitalWrite(in22, LOW);
  digitalWrite(in23, LOW);
  digitalWrite(in24, HIGH);

  analogWrite(en2A, LeftRotationSpeed);
  analogWrite(en2B, RightRotationSpeed);
}

void forward(float time){
  /*
    Moves the robot forward for a certain amount of time. 
  */
  float startTime = millis();
  while(millis() - startTime < time){
    forward();
  }
}

void moveUntilObstacle(){
  /*
    Keep moving till you encounter either a boundary or obstacle. Stop if you encounter it.
  */
  while(checkDistance() > 5){
    forward();
  }
  stop();
}

void right()
{
  digitalWrite(in21, LOW);  // Use in21 and in22 for motor B
  digitalWrite(in22, HIGH);
  digitalWrite(in23, LOW);  // Use in23 and in24 for motor B
  digitalWrite(in24, HIGH);

  analogWrite(en2A, LeftRotationSpeed);  // Use en2A and en2B for motor B
  analogWrite(en2B, RightRotationSpeed);
}

void left()
{
  digitalWrite(in11, HIGH);  // Use in11 and in12 for motor A
  digitalWrite(in12, LOW);
  digitalWrite(in13, HIGH);  // Use in13 and in14 for motor A
  digitalWrite(in14, LOW);

  analogWrite(en1A, LeftRotationSpeed);  // Use en1A and en1B for motor A
  analogWrite(en1B, RightRotationSpeed);
}


void stop()
{
  digitalWrite(in11, LOW);
  digitalWrite(in12, LOW);
  digitalWrite(in13, LOW);
  digitalWrite(in14, LOW);

  digitalWrite(in21, LOW);
  digitalWrite(in22, LOW);
  digitalWrite(in23, LOW);
  digitalWrite(in24, LOW);
}
