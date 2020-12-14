#include <Servo.h> 

Servo servo_1; 

void setup (){
  servo_1.attach(0);
}

void loop(){
  servo_1.write (45); 
  delay (1000);
  servo_1.write (90);  
  delay (1000);
  servo_1.write(135); 
delay(1000);
  servo_1.write(180); 
}
