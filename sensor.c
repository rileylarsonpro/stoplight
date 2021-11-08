
#include <ESP8266WiFi.h>              // This includes the libraries to connect to wifi and start a server
#include <string>
#include <Arduino.h>
#include <PubSubClient.h>

const char* wifiPSK  = "";            // And the preshared key (wifi password)
const char* wifiSSID = "Riley iPhone";
const char* server = "172.20.10.13";
//**  Connect to MQTT Adapted from Todd Barrett’s Example code **//

char* distanceTopic = "/distance";
char* connectTopic = "/connect";
char* disconnectTopic = "/disconnect";

// ------- Hostname of this Arduino -------
String macAddr = WiFi.macAddress();      // Store arduino MAC address as a string
String host = "arduino-" + macAddr.substring(15) ;  // Set a client ID for this device (should not match other MQTT devices)

// ------- Global Variables and Classes -------
String message;                         // Used for formatting message
long timer;                             // Used to track how often to send messages
WiFiClient wifiClient;                  // Instantiate wifi
PubSubClient mqttClient(wifiClient);    // Instantiate mqtt client


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
  delay (1000);                         // Let everything settle

  mqttClient.setServer(server, 1883);   // Set up MQTT Connection Info
  mqttClient.setCallback(callback);     // Set callback action for receiving messages

  Serial.println("Connecting to MQTT Broker"); // Serial debug
  char hostChar[host.length()+1];         // These 2 lines convert host (String) to Char Array
  host.toCharArray(hostChar, host.length()+1 );
  // This is the simple way to connect
  //if (mqttClient.connect(hostChar)) {
  // This connects with a Last Will and Testament message
  if (mqttClient.connect(hostChar, disconnectTopic, 0, false, hostChar)) {  
    Serial.println("MQTT Connected");
    mqttClient.publish(connectTopic, hostChar);
    Serial.println(mqttClient.state());

  } else {
    Serial.println("MQTT Connection Failure");
    Serial.println(mqttClient.state());
  }

  // ------- MQTT Subscribe to a topic -------
  mqttClient.subscribe(distanceTopic);

  

  // Setup Pins for distance sensor 
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);


} 


void loop() { 
  mqttClient.loop();  

// END OF ADAPTED CODE FROM TODD
  digitalWrite(TRIG, LOW);
  delay(20);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(15);
  digitalWrite(TRIG, LOW);
  duration = pulseIn(ECHO, HIGH);

  Serial.print("Distance: ");
  float inches = duration * 0.013504/2;
  Serial.println(duration * 0.013504/2);

  message = (String)inches;

//**  Connect to MQTT Adapted from Todd Barrett’s Example code **//
    char messageChar[message.length() + 1];                                                           // Create a char array as long as message
    message.toCharArray(messageChar, message.length() + 1);                                           // Convert message to char
    mqttClient.publish(distanceTopic, messageChar);     
    delay(500);
}


void callback(char* topic, byte* payload, unsigned int length) {                                      // Callback function to read messages for subscribed topics
  Serial.print("Message arrived [");    // Serial Debug
  Serial.print(topic);                  //    Print the topic name [in brackets]
  Serial.print("] ");                   //
  for (int i = 0; i < length; i++) {    // Iterate through the characters in the payload array
    Serial.print((char)payload[i]);     //    and display each character
  }
  Serial.println();                     // add a blank line
}
// END OF ADAPTED CODE FROM TODD