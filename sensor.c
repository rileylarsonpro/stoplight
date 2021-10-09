
#include <ESP8266WiFi.h>              // This includes the libraries to connect to wifi and start a server
#include <ESP8266HTTPClient.h>
#include <string>

const char* wifiPSK  = "";            // And the preshared key (wifi password)
const char* wifiSSID = "Riley iPhone";
const String stoplightIP = "172.20.10.10";

#define ECHO D2
#define TRIG D3

long duration;

void setup() {                        // Perform this part once when first powered on
  Serial.begin(9600);               // Open a serial connection (for debugging)
  // ** Connect to WiFi network - Adapted from https://github.com/todddb/example-lab/blob/master/example-lab/example-lab.ino
  Serial.print("Connecting to ");           // Display debugging connection info
  Serial.println(wifiSSID);                 // Print the configured SSID to the Serial Monitor

  WiFi.begin(wifiSSID, wifiPSK);            // Use the provided SSID and PSK to connect

  while (WiFi.status() != WL_CONNECTED) {   // If not connected to wifi
    delay(500);                             // Pause
    Serial.print(".");                      // Print a dot each loop while trying to connect
  }
  Serial.println("");
  Serial.println("WiFi connected");         // Print "connected" message to the Serial Monitor

  // Setup Pins for distance sensor 
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  Serial.begin(9600);

} 


void loop() { 
  // Connect to clinet
  WiFiClient client; 
  const int httpPort = 80;
  if (!client.connect(stoplightIP, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  digitalWrite(TRIG, LOW);
  delay(20);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(15);
  digitalWrite(TRIG, LOW);
  duration = pulseIn(ECHO, HIGH);

  Serial.print("Distance: ");
  float inches = duration * 0.013504/2;
  Serial.println(duration * 0.013504/2);

  HTTPClient http;
  String url = "http://" + stoplightIP;
  if (inches >= 10 ){ // GREEN STATE
    url += "/green_on";
  }
  else if (inches >= 6 ){ // YELLOW STATE
    url += "/yellow_on";
  }
  else if (inches >= 4) { // RED STATE
     url += "/red_on";
  }
  else { // FLASHING STATE
    url += "/toggle_red";
  }
  // Code adapted from https://esp8266-shop.com/blog/how-to-http-get-and-post-requests-with-esp8266/
  client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + stoplightIP + "\r\n" + "Connection: close\r\n\r\n");
  delay(500);
}
