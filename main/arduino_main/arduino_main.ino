#include <SoftwareSerial.h>

// comm 
SoftwareSerial espSerial(10, 11);

// motor
const int IN1 = 2;
const int IN2 = 3;
const int IN3 = 4;
const int IN4 = 5;

void setup() {
  Serial.begin(9600);
  // comm setup
  espSerial.begin(9600);
  Serial.println("Arduino: Listening for ESP32 on pin 10");

  // Motor setup
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  stopAllMotors();
}

void loop() {
  if (espSerial.available()) 
  {
    String message = espSerial.readStringUntil('\n');
    message.trim();
    Serial.print("ESP32 sent command: ");
    Serial.println(message);
    if (message.length() > 0) 
    {
      char command = message.charAt(0);
      executeMotorCommand(command);
    }
  }
}

void executeMotorCommand(char cmd) 
{
  switch (cmd) {
      case '1':
        Serial.println("Action: Motor 1 +");
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        delay(100);
        stopAllMotors();
        break;

      case '2':
        Serial.println("Action: Motor 1 -");
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        delay(100);
        stopAllMotors();
        break;

      case '3':
        Serial.println("Action: Motor 2 +");
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        delay(100);
        stopAllMotors();
        break;

      case '4':
        Serial.println("Action: Motor 2 -");
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
        delay(100);
        stopAllMotors();
        break;
      
      default:
        Serial.println("Action: Unknown Command");
        stopAllMotors();
        break; 
    }
}

void stopAllMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}