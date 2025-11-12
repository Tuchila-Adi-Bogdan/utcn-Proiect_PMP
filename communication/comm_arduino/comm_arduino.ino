//ardu
#include <SoftwareSerial.h>

SoftwareSerial espSerial(10, 11);
void setup() {
  Serial.begin(9600);
  Serial.println("Arduino Receiver is running...");
  Serial.println("Waiting for messages from ESP32...");
  espSerial.begin(9600);
}
void loop() 
{
  if (espSerial.available()) 
  {
    String message = espSerial.readStringUntil('\n');
    Serial.print("ESP32 says: ");
    Serial.println(message);
  }
}