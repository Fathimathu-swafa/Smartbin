#include <Servo.h>

#define echoPin 5
#define trigPin 4

int mr1 = 8;   // motor right 1
int mr2 = 9;   // motor right 2
int ml1 = 10;  // motor left 1
int ml2 = 11;  // motor left 2

int enr = 6;
int enl = 7;
int vspeed = 150;
int tspeed = 255;
int tdelay = 20;

Servo myservo;  // create servo object to control a servo
int servoPin = 3;  // servo signal pin

void forward() {
  digitalWrite(mr1, HIGH);
  digitalWrite(ml2, LOW);
  digitalWrite(ml1, HIGH);
  digitalWrite(mr2, LOW);
  analogWrite(enr, vspeed);
  analogWrite(enl, vspeed);
}

void backward() {
  digitalWrite(mr1, LOW);
  digitalWrite(mr2, HIGH);
  digitalWrite(ml1, LOW);
  digitalWrite(ml2, HIGH);
  analogWrite(enr, vspeed);
  analogWrite(enl, vspeed);
}

void right() {
  digitalWrite(mr1, LOW);
  digitalWrite(mr2, HIGH);
  digitalWrite(ml1, HIGH);
  digitalWrite(ml2, LOW);
  analogWrite(enr, tspeed);
  analogWrite(enl, tspeed);
  delay(tdelay);
}

void left() {
  digitalWrite(mr1, HIGH);
  digitalWrite(mr2, LOW);
  digitalWrite(ml1, LOW);
  digitalWrite(ml2, HIGH);
  analogWrite(enr, tspeed);
  analogWrite(enl, tspeed);
  delay(tdelay);
}

void stop() {
  analogWrite(enr, 0);
  analogWrite(enl, 0);
}

void setup() {
  Serial.begin(9600);
  pinMode(mr1, OUTPUT);
  pinMode(mr2, OUTPUT);
  pinMode(ml1, OUTPUT);
  pinMode(ml2, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myservo.attach(servoPin);  // attaches the servo on pin 3 to the servo object
  delay(5000);
}

float getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  return pulseIn(echoPin, HIGH) * 0.034 / 2;
}

void loop() {
  float distance = getDistance();

  if (distance < 20) {
    // Stop if an obstacle is detected within 20 cm
    stop();

    // Determine whether to turn left or right
    int turnDirection = random(2);  // 0 for left, 1 for right

    if (turnDirection == 0) {
      left();
    } else {
      right();
    }

    delay(2000);  // Adjust the delay based on your needs for turning
    stop();
  } else {
    // Move forward if no obstacle is detected
    forward();
  }

  delay(100);  // Adjust the delay based on your needs
}
