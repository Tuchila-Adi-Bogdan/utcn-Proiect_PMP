#include <WiFi.h>
#include <WiFiAP.h>
#include <WiFiClient.h>

// SERIAL COMMUNICATION
#define RXD2 16
#define TXD2 17

// WIFI CONFIGURATION 
const char *SSID = "esp32wifi";
const char *PASS = "12345678";

const int HTTP_PORT_NO = 80;
WiFiServer HttpServer(HTTP_PORT_NO);

// --- MESSAGES ---
const String SETUP_INIT = "SETUP: Initializing ESP32 dev board";
const String SETUP_ERROR = "!!ERROR!! SETUP: Unable to start SoftAP mode";
const String SETUP_SERVER_START = "SETUP: HTTP server started --> IP addr: ";
const String INFO_NEW_CLIENT = "New client connected";
const String INFO_DISCONNECT_CLIENT = "Client disconnected";

// Standard HTTP Header
const String HTTP_HEADER = "HTTP/1.1 200 OK\r\nContent-type:text/html\r\n\r\n";

// Variable to store the HTTP request
String header;

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  
  Serial.println(SETUP_INIT);
  if (!WiFi.softAP(SSID, PASS)) 
  { 
    Serial.println(SETUP_ERROR);
    while (1);
  }

  IPAddress accessPointIP = WiFi.softAPIP();
  Serial.print(SETUP_SERVER_START);
  Serial.println(accessPointIP);
  
  // Start the Web Server
  HttpServer.begin();
}

void loop() 
{
  WiFiClient client = HttpServer.available();
  
  if (client) 
  {
    Serial.println(INFO_NEW_CLIENT);
    String currentLine = "";
    header = ""; 

    while (client.connected()) 
    {
      if (client.available()) 
      {
        char c = client.read();
        header += c; 
        if (c == '\n') 
        {
          if (currentLine.length() == 0) 
          {
            if (header.indexOf("GET /btn1") >= 0) {
              Serial.println("Web: Button 1 Pressed -> Sending '1' to Arduino");
              Serial2.println("1"); // Send to Arduino
            } 
            else if (header.indexOf("GET /btn2") >= 0) {
              Serial.println("Web: Button 2 Pressed -> Sending '2' to Arduino");
              Serial2.println("2"); // Send to Arduino
            } 
            else if (header.indexOf("GET /btn3") >= 0) {
              Serial.println("Web: Button 3 Pressed -> Sending '3' to Arduino");
              Serial2.println("3"); // Send to Arduino
            } 
            else if (header.indexOf("GET /btn4") >= 0) {
              Serial.println("Web: Button 4 Pressed -> Sending '4' to Arduino");
              Serial2.println("4"); // Send to Arduino
            }
            
            // Show the webpage to the user
            printWebPage(client);
            break;
            
          } 
          else 
          {
            currentLine = "";
          }
        } 
        else if (c != '\r') 
        {
          currentLine += c;
        }
      }
    }
    
    header = ""; 
    client.stop();
    Serial.println(INFO_DISCONNECT_CLIENT);
  }
}

// Function to generate the HTML
void printWebPage(WiFiClient client) {
  client.println(HTTP_HEADER);
  
  client.println("<!DOCTYPE html><html>");
  client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  client.println("<style>");
  client.println("html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center; background-color: #222; color: white;}");
  client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 20px; width: 200px;");
  client.println("text-decoration: none; font-size: 20px; margin: 10px; cursor: pointer; border-radius: 10px;}");
  client.println(".button2 {background-color: #FF9800;}"); // Orange
  client.println(".button3 {background-color: #008CBA;}"); // Blue
  client.println(".button4 {background-color: #f44336;}"); // Red
  client.println("h1 {color: #f2f2f2;}");
  client.println("</style></head>");
  
  client.println("<body><h1>Remote Motor Control</h1>");
  
  // Motor 1 Controls
  client.println("<h3>Motor 1</h3>");
  client.println("<p><a href=\"/btn1\"><button class=\"button\">Clockwise</button></a></p>");
  client.println("<p><a href=\"/btn2\"><button class=\"button button2\">Counter-CW</button></a></p>");
  
  client.println("<hr>"); // Divider line
  
  // Motor 2 Controls
  client.println("<h3>Motor 2</h3>");
  client.println("<p><a href=\"/btn3\"><button class=\"button button3\">Clockwise</button></a></p>");
  client.println("<p><a href=\"/btn4\"><button class=\"button button4\">Counter-CW</button></a></p>");
  
  client.println("</body></html>");
  client.println();
}