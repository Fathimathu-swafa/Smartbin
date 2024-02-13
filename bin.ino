#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
const int trigPin = D5;
const int echoPin = D6;

long duration, distance;

void setup() {
  Serial.begin(115200);
  Wire.begin(D2, D1);
  lcd.begin(); // initialize the lcd
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void ultrsc() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.0343) / 2;
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(1000);
}

void lcddisp()
{
  lcd.clear();                  // clear display
  lcd.setCursor(3, 0);          // move cursor to   (3, 0)
  lcd.print("Quantity");
  distance=distance;
  if(distance<3)
    distance=0;
  double percent=distance*4.54545455;     // print message at (3, 0)
  lcd.setCursor(0, 1);          // move cursor to   (0, 1)
  lcd.print(percent); // print message at (0, 1)                  // display the above for two seconds
}

void loop(){
  ultrsc();
  lcddisp();
}
