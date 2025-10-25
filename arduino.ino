// This variable will store the command we receive
String command; 

// This variable tracks the state of the light
// 0 = OFF, 1 = ON, 2 = BLINK, 3 = ALARM
int ledState = 0; 

// Define our pins
int ledPin = 13;
int buzzerPin = 12;

void setup() {
  // Set up our component pins
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  
  Serial.begin(9600);
  
  Serial.println("Smart Light & Alarm System Ready.");
  Serial.println("Commands: ON, OFF, BLINK, ALARM, STATUS"); 
}

void loop() {
  
  // --- PART 1: Check for new commands ---
  if (Serial.available() > 0) {
    command = Serial.readStringUntil('\n');
    command.trim(); 

    if (command == "ON") {
      ledState = 1; 
      Serial.println("Command: ON. Light is now solid ON.");
    } 
    else if (command == "OFF") {
      ledState = 0; 
      Serial.println("Command: OFF. System is OFF.");
    } 
    else if (command == "BLINK") {
      ledState = 2; 
      Serial.println("Command: BLINK. Light is now blinking.");
    }
    else if (command == "ALARM") {
      ledState = 3; // Set state to ALARM
      Serial.println("Command: ALARM. Security alert activated!");
    }
    else if (command == "STATUS") {
      Serial.print("Command: STATUS. Current state is: ");
      if (ledState == 0) {
        Serial.println("OFF");
      } else if (ledState == 1) {
        Serial.println("ON");
      } else if (ledState == 2) {
        Serial.println("BLINKING");
      } else if (ledState == 3) {
        Serial.println("ALARM");
      }
    }
    else {
      Serial.println("Unknown command.");
    }
  }

  // --- PART 2: Act based on the current state ---
  if (ledState == 1) {
    // State is ON
    digitalWrite(ledPin, HIGH); 
    noTone(buzzerPin); // Make sure buzzer is off
  } 
  else if (ledState == 0) {
    // State is OFF
    digitalWrite(ledPin, LOW);
    noTone(buzzerPin); // Make sure buzzer is off
  } 
  else if (ledState == 2) {
    // State is BLINK
    digitalWrite(ledPin, HIGH);
    delay(500); 
    digitalWrite(ledPin, LOW);
    delay(500); 
    noTone(buzzerPin); // Make sure buzzer is off
  }
  else if (ledState == 3) {
    // State is ALARM
    digitalWrite(ledPin, HIGH);   // Light ON
    tone(buzzerPin, 1000); // Buzzer ON (at 1000 Hz)
    delay(250); // Wait 0.25 seconds
    digitalWrite(ledPin, LOW);    // Light OFF
    noTone(buzzerPin);  // Buzzer OFF
    delay(250); // Wait 0.25 seconds
  }
}