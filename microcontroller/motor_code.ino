const int trigPin = 10;
const int echoPin = 11;
const int leftSensor = 12;
const int rightSensor = 13;
// defines variables
long duration;
int distance;
int state = 0;

// Motor A connections
int enA = 9;
int in1 = 8;
int in2 = 7;
// Motor B connections
int enB = 3;
int in3 = 5;
int in4 = 4;

int checkDistance(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  return distance;
}

void moveForward(){
  analogWrite(enA, 255);
	analogWrite(enB, 255);

  digitalWrite(in1, HIGH);
	digitalWrite(in2, LOW);
	digitalWrite(in3, HIGH);
	digitalWrite(in4, LOW);

}

void Turnright(){
  analogWrite(enA, 255);
	analogWrite(enB, 255);

  digitalWrite(in1, HIGH);
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);
  delay(500);//turn 90 degrees right, to be determined tmr
}

void Turnleft(){
  analogWrite(enA, 255);
	analogWrite(enB, 255);

  digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
	digitalWrite(in3, HIGH);
	digitalWrite(in4, LOW);
  delay(1000);//turn 180 degrees left, to be determined tmr
}

void Turnbackwards(){
  analogWrite(enA, 255);
	analogWrite(enB, 255);

    digitalWrite(in1, LOW);
	  digitalWrite(in2, LOW);
	  digitalWrite(in3, HIGH);
	  digitalWrite(in4, LOW);
    delay(500);
}

void stop(){
  analogWrite(enA, 255);
	analogWrite(enB, 255);

  digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);
  delay(1000);
}

void checkState(){
  bool leftSensorValue = digitalRead(leftSensor);
  bool rightSensorValue = digitalRead(rightSensor);
  //int frontDistance = checkDistance();
  //Serial.println(rightSensorValue);
  if (leftSensorValue){
    state = 2;
  }
  else if (rightSensorValue){
    state = 1;
  }
  else {
    state = 0;
  }

}



void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT); 
  pinMode(leftSensor, INPUT);
  pinMode(rightSensor, INPUT);
  pinMode(enA, OUTPUT);
	pinMode(enB, OUTPUT);
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	pinMode(in3, OUTPUT);
	pinMode(in4, OUTPUT);

  digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);


  Serial.begin(9600);
}


void loop() {

  moveForward();
  if(checkDistance() <= 5){
    stop();
    Turnright();
    if (checkDistance() <= 5){
      stop();
      Turnleft();
      if (checkDistance() <= 5){
        stop();
        Turnbackwards();
      }
    }
  }
  
}
