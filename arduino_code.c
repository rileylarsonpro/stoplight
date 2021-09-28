#include <ESP8266WiFi.h>              // This includes the libraries to connect to wifi and start a server

//const char* wifiSSID = "BYU-WiFi";    // In order for this to work, you MUST specify the SSID for your wifi
const char* wifiSSID = "Riley BYU";
const char* wifiPSK  = "darkesttimeline";            // And the preshared key (wifi password)

WiFiServer server(80);                // This sets which port our server will listen on

int RED = D7;                       // Sets which GPIO pin we will use for the LEDS
int YELLOW = D6;  
int GREEN = D5;    
boolean redState = false;            // Tracks state of LEDS
boolean yellowState = false;
boolean greenState = false;

unsigned long timer1 = 0;
unsigned long timer2 = 0;
unsigned long timer3 = 0;
boolean autoState = false;

//Helper function to turn all lights off
void allOff() {
      Serial.println("all off called");
      autoState = false;
      digitalWrite(GREEN, LOW);             
      greenState = false;                    
      digitalWrite(RED, LOW);                       
      redState = false;
      digitalWrite(YELLOW, LOW);
      yellowState = false; 
    return;
}

void setup() {                        // Perform this part once when first powered on
  Serial.begin(9600);               // Open a serial connection (for debugging)
  delay(10);                          // Wait 10 milliseconds (1/100th of a second)
  Serial.println("Initializing ..."); // DEBUG CODE

  pinMode(RED, OUTPUT);            // Set the LED pin to Output
  digitalWrite(RED, LOW);          // Set the pin to LOW (Off)

  pinMode(YELLOW, OUTPUT);            // Set the LED pin to Output
  digitalWrite(YELLOW, LOW);          // Set the pin to LOW (Off)

  pinMode(GREEN, OUTPUT);            // Set the LED pin to Output
  digitalWrite(GREEN, LOW);          // Set the pin to LOW (Off)


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

  server.begin();                           // Start the web server
  Serial.println("Server started");

  Serial.print("Control the LED Stoplight at: ");          // Print the connected IP address to the Serial Monitor
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
} // ** End Adapted Code - This is the end of the code that was adapted from www.esp8266learning.com


void loop() { // ** Create a web server - Adapted from https://github.com/todddb/example-lab/blob/master/example-lab/example-lab.ino
  WiFiClient client = server.available(); // Create a new client object for available connections
  if (client) {                           // If a client is connected, wait until it sends some data
    while (!client.available()) {         // If the client hasn't sent info, wait for it
      delay(10);
    }

    String request = client.readStringUntil('\r');  // read the first line of the request
    Serial.println(request);              // DEBUG CODE - Echo the request to the Serial Monitor for debug
    client.flush();                       // Wait until the buffers are clear

    if (request.indexOf("/red_on") != -1) {   // If the request is for the page "/red_on"
      autoState = false;
      digitalWrite(RED, !redState);             //   then set the RED to high (turn on)
      redState = !redState;                        //   and track the state 
      
      digitalWrite(YELLOW, LOW);                //Turn off other lights
      yellowState = false;
      digitalWrite(GREEN, LOW); 
      greenState = false;
    }
    if (request.indexOf("/yellow_on") != -1) {   // If the request is for the page "/yellow_on"
      autoState = false;
      digitalWrite(YELLOW, !yellowState);             //   then set the YELLOW to high (turn on)
      yellowState = !yellowState;                       //   and track the state
      
      digitalWrite(RED, LOW);             //Turn off other lights
      redState = false;
      digitalWrite(GREEN, LOW); 
      greenState = false;
    }
    if (request.indexOf("/green_on") != -1) {   // If the request is for the page "/green_on"
      autoState = false;
      digitalWrite(GREEN, !greenState);             //   then set the GREEN to high (turn on)
      greenState = !greenState;                        //   and track the state  
      
      digitalWrite(RED, LOW);                       //Turn off other lights
      redState = false;
      digitalWrite(YELLOW, LOW);
      yellowState = false; 
    }
    if (request.indexOf("/all_off") != -1) {   // If the request is for the page "/all_off"
      allOff();
    }

 
    // ** End Adapted Code - This is the end of the code that was adapted from https://github.com/todddb/example-lab/blob/master/example-lab/example-lab.ino
     if (request.indexOf("/auto") != -1) {   // If the request is for the page "/auto"
      allOff();
      autoState = true;
     }
     
     
 
    // Return the html page
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    client.println("    <!-- Base File from https://codepen.io/BendyWendy/pen/pbyxxz -->");
    client.println("<!DOCTYPE html>");
    client.println("<html>");

    client.println("<head>");
    client.println("    <title> Riley's Stoplight </title>");
    client.println("    <!-- Links to stylesheets -->");
    client.println("    <link href=\"https://fonts.googleapis.com/icon?family=Material+Icons\" rel=\"stylesheet\">");

    client.println("    <!-- Link to Bootstrap-->");
    client.println("    <link rel=\"stylesheet\" href=\"https://stackpath.bootstrapcdn.com/bootstrap/4.5.0/css/bootstrap.min.css\"");
    client.println("        integrity=\"sha384-9aIt2nRpC12Uk9gS9baDl411NQApFmC26EwAOH8WgZl5MYYxFfc+NcPb1dKGj7Sk\" crossorigin=\"anonymous\">");

    client.println("    <!-- Custom style sheet-->");
    client.println("    <style>");
    client.println("        /* Base File from https://codepen.io/BendyWendy/pen/pbyxxz */");
    client.println("        * {");
    client.println("            margin: 20px auto;");
    client.println("        }");
            
    client.println("        div {");
    client.println("            margin-bottom: 0px;");
    client.println("        }");
            
    client.println("        p {");
    client.println("            text-align: center;");
    client.println("            padding: 40px 0px 0px 10px;");
    client.println("            font-family: helvetica;");
    client.println("        }");
            
    client.println("        .Red {");
    client.println("            width: 100px;");
    client.println("            height: 100px;");
    client.println("            background: #FF0000;");
    client.println("            -moz-border-radius: 50px;");
    client.println("            -webkit-border-radius: 50px;");
    client.println("            border-radius: 50px;");
    client.println("            cursor: pointer;");
    client.println("        }");
            
    client.println("        .Yellow {");
    client.println("            width: 100px;");
    client.println("            height: 100px;");
    client.println("            background: #FFFF00;");
    client.println("            -moz-border-radius: 50px;");
    client.println("            -webkit-border-radius: 50px;");
    client.println("            border-radius: 50px;");
    client.println("            cursor: pointer;");
    client.println("        }");
            
    client.println("        .Green {");
    client.println("            width: 100px;");
    client.println("            height: 100px;");
    client.println("            background: #00FF00;");
    client.println("            -moz-border-radius: 50px;");
    client.println("            -webkit-border-radius: 50px;");
    client.println("            border-radius: 50px;");
    client.println("            cursor: pointer;");
    client.println("        }");
            
    client.println("        .rectangle {");
    client.println("            width: 200px;");
    client.println("            height: 400px;");
    client.println("            background: #000000;");
    client.println("            position: absolute;");
    client.println("            top: 0;");
    client.println("            left: 0;");
    client.println("            right: 0;");
    client.println("            z-index:-1;");
    client.println("        }");
            
            
            
            
    client.println("    </style>");

    client.println("</head>");

    client.println("<body>");

    client.println("    <div class=\"Red\" onclick=\"redClicked()\"> </div>");

    client.println("    <div class=\"Yellow\" onclick=\"yellowClicked()\"> </div>");

    client.println("    <div class=\"Green\" onclick=\"greenClicked()\"> </div>");
        
    client.println("    <div class=\"Pole\"> </div>");

    client.println("    <div class=\"rectangle\"> </div>");

    client.println("    <div class=\"overlay\"> </div>");
    client.println("    <br>");
    client.println("    <br>");
    client.println("    <div class=\"container text-center\">");
    client.println("        <button type=\"button\" class=\"btn btn-secondary\" onclick=\"allOff()\">All Off</button>");
    client.println("        <button id=\"auto-btn\" type=\"button\" class=\"btn btn-secondary\" onclick=\"auto()\">Automatic</button>");
    client.println("        <button id=\"manual-btn\" type=\"button\" class=\"btn btn-secondary\" onclick=\"allOff()\">Manual</button>");
    client.println("    </div>");
    client.println("    <!-- Links to scripts -->");
    client.println("    <script src=\"https://code.jquery.com/jquery-3.5.1.slim.min.js\"");
    client.println("        integrity=\"sha384-DfXdz2htPH0lsSSs5nCTpuj/zy4C+OGpamoFVy38MVBnE+IbbVYUew+OrCXaRkfj\"");
    client.println("        crossorigin=\"anonymous\"></script>");
    client.println("    <script src=\"https://cdn.jsdelivr.net/npm/popper.js@1.16.0/dist/umd/popper.min.js\"");
    client.println("        integrity=\"sha384-Q6E9RHvbIyZFJoft+2mJbHaEWldlvI9IOYy5n3zV9zzTtmI3UksdQRVvoxMfooAo\"");
    client.println("        crossorigin=\"anonymous\"></script>");
    client.println("    <script src=\"https://stackpath.bootstrapcdn.com/bootstrap/4.5.0/js/bootstrap.min.js\"");
    client.println("        integrity=\"sha384-OgVRvuATP1z7JjHLkuOU7Xw704+h835Lr+6QL9UvYjZE3Ipu6Tp75j7Bh/kR0JKI\"");
    client.println("        crossorigin=\"anonymous\"></script>");

    client.println("    <!--Custom JS file-->");
    client.println("    <script>");
    client.print("const RPI_IP = \"");
    client.print(WiFi.localIP());
    client.println("\"");
    client.println("        document.getElementById(\"auto-btn\").hidden = " + (String)autoState);
    client.println("        document.getElementById(\"manual-btn\").hidden = " + (String)!autoState);
    client.println("        function redClicked() {");
    client.println("            manual()");
    client.println("            var xhr = new XMLHttpRequest();");
    client.println("            xhr.open(\"GET\", \"http://\" + RPI_IP + \"/red_on\");");
    client.println("            xhr.send()");
    client.println("        }");
    client.println("        function yellowClicked() {");
    client.println("            manual()");
    client.println("            var xhr = new XMLHttpRequest();");
    client.println("            xhr.open(\"GET\", \"http://\" + RPI_IP + \"/yellow_on\");");
    client.println("            xhr.send()");
    client.println("        }");
    client.println("        function greenClicked() {");
    client.println("            manual()");
    client.println("            var xhr = new XMLHttpRequest();");
    client.println("            xhr.open(\"GET\", \"http://\" + RPI_IP + \"/green_on\");");
    client.println("            xhr.send()");
    client.println("        }");
    client.println("        function allOff() {");
    client.println("            manual()");
    client.println("            var xhr = new XMLHttpRequest();");
    client.println("            xhr.open(\"GET\", \"http://\" + RPI_IP + \"/all_off\");");
    client.println("            xhr.send()");
    client.println("        }");
    client.println("        // Start auto mode and show manual button");
    client.println("        function auto() {");
    client.println("            var xhr = new XMLHttpRequest();");
    client.println("            xhr.open(\"GET\", \"http://\" + RPI_IP + \"/auto\");");
    client.println("            xhr.send()");
    client.println("            document.getElementById(\"auto-btn\").hidden = true;");
    client.println("            document.getElementById(\"manual-btn\").hidden = false;");
    client.println("        }");
    client.println("        function manual() {");
    client.println("        // Show Automatic button");
    client.println("            document.getElementById(\"auto-btn\").hidden = false;");
    client.println("            document.getElementById(\"manual-btn\").hidden = true;");
    client.println("        }");
    client.println("    </script>");
    client.println("</body>");

    client.println("</html>");
  }
  
       if (autoState == true){ // run if auto is turned on
        if(millis() > timer3) {
          timer1 = millis() + 2000;
          timer2 = millis() + 4000;
          timer3 = millis() + 5000;
        }
        if (timer1 > millis()) {
          Serial.println("in loop 1 :");
          Serial.println(timer1);
          Serial.println(millis());
          digitalWrite(YELLOW, LOW);  
          yellowState = false;
          digitalWrite(RED, HIGH);  
          redState = true;
        }
        if (timer2 > millis() && millis() > timer1) {
          Serial.println("in loop 2 :");
          Serial.println(timer2);
          digitalWrite(RED, LOW); 
          redState = false; 
          
          digitalWrite(GREEN, HIGH);  
          greenState = true;
        }
        if (timer3 > millis() && millis() > timer2) {
         Serial.println("in loop 3 :");
          Serial.println(timer3);
          digitalWrite(GREEN, LOW); 
          greenState = false; 
          digitalWrite(YELLOW, HIGH);  
          yellowState = true;
        }
      }
  delay(100); // This introduces a little pause in each cycle. Probably helps save some power.
}
