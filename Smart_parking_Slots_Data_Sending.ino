#include<ESP8266WiFi.h>
#include<ESP8266HTTPClient.h>

HTTPClient http;          //  http object of HTTPClient class 

WiFiServer server(80);    //  Default Server
WiFiClient client = server.available();

// IR Sensor Slot No. Placement
int ir_slot1 = 5;     
int ir_slot2 = 4;

// Led 
int ledpin = 16;

char* ssid = "Redmi";     // ssid of your WiFi
char* password = "shivam1234";    // password of your WiFi

String httpurl;
String AnswerOfClient;

String SendWithMessage(String IP,String url){
  httpurl = "http://";
  httpurl += IP;
  httpurl += url;
  httpurl += "/";  
  http.begin(httpurl);
  http.GET();
  AnswerOfClient = (http.getString());
  http.end();
  return AnswerOfClient;    
}

void setup() {
  // Pin Mode Declaration of IR sensor
  pinMode(ir_slot1,INPUT);
  pinMode(ir_slot2,INPUT);

  // Pin Declaration of LED
  pinMode(ledpin,OUTPUT);
  
  // ESP8266 checking the WiFi ssid and password
  WiFi.begin(ssid,password);
  Serial.begin(115200);
  
  while(WiFi.status() != WL_CONNECTED){
    Serial.println(".");
    delay(400);
  }

  Serial.println("Connected");
  Serial.println(WiFi.localIP());   // Our localIP of ESP8266 provided by the router
  delay(100);

  server.begin();

}

String host = "harshnigm.pythonanywhere.com";     // Testing Website
String stream_id = "/park/create/";
String save_request = "";
String request = "";

String sendIR = "";
String sendURI = "";
String prev_request = "";
boolean temp  = false;

void loop() {

  // Reading the sensors in the Slots
  int ir1 = digitalRead(ir_slot1);
  int ir2 = digitalRead(ir_slot2);
  int ir3 = 0;
  int ir4 = 0;

  sendIR = String(ir1) + String(ir2) + String(ir3) + String(ir4);
  sendURI = stream_id + sendIR;
  
  if(temp == false){
    temp = true;
    prev_request = sendIR;
    save_request = SendWithMessage(host,sendURI);
  }

  else if(prev_request == sendIR){
    // Do nothing 
  }

  else{
    prev_request = sendIR;
    save_request = SendWithMessage(host,sendURI);
  }
  
}

// This function is for verification of the received data from the webserver 
void PrintOnMyLocalIP(String i){

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");                           //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  
  client.println("<HTML>");
  client.println("hello world");
  
  client.println(i);                            // The data from the webserver
  client.println("</HTML>");
 
  Serial.println(i);
 
}
