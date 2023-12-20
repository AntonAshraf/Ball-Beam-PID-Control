// note: for my beam to be horizontal, Servo Motor angle should be 102 degrees.
#include<Servo.h>

const int trigPin = 9;    // Trig pin of the ultrasonic sensor
const int echoPin = 10;   // Echo pin of the ultrasonic sensor
const int servoPin = 11;  // Servo Pin

double Input, Output;                                       

Servo myServo;                                                       //Initialize Servo.

void setup() {

  Serial.begin(9600);                                                //Begin Serial 
  myServo.attach(servoPin);                                          //Attach Servo
  resetServo();                                               // Reset servo to initial angle

  Input = readPosition();                                            //Calls function readPosition() and sets the balls
                                                                     //  position as the input to the PID algorithm

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);                                       

}

void loop(){
  // delay(100);
  Input = readPosition();                                            
  resetServo();
  
}

void resetServo() {
  myServo.write(102);  // Set servo to 102 degrees for horizontal positioning
  delay(500);          // Delay to allow the servo to reach the desired position
}


float readPosition() {
  // delay(40);                                                            //Don't set too low or echos will run into eachother.      
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.034 / 2; // Calculate distance in cm

  Serial.print("distance: ");
  Serial.println(distance);
  return distance;
}