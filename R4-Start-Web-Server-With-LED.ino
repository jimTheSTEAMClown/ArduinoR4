//#include "R4WiFi_secrets.h"
#define SECRET_SSID         "your_SSID";
#define SECRET_PASS         "Your_SSID_Password";
#include <R4HttpClient.h>
WiFiServer server(80);
int LED = 13;
//#define LED 10;
String led_status = "OFF";


// the setup function runs once when you press reset or power the board
WiFiSSLClient client;
R4HttpClient http;

const char* _SSID = SECRET_SSID;
const char* _PASS = SECRET_PASS;

void printMacAddress(byte mac[]) {
  for (int i=0; i<6; i++){
    if(i>0) {
      Serial.print(":");      
    }
    if(mac[i] <16) {
      Serial.print("0");      
    }
    Serial.print(mac[i],HEX);  
  }
  Serial.println();  
}

void setup()
{
  Serial.begin(115200);
  pinMode(LED, OUTPUT);

  while (!Serial);

  String fv = WiFi.firmwareVersion();
  Serial.println(fv);
  if (fv < WIFI_FIRMWARE_LATEST_VERSION)
    Serial.println(F("Please upgrade the firmware"));
    Serial.println(WIFI_FIRMWARE_LATEST_VERSION);
  if (WiFi.status() == WL_NO_MODULE)
  {
    Serial.println(F("Communication with WiFi module failed!"));
    while (true);
  }

  WiFi.begin(_SSID, _PASS);
  Serial.print(F("Connecting to WiFi"));
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(F("."));
  }
  Serial.println();
  Serial.println(F("Successfully connected to WiFi!"));
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  long rssi = WiFi.RSSI();
  Serial.print("Signal Strength (RSSI): ");
  Serial.println(rssi);
  byte encryption = WiFi.encryptionType();
  Serial.print("Encryption Type: ");
  Serial.println(encryption,HEX);
  Serial.println();
  byte mac[6];
  WiFi.macAddress(mac);
    Serial.print("MAC Address: ");
  printMacAddress(mac);
  //Serial.println();
  byte bssid[6];
  WiFi.BSSID(bssid);
  Serial.print("BSSID: ");
  printMacAddress(bssid);
  Serial.println();
  // Start the web server
  server.begin();

  
}

void loop() {
  WiFiClient client = server.available(); // Check if a client has connected 
  if (client) { // If a client has connected
    Serial.println("New client connected");
    String request = client.readStringUntil('\r'); // Read the client's request 
    Serial.println (request); // Print the request to the serial monitor

    // Respond to client request
    if (request.indexOf("/H") != -1) {
      digitalWrite(LED, HIGH); 
      led_status="ON"; 
    }else if (request.indexOf("/L") != -1) {
      digitalWrite(LED, LOW); 
      led_status="OFF"; 
    }  
    // Send HTTP response to client 
    client.println("HTTP/1.1 200 OK"); 
    client.println("Content-type: text/html");
    client.println();
    client.println("<html><body>");
    client.println("<h1>LED status is " + led_status + "</h1>");
    client.println("<h2>Click a Link</h1>");
    client.println("<a href=\"http://192.168.1.140/H\">Turn The LED On</a>");
    client.println("<br>");
    client.println("<a href=\"http://192.168.1.140/L\">Turn The LED Off</a>");  
    client.println("");
  

    client.println("</body></html>");
    //delay(100);
    // Close the connection
    client.stop();
    Serial.println("Client disconnected");
  }
}


