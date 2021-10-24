#include <Arduino.h>
#include <string>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char *wifiPSK = ""; // And the preshared key (wifi password)
const char *wifiSSID = "Riley iPhone";   // In order for this to work, you MUST specify the SSID for your wifi

//**  Connect to MQTT Adapted from Todd Barrett’s Example code **//
const char *server = "172.20.10.13";
//**  Connect to MQTT Adapted from Todd Barrett’s Example code **//

char *doorTopic = "/door";
String macAddr = WiFi.macAddress();       // Store arduino MAC address as a string
String host = "arduino-" + macAddr.substring(15) ;  // Create hostname for this device
char *connectTopic = "/connect";
char *disconnectTopic = "/disconnect";

String message;                         // Used for formatting message

WiFiClient wifiClient;               // Instantiate wifi
PubSubClient mqttClient(wifiClient); // Instantiate mqtt client


int DOOR = D1;
boolean doorState = true;


void setup()
{                                     // Perform this part once when first powered on
  Serial.begin(9600);                 // Open a serial connection (for debugging)
  delay(10);                          // Wait 10 milliseconds (1/100th of a second)
  Serial.println("Initializing ..."); // DEBUG CODE

  pinMode(DOOR, INPUT);   // Set the LED pin to Output

  // ** Connect to WiFi network - Adapted from https://github.com/todddb/example-lab/blob/master/example-lab/example-lab.ino
  Serial.print("Connecting to "); // Display debugging connection info
  Serial.println(wifiSSID);       // Print the configured SSID to the Serial Monitor

  WiFi.begin(wifiSSID, wifiPSK); // Use the provided SSID and PSK to connect

  while (WiFi.status() != WL_CONNECTED)
  {                    // If not connected to wifi
    delay(500);        // Pause
    Serial.print("."); // Print a dot each loop while trying to connect
  }
  Serial.println("");
  Serial.println("WiFi connected"); // Print "connected" message to the Serial Monitor

  // ----- Connect to MQTT -----
  Serial.println("Connecting to MQTT Broker"); // Serial debug
  mqttClient.setServer(server, 1883);          // Set up MQTT Connection Info
  mqttClient.setCallback(callback);            // Function to call when new messages are received
  mqttClient.connect(host.c_str());            // Connect to the broker with unique hostname
  mqttClient.subscribe(doorTopic);             // Subscribe to the LED topic on the broker
  Serial.println(mqttClient.state());          // Show debug info about MQTT state
}


void loop()
{
  mqttClient.loop(); // Check for new MQTT messages
  doorState = digitalRead(DOOR); // Set the pin to LOW (Off)
  Serial.println("Door State");
  if(!doorState) {
    message = "door_open";
  }
  else {
    message = "door_close";
  }
  Serial.println(doorState);

//**  Connect to MQTT Adapted from Todd Barrett’s Example code **//
   char messageChar[message.length() + 1];                                                           // Create a char array as long as message
    message.toCharArray(messageChar, message.length() + 1);                                           // Convert message to char
    mqttClient.publish(doorTopic, messageChar);     
  delay(500); // This introduces a little pause in each cycle. Probably helps save some power.
}

// The callback function is defined above. New MQTT messages are handed to this function.
void callback(char* topic, byte* payload, unsigned int length) {                                      // Callback function to read messages for subscribed topics
  Serial.print("Message arrived [");    // Serial Debug
  Serial.print(topic);                  //    Print the topic name [in brackets]
  Serial.print("] ");                   //
  for (int i = 0; i < length; i++) {    // Iterate through the characters in the payload array
    Serial.print((char)payload[i]);     //    and display each character
  }
  Serial.println();                     // add a blank line
}
