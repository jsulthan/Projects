
#include <Servo.h>
Servo servo;

void setup() {
  Serial.begin(9600);
  servo.attach(4);
  servo.write(45);
  
}
void loop() {

}
