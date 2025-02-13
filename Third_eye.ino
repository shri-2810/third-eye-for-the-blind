const int TrigPin = A4;  // Trigger connected to PIN
const int EchoPin = A5;  // Echo connected to PIN
int led = 13;            // LED pin connected to PIN 13
int buz1 = 4;            // Buzzer to PIN 4
int vibMotor = 10;       // Vibrator motor pin connected to PIN 10
int buttonPin = 12;       // Push button connected to PIN 2
int buttonState = 0;     // Variable to store the button state
int lastButtonState = 0; // Variable to store the previous button state
unsigned long lastDebounceTime = 0;  // Last time the button was pressed
unsigned long debounceDelay = 50;    // Debounce time; increase if the button is too sensitive

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(buz1, OUTPUT);
  pinMode(vibMotor, OUTPUT);
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);  // Internal pull-up resistor for the button
}

void loop() {
  int reading = digitalRead(buttonPin);
  
  // Check if the button state has changed
  if (reading != lastButtonState) {
    lastDebounceTime = millis();  // Reset the debounce timer
  }

  // Check if the button state has been stable for a certain time
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // If the button is pressed once
    if (reading == LOW && buttonState == LOW) {
      buttonState = HIGH;

      long duration, cm;
      digitalWrite(TrigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(TrigPin, HIGH);
      delayMicroseconds(5);
      digitalWrite(TrigPin, LOW);
      duration = pulseIn(EchoPin, HIGH);  // Read Echo pin and return soundwave duration
      cm = microsecondsToCentimeters(duration);  // Microseconds are converted to Centimeters
      
      if (cm <= 100 && cm > 0) {
        int d = map(cm, 1, 300, 10, 1000);
        digitalWrite(led, HIGH);
        digitalWrite(buz1, HIGH);
        digitalWrite(vibMotor, HIGH);
        delay(50);
        digitalWrite(led, LOW);
        digitalWrite(buz1, LOW);
        digitalWrite(vibMotor, LOW);
        delay(d);
      }
      Serial.print(cm);  // Measured distance displayed in serial monitor
      Serial.print("cm");
      Serial.println();
    }
    // If the button is pressed twice
    else if (reading == LOW && buttonState == HIGH) {
      buttonState = LOW;
      // Perform actions for turning off the system if needed
    }
  }

  lastButtonState = reading;  // Save the current button state
  delay(50);
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
