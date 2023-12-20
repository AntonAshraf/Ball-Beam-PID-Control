double Input, Output;                

const int trigPin = 9;    // Trig pin of the ultrasonic sensor
const int echoPin = 10;   // Echo pin of the ultrasonic sensor

void setup() {

  Serial.begin(9600);                                                //Begin Serial 

  Input = readPosition();                                            //Calls function readPosition() and sets the balls
                                                                     //  position as the input to the PID algorithm

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);                                       

}

void loop(){
  Input = readPosition();                                              
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