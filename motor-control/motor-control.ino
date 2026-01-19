const int IN1 = 2;
const int IN2 = 3;
const int IN3 = 4;
const int IN4 = 5;

void setup() {
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  stopAllMotors();
  Serial.println("Init gata");
  Serial.println("1: M1 +, 2: M1 -, 3: M2 +, 4: M2 -");
}

void loop() {
  if (Serial.available() > 0) 
  {
    char command = Serial.read();
    switch (command) 
    {
      case '1':
        // Motor 1 +
        Serial.println("Motor 1: +");
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        delay(100);
        stopAllMotors();
        break;

      case '2':
        // Motor 1 -
        Serial.println("Motor 1: -");
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        delay(100);
        stopAllMotors();
        break;

      case '3':
        // Motor 2 +
        Serial.println("Motor 2: +");
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        delay(100);
        stopAllMotors();
        break;

      case '4':
        // Motor 2 -
        Serial.println("Motor 2: -");
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
        delay(100);
        stopAllMotors();
        break;
      
      default:
        break; 
    }
  }
}

void stopAllMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}