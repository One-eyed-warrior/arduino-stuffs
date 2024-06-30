#include <Servo.h>

#define trigPin 10 // Trigger pin for ultrasonic sensor
#define echoPin  9  // Echo pin for ultrasonic sensor

#define servoPin 5  // Pin connected to the servo motor

const int minServoPosition = 0;   // Minimum position for the servo (in degrees)
const int maxServoPosition = 180; // Maximum position for the servo (in degrees)

long duration; // Variable to store pulse duration
int distance;  // Variable to store calculated distance

Servo myservo;  // Create a servo object

void setup() {
  pinMode(trigPin, OUTPUT); // Set trigger pin as output
  pinMode(echoPin, INPUT);  // Set echo pin as input
  pinMode(servoPin, OUTPUT);  // Set servo pin as output
  myservo.attach(servoPin);   // Attach the servo to the servoPin

  Serial.begin(9600);        // Start serial communication at 9600 baud
}

void loop() {
  // Trigger the ultrasonic sensor
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(2); // Send a short pulse (high for 2 microseconds)
  digitalWrite(trigPin, LOW);

  // Measure pulse duration (time for sound wave to go and return)
  duration = pulseIn(echoPin, HIGH);

  // Calculate distance (speed of sound * round trip time / 2)
  distance = duration * 0.034 / 2;

  // Print distance to serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Control servo based on distance
  if (distance < 20) { // If object is less than 20 cm away
    myservo.write(maxServoPosition);  // Move servo to maximum position
  } else {
    myservo.write(minServoPosition);  // Move servo to minimum position
  }

  delay(1000); // Wait for one second before next measurement
}
  
