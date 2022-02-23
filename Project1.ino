#include "Stepper.h"
#include <Servo.h>

const int STEPS = 32; 
Servo myservo;
int sdir = 1;
Stepper stepper(STEPS, 11, 9, 10, 8);

//analog variables
int s1 = A5;
int s2 = A4;

//variables 
int r1, r2, diff, diff2, correction, sum, sum2, sum3;
int pos = 90;
int thres = 10;
int d = 80;

void setup() {
  Serial.begin(9600);
  stepper.setSpeed(1000);
  myservo.attach(6);

  for (int i = 0; i<10; i++) {
    r1 += analogRead(s1);
    r2 += analogRead(s2);
  }
  correction = (r1-r2)/10;
}

void loop() {

  myservo.write(pos);

  r1 = analogRead(s1);
  r2 = analogRead(s2);
  r2 += correction;

  diff = abs(r1- r2); //positive only

  Serial.print(r1);
  Serial.print(' ');
  Serial.println(r2);

  if ((r1 > r2) && (diff > thres)) {  
    stepper.step(diff);
  }
   if ((r1 < r2) && (diff > thres)) {
    stepper.step(-diff);
  }

  sum = analogRead(s1) + analogRead(s2);
  pos += 10;
  delay(d);
  sum2 = analogRead(s1) + analogRead(s2);


    while ((sum2 > sum) && (sum2 < 350)){
      pos += 10*sdir;
      delay(d);
      sum = analogRead(s1) + analogRead(s2);
      pos += 10;
      delay(d);
      sum2 = analogRead(s1) + analogRead(s2);
    };

     while ((sum > sum2) && (sum < 350)){
      pos -= 10*sdir;
      delay(d);
      sum = analogRead(s1) + analogRead(s2);
      pos -= 10;
      delay(d);
      sum2 = analogRead(s1) + analogRead(s2);
    };

    if (pos < 70) {
      pos = 80;
    }
    if (pos > 175) {
      pos = 170;
    }
    
 }
  
