// note: for my beam to be horizontal, Servo Motor angle should be 102 degrees.
#include<Servo.h>
#include<PID_v1.h>

const int trigPin = 9;    // Trig pin of the ultrasonic sensor (Yellow)
const int echoPin = 10;   // Echo pin of the ultrasonic sensor (Orange)
const int servoPin = 11;  // Servo Pin

float Kp = 2.05;                                                   //Initial Proportional Gain 2.05
float Ki = 0;                                                      //Initial Integral Gain
float Kd = 0.85;                                                    //Intitial Derivative Gain 0.85
double Setpoint, Input, Output, ServoOutput;                                       

PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);           //Initialize PID object, which is in the class PID.                                                                   
Servo myServo;                                                       //Initialize Servo.

void setup() {

  Serial.begin(9600);                                                //Begin Serial 
  myServo.attach(servoPin);                                          //Attach Servo
  resetServo();                                               // Reset servo to initial angle

  Input = readPosition();                                            //Calls function readPosition() and sets the balls
                                                                     //  position as the input to the PID algorithm

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);                                       
  myPID.SetMode(AUTOMATIC);                                          //Set PID object myPID to AUTOMATIC 

  myPID.SetOutputLimits(-60,80);                             // Set output limits to match servo range
}

void loop(){
  delay(100);
  Setpoint = 15;
  Input = readPosition();                                            
 
  myPID.Compute();                                                   //computes Output in range of -80 to 80 degrees
  
  ServoOutput=102-Output;                                            // 102 degrees is my horizontal 
  myServo.write(ServoOutput);                                        //Writes value of Output to servo
  Serial.print("angle: ");
  Serial.println(ServoOutput);
  
}

void resetServo() {
  myServo.write(102);  // Set servo to 102 degrees for horizontal positioning
  delay(500);          // Delay to allow the servo to reach the desired position
}

float readPosition() {
  delay(40);                                                            //Don't set too low or echos will run into eachother.      
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.034 / 2; // Calculate distance in cm

  if (distance > 30 || distance <= 0) {
    distance = 40; // Set maximum distance as 30 cm for the ball
  }
  Serial.print("distance: ");
  Serial.println(distance);
  return distance;
}