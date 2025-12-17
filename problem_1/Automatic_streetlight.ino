//set pin numbers
//const won't change
const int ledPin = 13;   //the number of the LED pin
const int ldrPin = A0;  //the number of the LDR pin
 
 
void setup() {
 
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);  //initialize the LED pin as an output
  pinMode(ldrPin, INPUT);   //initialize the LDR pin as an input
}
 
void loop() {
  //Serial.println(ldrStatus); used to check the ldr intensity at day and night
  int ldrStatus = analogRead(ldrPin);   //read the status of the LDR value
 
  //check if the LDR status is <= 300
  //if it is, the LED is HIGH
 
   if (ldrStatus <=530) {
 
    digitalWrite(ledPin, HIGH);               //turn LED on
    Serial.println("Night Time , Street light is ON");
    
   }
  else {
 
    digitalWrite(ledPin, LOW);          //turn LED off
    Serial.println("Day Time , Street light  is off");
  }
}
