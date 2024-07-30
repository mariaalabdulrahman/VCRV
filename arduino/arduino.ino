#include <ESP8266WebServer.h>

long duration;
int distance;

const char* ssid = "wifi name";
const char* password = "wifi pass";
const int port = 5000;
const int trigP = D5;  
const int echoP = D4;  
const int MA1 = D3;    
const int MA2 = D2;  
const int MB1 = D1;    
const int MB2 = D0;  

ESP8266WebServer server(port);

IPAddress myIP;  // Variable to store ESP's IP address

void setup() {
  Serial.begin(115200);
   
  pinMode(trigP, OUTPUT);  
  pinMode(echoP, INPUT);  
  pinMode(MA1, OUTPUT);
  pinMode(MA2, OUTPUT);
  pinMode(MB1, OUTPUT);
  pinMode(MB2, OUTPUT);
 
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
  myIP = WiFi.localIP();  // Get ESP's IP address
  Serial.print("ESP8266 IP Address: ");
  Serial.println(myIP);
  server.begin();
  Serial.println("Server started");

  setupHandlers();
}

void loop() {
  server.handleClient();
  // Serial.println("Waiting for request");
  digitalWrite(trigP, LOW);   // Makes trigPin low
  delayMicroseconds(2);       // 2 micro second delay
 
  digitalWrite(trigP, HIGH);  // tigPin high
  delayMicroseconds(10);      // trigPin high for 10 micro seconds
  digitalWrite(trigP, LOW);   // trigPin low
 
  duration = pulseIn(echoP, HIGH);   //Read echo pin, time in microseconds
  distance= duration*0.034/2;        //Calculating actual/real distance
 
  Serial.print("Distance = "); Serial.print(distance); Serial.println("cm");
  delay(1000);
}

void moveForward(){
  if (server.method() == HTTP_GET) {
    String message = "";
    message += myIP.toString();
    server.send(200, "text/plain", message);
  }
  Serial.println("Move Forward function not implemented");

  digitalWrite(MA1,HIGH);
  digitalWrite(MA2,LOW);
  digitalWrite(MB1,HIGH);
  digitalWrite(MB2,LOW);  
}

void moveBackward(){
  if (server.method() == HTTP_GET) {
    String message = "";
    message += myIP.toString();
    server.send(200, "text/plain", message);
  }
  Serial.println("Move Backward ma friend");

  digitalWrite(MA1,LOW);
  digitalWrite(MA2,HIGH);
  digitalWrite(MB1,LOW);
  digitalWrite(MB2,HIGH);
}

void moveRight(){
  if (server.method() == HTTP_GET) {
    String message = "";
    message += myIP.toString();
    server.send(200, "text/plain", message);
  }
  Serial.println("Move Right dude");

  digitalWrite(MA1,HIGH);
  digitalWrite(MA2,LOW);
  digitalWrite(MB1,LOW);
  digitalWrite(MB2,HIGH);
}

void moveLeft(){
  if (server.method() == HTTP_GET) {
    String message = "Hello from ESP8266 server! My IP is: ";
    message += myIP.toString();
    server.send(200, "text/plain", message);
  }
  Serial.println("Moving left yoooo");

  digitalWrite(MA1,LOW);
  digitalWrite(MA2,HIGH);
  digitalWrite(MB1,HIGH);
  digitalWrite(MB2,LOW);  
}

void stobbit(){
  if (server.method() == HTTP_GET) {
    String message = "Hello from ESP8266 server! My IP is: ";
    message += myIP.toString();
    server.send(200, "text/plain", message);
  }
  Serial.println("Stobbing brudda");

  digitalWrite(MA1,LOW);
  digitalWrite(MA2,LOW);
  digitalWrite(MB1,LOW);
  digitalWrite(MB2,LOW);
}

void setupHandlers() {
  Serial.println("Setting up handlers");
  server.on("/forward", moveForward);
  server.on("/backward", moveBackward);
  server.on("/right", moveRight);
  server.on("/left", moveLeft);
  server.on("/stop", stobbit);
}