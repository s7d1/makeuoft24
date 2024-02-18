#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

#define in11 4
#define in12 3
#define in13 2
#define in14 1
#define en1A 5
#define en1B 0

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

void setup() {
  Serial.begin(9600);

  pinMode(in11,OUTPUT);
  pinMode(in12,OUTPUT);
  pinMode(in13,OUTPUT);
  pinMode(in14,OUTPUT);

  pinMode(en1A,OUTPUT); // Wheel speed control
  pinMode(en1B,OUTPUT); // Wheel speed control
  mySerial.being(9600);

}

void loop() {
  //mySerial.println("Hello world");
  if (mySerial.available()) { // if data is available to read
    char receivedChar = mySerial.read(); // read it
    //Serial.write(receivedChar);


    if (receivedChar == '0') { // if '1' is received
      Serial.println("Straight");
      forward();
    } 
    else if (receivedChar == '1') { // if '0' is received
      Serial.println("Right"); // turn the LED off
    }
    else if (receivedChar == '2') 
    { // if '0' is received
      Serial.println("Left");  // turn the LED off
    }else if (receivedChar == '3') { // if '0' is received
      Serial.println("Stop");  // turn the LED off
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

/*
void right()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  analogWrite(enA, LeftRotationSpeed);
  analogWrite(enB, RightRotationSpeed);
}

void left()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  analogWrite(enA, LeftRotationSpeed);
  analogWrite(enB, RightRotationSpeed);
}

void stop()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
*/