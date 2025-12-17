#include <Ultrasonic.h>
#include <Servo.h>

Servo myservo;  
Ultrasonic ultrasonic(2, 3);
int distance;

void setup() {
  pinMode(5, OUTPUT);
  myservo.attach(9);  
  Serial.begin(9600);
  myservo.write(0);
}

void loop() {
  
  distance = ultrasonic.read();
  if (distance <= 30){            
    digitalWrite(5, HIGH);
    myservo.write(90);
    delay(4000);
    myservo.write(0);
    digitalWrite(5, LOW);

  }
  Serial.print("Distance in CM: ");
  Serial.println(distance);
  delay(100);
}

