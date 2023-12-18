#include <Servo.h>

// Define pins for servos - all are PWM
const uint8_t CLAW_SERVO_PIN = 9;
const uint8_t ARM_SERVO_PIN = 10;
const uint8_t BASE_SERVO_PIN = 11;

// Define servo angles for init/default position
const uint8_t CLAW_DEFAULT_DEG = 90;  //initialize the angle value of claw servo 1
const uint8_t ARM_DEFAULT_DEG  = 135; //initialize the angle value of arm servo 2
const uint8_t BASE_DEFAULT_DEG = 90;  //initialize the angle value of base servo 3

// Define pins used for motor
const uint8_t MTR_A_DIR = 2; // Forward or reverse - Digital
const uint8_t MTR_A_SPD = 5; // Speed - PWM
const uint8_t MTR_B_DIR = 4; // Forward or reverse - Digital
const uint8_t MTR_B_SPD = 6; // Speed - PWM

Servo clawServo;  //servo of claw
Servo armServo;   //servo of arm
Servo baseServo;  //servo of base

void setup() {
  Serial.begin(9600);

  pinMode(MTR_A_DIR, OUTPUT);
  pinMode(MTR_A_SPD, OUTPUT);
  pinMode(MTR_B_DIR, OUTPUT);
  pinMode(MTR_B_SPD, OUTPUT);
  
  clawServo.attach(CLAW_SERVO_PIN);   //claw Servo 1 is connected to D9
  armServo.attach(ARM_SERVO_PIN);   //arm Servo 2 is connected to D10
  baseServo.attach(BASE_SERVO_PIN);  //base Servo 3 is connected to D11

  clawServo.write(CLAW_DEFAULT_DEG);
  armServo.write(ARM_DEFAULT_DEG);
  baseServo.write(BASE_DEFAULT_DEG);
}
void loop() {
  clawServo.write(0);   // open the claw
  delay(200);

  clawServo.write(180); // close the claw
  delay(200);

  clawServo.write(CLAW_SERVO_DEG);  // set claw to default position
  delay(200);

  armServo.write(0);  // lower arm to lowest point
  delay(200);

  armServo.write(180); // raise arm to highest poin
  delay(200);

  armServo.write(ARM_SERVO_DEG); // return claw to default position
  delay(200);

  baseServo.write(0);  // rotate base to left
  delay(200);

  baseServo.write(180);  // rotate base to right
  delay(200);

  baseServo.write(BASE_SERVO_DEG);  // return base to default position
  delay(200);

  // Move forward for 500ms then stop
  Move_Forward(70);
  delay(500);
  Stop();

  // Move backward for 500ms then stop
  Move_Backward(70);
  delay(500);
  Stop();

  // Spin right for 500ms then stop
  Rotate_Right(70);//go forward for 2s
  delay(500);
  Stop();

  // Spin left for 500ms then stop
  Rotate_Left(70);
  delay(500);
  Stop();

  // delay 10 seconds before starting again
  delay(10000);
  
}

// Drive the robot forward at the passed in speed (0-255)
void Move_Forward(uint8_t speed)
{
  digitalWrite(MTR_A_DIR,HIGH); //D2 digital I/O port controls the direction of the motor of interface A
  analogWrite(MTR_A_SPD,speed); //D5 digital I/O port outputs PWM signal to control the speed of the motor of port A.
  digitalWrite(MTR_B_DIR,LOW);  //D4 digital I/O port controls the direction of the motor of interface B - reverse of A 
  analogWrite(MTR_B_SPD,speed); //D6 digital I/O port outputs PWM signal to control the speed of interface B motor.
}

// Drive the robot backward at the passed in speed (0-255)
void Move_Backward(uint8_t speed)
{
  digitalWrite(MTR_A_DIR,LOW);
  analogWrite(MTR_A_SPD,speed);
  digitalWrite(MTR_B_DIR,HIGH);
  analogWrite(MTR_B_SPD,speed);
}

// Spin the robot right on its axis at the passed in speed
void Rotate_Right(uint8_t speed)
{
  digitalWrite(MTR_A_DIR,HIGH);
  analogWrite(MTR_A_SPD,speed);
  digitalWrite(MTR_B_DIR,HIGH);
  analogWrite(MTR_B_SPD,speed);
}

// Spin the robot left on its axis at the passed in speed
void Rotate_Left(uint8_t speed)
{
  digitalWrite(MTR_A_DIR,LOW);
  analogWrite(MTR_A_SPD,speed);
  digitalWrite(MTR_B_DIR,LOW);
  analogWrite(MTR_B_SPD,speed);
}

// Stop all motors, set to move forward
void Stop()
{
  digitalWrite(MTR_A_DIR,LOW);
  analogWrite(MTR_A_SPD,0);
  digitalWrite(MTR_B_DIR,HIGH);
  analogWrite(MTR_B_SPD,0);
}