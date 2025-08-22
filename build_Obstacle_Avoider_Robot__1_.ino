#include <Servo.h> 

Servo Myservo;
#define trigPin 9   // HC-SR04 Trigger Pin
#define echoPin 8   // HC-SR04 Echo Pin
#define MLa 4       // Left Motor 1st Pin
#define MLb 5       // Left Motor 2nd Pin
#define MRa 6       // Right Motor 1st Pin
#define MRb 7       // Right Motor 2nd Pin

long duration, distance;

void setup() {
  Serial.begin(9600);
  pinMode(MLa, OUTPUT);
  pinMode(MLb, OUTPUT);
  pinMode(MRa, OUTPUT);
  pinMode(MRb, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Myservo.attach(10);
  Myservo.write(90);  // Set initial servo position to front
}

long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  return duration / 58.2; // Convert to cm
}

void moveForward() {
  digitalWrite(MRb, HIGH);
  digitalWrite(MRa, LOW);
  digitalWrite(MLb, HIGH);
  digitalWrite(MLa, LOW);
}

void moveBackward() {
  digitalWrite(MRb, LOW);
  digitalWrite(MRa, HIGH);
  digitalWrite(MLb, LOW);
  digitalWrite(MLa, HIGH);
}

void stopMovement() {
  digitalWrite(MRb, LOW);
  digitalWrite(MRa, LOW);
  digitalWrite(MLb, LOW);
  digitalWrite(MLa, LOW);
}

void loop() {
  distance = getDistance();
  Serial.println(distance);
  
  if (distance > 10) {
    moveForward();
  } 
  else if (distance > 0 && distance < 10) {  
    stopMovement();
    delay(100);
    
    // Move backward
    moveBackward();
    delay(1000);  // Move backward for 1 second
    stopMovement();
    delay(100);
    
    // Retry moving forward
    moveForward();
    delay(500);  // Move forward a bit before rechecking
  }

  delay(50);
}