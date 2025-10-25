# Arduino Smart Security System (Tinkercad Simulation)

This project is a complete "Smart Security System" built and simulated entirely in **Autodesk Tinkercad**. It uses an Arduino Uno to control an LED, a buzzer, and a PIR motion sensor.

It simulates a real-world IoT (Internet of Things) device by using the **Serial Monitor as a "command app"** to arm the system, check its status, and receive alerts.

## 🚀 Features

-   **Remote Commands**: Control the system by sending commands through the Serial Monitor.
-   **Arm/Disarm**: An `ARM` command puts the system into a monitoring state. `DISARM` turns it off.
-   **Motion Detection**: When armed, the **PIR sensor** automatically detects motion and triggers a visual and audible `ALARM`.
-   **Multiple States**: The system can be `ON` (light on), `OFF` (disarmed), `BLINKING`, `ARMED`, or in full `ALARM` mode.
-   **Status Reports**: A `STATUS` command reports the system's current state back to the user (e.g., "System is ARMED").

## 🛠️ Components Used (Virtual)

-   Arduino Uno R3
-   PIR Motion Sensor
-   Piezo Buzzer
-   1x LED
-   1x 220 $\Omega$ Resistor
-   Jumper Wires & Breadboard

## Circuit Diagram

Here is the complete circuit wiring in Tinkercad:

*(**Action for you**: Add a screenshot of your Tinkercad circuit here. Just drag and drop the image file onto the GitHub README editor.)*

## 💻 How to Use

1.  **Open in Tinkercad**: [[Project Link](https://www.tinkercad.com/things/cj3uHaag9TB-iot-mini-project-3rd-yr)]
2.  **Start Simulation**: Click the "Start Simulation" button.
3.  **Open Serial Monitor**: Click the "Serial Monitor" button at the bottom of the screen.
4.  **Send Commands**: Type one of the following commands into the serial input box and press "Send":

### Available Commands

-   `ON`: Turns the LED on (solid).
-   `OFF` or `DISARM`: Turns off all components and disarms the system.
-   `BLINK`: Makes the LED flash.
-   `ARM`: Arms the security system. The light and buzzer will turn off, and the PIR sensor will begin watching for motion.
-   `STATUS`: Reports the system's current state (e.g., "DISARMED (OFF)", "ARMED", "ALARM").

### Testing the Alarm

1.  Send the `ARM` command.
2.  In the simulation, click the **PIR Motion Sensor**.
3.  Move the small blue circle to simulate movement.
4.  Observe as the system automatically enters the `ALARM` state, flashing the LED and sounding the buzzer.
5.  Send the `DISARM` command to stop the alarm.

## 🗒️ Code

Here is the complete `*.ino` sketch for the Arduino.

```cpp
// This variable will store the command we receive
String command; 

// This variable tracks the state of the system
// 0 = DISARMED (OFF), 1 = ON, 2 = BLINK, 3 = ALARM, 4 = ARMED
int systemState = 0; 

// Define our pins
int ledPin = 13;
int buzzerPin = 12;
int pirPin = 2; // Our new motion sensor pin

void setup() {
  // Set up our component pins
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(pirPin, INPUT); // PIR sensor is an INPUT
  
  Serial.begin(9600);
  
  Serial.println("Smart Security System Ready.");
  Serial.println("Commands: ON, OFF, BLINK, ARM, DISARM, STATUS"); 
}

void loop() {
  
  // --- PART 1: Check for new commands from the "app" ---
  if (Serial.available() > 0) {
    command = Serial.readStringUntil('\n');
    command.trim(); 

    if (command == "ON") {
      systemState = 1; 
      Serial.println("Command: ON. Light is now solid ON.");
    } 
    else if (command == "OFF" || command == "DISARM") { // 'OFF' and 'DISARM' do the same thing
      systemState = 0; 
      Serial.println("Command: DISARM. System is OFF.");
    } 
    else if (command == "BLINK") {
      systemState = 2; 
      Serial.println("Command: BLINK. Light is now blinking.");
    }
    else if (command == "ARM") {
      systemState = 4; // Set state to ARMED
      Serial.println("Command: ARM. System is ARMED. Watching for motion...");
    }
    else if (command == "STATUS") {
      Serial.print("Command: STATUS. Current state is: ");
      if (systemState == 0) Serial.println("DISARMED (OFF)");
      else if (systemState == 1) Serial.println("ON");
      else if (systemState == 2) Serial.println("BLINKING");
      else if (systemState == 3) Serial.println("ALARM (MOTION DETECTED!)");
      else if (systemState == 4) Serial.println("ARMED");
    }
    else {
      // ALARM is no longer a direct command, it's triggered by the sensor
      Serial.println("Unknown command.");
    }
  }

  // --- PART 2: Act based on the current system state ---
  if (systemState == 0) { // DISARMED
    digitalWrite(ledPin, LOW);
    noTone(buzzerPin); 
  }
  else if (systemState == 1) { // ON
    digitalWrite(ledPin, HIGH); 
    noTone(buzzerPin);
  } 
  else if (systemState == 2) { // BLINK
    digitalWrite(ledPin, HIGH);
    delay(500); 
    digitalWrite(ledPin, LOW);
    delay(500); 
    noTone(buzzerPin);
  }
  else if (systemState == 3) { // ALARM
    digitalWrite(ledPin, HIGH);
    tone(buzzerPin, 1000); 
    delay(250); 
    digitalWrite(ledPin, LOW);
    noTone(buzzerPin);
    delay(250); 
  }
  else if (systemState == 4) { // ARMED
    // System is quiet...
    digitalWrite(ledPin, LOW);
    noTone(buzzerPin);
    
    // ...but it's watching the sensor
    int motion = digitalRead(pirPin);
    
    if (motion == HIGH) {
      Serial.println("!!! MOTION DETECTED !!!");
      Serial.println("Triggering ALARM!");
      systemState = 3; // Switch to ALARM state!
    }
  }
}

```