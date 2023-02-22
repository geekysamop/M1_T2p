// Define the ultrasound sensor pins
const int trigPin = 9;
const int echoPin = 10;

// Define the LED pin
const int ledPin = 13;

// Define the threshold distance in centimeters
const int threshold = 30;

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
  if (distance < threshold) {
    digitalWrite(ledPin, HIGH);
    delay(100);
    digitalWrite(ledPin, LOW);
  }

  delay(100);
}

// Interrupt function that is triggered when the echoPin changes state
void interruptFunction() {
  if (digitalRead(echoPin) == HIGH) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
}
