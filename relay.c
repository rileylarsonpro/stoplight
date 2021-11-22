#include <Arduino.h>
#include <string>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char *wifiPSK = ""; // And the preshared key (wifi password)
const char *wifiSSID = "Riley iPhone";   // In order for this to work, you MUST specify the SSID for your wifi

//**  Connect to MQTT Adapted from Todd Barrett’s Example code **//
const char *server = "172.20.10.13";
//**  Connect to MQTT Adapted from Todd Barrett’s Example code **//

char *relayTopic = "/relay";
String macAddr = WiFi.macAddress();       // Store arduino MAC address as a string
String host = "arduino-" + macAddr.substring(15) ;  // Create hostname for this device
char *connectTopic = "/connect";
char *disconnectTopic = "/disconnect";

String message;                         // Used for formatting message

WiFiClient wifiClient;               // Instantiate wifi
PubSubClient mqttClient(wifiClient); // Instantiate mqtt client


int RELAY = D1;
boolean relayState = false;


void setup()
{                                     // Perform this part once when first powered on
  Serial.begin(9600);                 // Open a serial connection (for debugging)
  delay(10);                          // Wait 10 milliseconds (1/100th of a second)
  Serial.println("Initializing ..."); // DEBUG CODE

  pinMode(RELAY, OUTPUT);   // Set the LED pin to Output
  digitalWrite(RELAY, LOW);   
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
  mqttClient.subscribe(relayTopic);             // Subscribe to the LED topic on the broker
  Serial.println(mqttClient.state());          // Show debug info about MQTT state
}


void loop()
{
  mqttClient.loop(); // Check for new MQTT messages
  delay(1000); // This introduces a little pause in each cycle. Probably helps save some power.
}

// The callback function is defined above. New MQTT messages are handed to this function.
void callback(char *topicChar, byte *payload, unsigned int length)
{
  String topic = (String)topicChar; // Convert the char* to a String
  String message = "";              // Convert the byte* payload to String
  // There won't be a null character to terminate, so we manually copy each character
  for (int i = 0; i < length; i++)
  {                              // For each character of the payload
    message += (char)payload[i]; // append to the message string
  }

  Serial.print("Message arrived ["); // Serial Debug
  Serial.print(topic);               //    Print the topic name [in brackets]
  Serial.print("] ");                //
  Serial.println(message);           //    And the message

  if (topic == (String)relayTopic)
  {   

    if (message == "relay_on")
    {
        digitalWrite(RELAY, HIGH);
    }
    else if (message == "relay_off")
    {
        digitalWrite(RELAY, LOW);
    }
  }
}
