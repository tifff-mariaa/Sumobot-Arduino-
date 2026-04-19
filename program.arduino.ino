#include<Servo.h>

  Servo servoA;
	const int trigger = 8;
  const int echo = 7;
  const int near = 20;
  const int med  = 50;
  const int far  = 75;
  const int infared1 = 10;
  const int infared2 = 12;
  const int infared3 = 13;
  const int LF = 3;
  const int LB = 5;
  const int RF = 2;
  const int RB = 4;
  const int LS = 6;
  const int RS = 9;
  float distance;
  long duration;

void setup() {
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);

  pinMode(LF, OUTPUT);
  pinMode(LB, OUTPUT);
  pinMode(RF, OUTPUT);
  pinMode(RB, OUTPUT);
  pinMode(LS, OUTPUT);
  pinMode(RS, OUTPUT);
  pinMode(infared1, INPUT);
  pinMode(infared2, INPUT);
  pinMode(infared3, INPUT);

  Serial.begin(9600);
  Serial.println("Robot Started...");
  delay(5000);
}

void loop() {

  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  duration = pulseIn(echo, HIGH, 25000);
  distance = duration * 0.017;

  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance > 0 && distance <= near) {
    moveForward(255);
    return;
  }
  else if (distance <= med) {
    moveForward(100);
    return;
  }
  else if (distance <= far) {
    moveBackward(75);
    return;
  }

  int left  = digitalRead(infared1);
  int right = digitalRead(infared2);

  Serial.print("LEFT: "); 
  Serial.println(left);
  Serial.print("RIGHT: "); 
  Serial.println(right);

  if (left == 1 && right == 1) {
    moveForward(120);
  }
  else if (left == 0 && right == 0) {
    moveBackward(120);
    delay(1000);
  }
  else if (left == 0 && right == 1) {
    turnLeft();
  }
  else if (left == 1 && right == 0) {
    turnRight();
  }
}

void moveForward(int speed) {
  digitalWrite(LF, HIGH);
  digitalWrite(LB, LOW);
  digitalWrite(RF, HIGH);
  digitalWrite(RB, LOW);
  analogWrite(LS, speed);
  analogWrite(RS, speed);
}

void moveBackward(int speed) {
  digitalWrite(LF, LOW);
  digitalWrite(LB, HIGH);
  digitalWrite(RF, LOW);
  digitalWrite(RB, HIGH);
  analogWrite(LS, speed);
  analogWrite(RS, speed);
}

void turnLeft() {
  digitalWrite(LF, LOW);
  digitalWrite(LB, HIGH);
  digitalWrite(RF, HIGH);
  digitalWrite(RB, LOW);
  analogWrite(LS, 100);
  analogWrite(RS, 150);
}

void turnRight() {
  digitalWrite(LF, HIGH);
  digitalWrite(LB, LOW);
  digitalWrite(RF, LOW);
  digitalWrite(RB, HIGH);
  analogWrite(LS, 150);
  analogWrite(RS, 100);
}