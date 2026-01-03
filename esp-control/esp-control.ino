#include <WiFi.h>
#include <WiFiAP.h>
#include <WiFiClient.h>

// Mesaje predefinite
const String SETUP_INIT = "SETUP: Initializing ESP32 dev board";
const String SETUP_ERROR = "!!ERROR!! SETUP: Unable to start SoftAP mode";
const String SETUP_SERVER_START = "SETUP: HTTP server started --> IP addr: ";
const String SETUP_SERVER_PORT = " on port: ";
const String INFO_NEW_CLIENT = "New client connected";
const String INFO_DISCONNECT_CLIENT = "Client disconnected";

// Header HTTP standard
const String HTTP_HEADER = "HTTP/1.1 200 OK\r\nContent-type:text/html\r\n\r\n";

// Configurare WiFi
const char *SSID = "esp32wifi";
const char *PASS = "12345678";

const int HTTP_PORT_NO = 80;

WiFiServer HttpServer(HTTP_PORT_NO);

// Variabila pentru a stoca cererea HTTP (header-ul)
String header;

void setup() {
  Serial.begin(9600);
  
  // Pornim SoftAP cu parola definita
  if (!WiFi.softAP(SSID)) {
    Serial.println(SETUP_ERROR);
    while (1);
  }

  const IPAddress accessPointIP = WiFi.softAPIP();
  const String webServerInfoMessage = SETUP_SERVER_START + accessPointIP.toString() 
                                    + SETUP_SERVER_PORT + HTTP_PORT_NO;
  
  HttpServer.begin();
  Serial.println(webServerInfoMessage);
}

void loop() {
  WiFiClient client = HttpServer.available();
  
  if (client) {
    Serial.println(INFO_NEW_CLIENT);
    String currentLine = "";
    header = ""; // Resetam header-ul pentru noul client

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        header += c; // Adaugam caracterul citit in string-ul 'header'
        
        if (c == '\n') {
          // Daca linia este goala (doua newline consecutive), s-a terminat request-ul HTTP
          if (currentLine.length() == 0) {
            
            // --- AICI VERIFICAM BUTOANELE ---
            // Verificam ce a cerut browserul cautand in variabila 'header'
            
            if (header.indexOf("GET /btn1") >= 0) {
              Serial.println(">>> Comanda primita: BUTONUL 1 (Actiune A)");
              // Aici poti adauga cod sa aprinzi un LED, etc.
            } 
            else if (header.indexOf("GET /btn2") >= 0) {
              Serial.println(">>> Comanda primita: BUTONUL 2 (Actiune B)");
            } 
            else if (header.indexOf("GET /btn3") >= 0) {
              Serial.println(">>> Comanda primita: BUTONUL 3 (Actiune C)");
            } 
            else if (header.indexOf("GET /btn4") >= 0) {
              Serial.println(">>> Comanda primita: BUTONUL 4 (Actiune D)");
            }
            
            // Trimitem pagina web inapoi catre client
            printWebPage(client);
            break;
            
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    
    header = ""; // Curatam header-ul
    client.stop();
    Serial.println(INFO_DISCONNECT_CLIENT);
    Serial.println();
  }
}

void printWebPage(WiFiClient client) {
  client.println(HTTP_HEADER);
  
  // HTML-ul Paginei
  client.println("<!DOCTYPE html><html>");
  client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  client.println("<style>");
  client.println("html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
  client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
  client.println("text-decoration: none; font-size: 30px; margin: 10px; cursor: pointer; display: block;}");
  client.println(".button2 {background-color: #555555;}");
  client.println(".button3 {background-color: #008CBA;}");
  client.println(".button4 {background-color: #f44336;}");
  client.println("</style></head>");
  
  client.println("<body><h1>ESP32 Control Panel</h1>");
  
  client.println("<p><a href=\"/btn1\"><button class=\"button\">M1+10</button></a></p>");
  client.println("<p><a href=\"/btn2\"><button class=\"button button2\">M1-10</button></a></p>");
  client.println("<p><a href=\"/btn3\"><button class=\"button button3\">M2+10</button></a></p>");
  client.println("<p><a href=\"/btn4\"><button class=\"button button4\">M2-10</button></a></p>");
  
  client.println("</body></html>");
  client.println();
}