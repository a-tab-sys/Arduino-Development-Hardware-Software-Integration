
//Open  543--782--797--746
//Close 811--866-929-863

#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
//Servo servo5;

int flex1 = A1;
int flex2 = A2;
int flex3 = A3;
int flex4 = A4;
//int flex5 = A5;

void setup() {
  Serial.begin(9600);
  servo1.attach(4);
  servo2.attach(5);
  servo3.attach(3);
  servo4.attach(2);
  //servo5.attach(6);
}


void loop() {
  int flex1_pos;
  int servo1_pos;
  flex1_pos = analogRead(flex1);

  servo1_pos = map(flex1_pos, 543, 811, 180, 0);
  servo1_pos = constrain(servo1_pos, 0, 180);
  servo1.write(servo1_pos);
  /*
pinky
open-180
close-0
servo1.write(0);
*/



  int flex2_pos;
  int servo2_pos;
  flex2_pos = analogRead(flex2);
  servo2_pos = map(flex2_pos, 782, 866, 140, 0);
  servo2_pos = constrain(servo2_pos, 0, 180);
  servo2.write(servo2_pos);
  /*
ring
140-open
0-close
servo2.write(0);
*/



  int flex3_pos;
  int servo4_pos;
  flex3_pos = analogRead(flex3);
  servo4_pos = map(flex3_pos, 797, 929, 0, 180);
  servo4_pos = constrain(servo4_pos, 0, 180);
  servo4.write(servo4_pos);
  /*
index
close-180
open-0
servo4.write(0);
*/




  int flex4_pos;
  int servo3_pos;
  flex4_pos = analogRead(flex4);
  servo3_pos = map(flex4_pos, 746, 863, 180, 0);
  servo3_pos = constrain(servo3_pos, 0, 180);
  servo3.write(servo3_pos);
  /*
middle
open-180
close-0
servo3.write(0);
*/


  /*
  int flex5_pos;  
  int servo5_pos;  
  flex5_pos = analogRead(flex5); 
  servo5_pos = map(flex5_pos, 530, 755, 180, 0); 
  servo5_pos = constrain(servo5_pos, 180, 0);  
  servo5.write(servo5_pos);
  */


  Serial.print(servo1_pos);
  Serial.print("--");
  Serial.print(servo2_pos);
  Serial.print("--");
  Serial.print(servo3_pos);
  Serial.print("--");
  Serial.print(servo4_pos);
  Serial.print("--");
  /*
Serial.print(servo5_pos);
Serial.println("--");
*/

  Serial.print(flex1_pos);
  Serial.print("--");
  Serial.print(flex2_pos);
  Serial.print("--");
  Serial.print(flex3_pos);
  Serial.print("--");
  Serial.print(flex4_pos);
  Serial.println("--");
  /*
Serial.print(flex5_pos);
Serial.println("--");
*/
  delay(300);
}
