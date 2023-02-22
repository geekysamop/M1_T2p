// Define the ultrasound sensor pins
const int trigPin = 9;
const int echoPin = 2;

// Define the LED pin
const int ledPin = 13;

// Define the threshold distance in centimeters
const int threshold = 30;
static unsigned long startTime = 0;
static unsigned long endTime = 0;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(echoPin), interruptFunction, CHANGE);
}

void loop() {
  // Send a pulse to the ultrasound sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the pulse duration
  unsigned long pulseDuration = pulseIn(echoPin, HIGH);

  // Convert the pulse duration to distance in centimeters
  int distance = pulseDuration / 58;

  // Print the distance to the serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // If the distance falls below the threshold, blink the LED
  

  delay(100);
}

// Interrupt function that is triggered when the echoPin changes state
void interruptFunction() {
  int echo = digitalRead(echoPin);
  if(echo == HIGH){
  	startTime = micros();
  }else{
    endTime = micros();
  	long duration = endTime - startTime;
    int distance = duration/58;
    if(distance < threshold)
    {
   	  digitalWrite(ledPin,HIGH);
      delay(500);
      digitalWrite(ledPin,LOW);
      delay(500);
    }
  }
  
}
