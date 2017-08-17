
#include<ESP8266WiFi.h>
#include<ESP8266HTTPClient.h>

HTTPClient http;          //  http object of HTTPClient class 

WiFiServer server(80);    //  Default Server
WiFiClient client = server.available();

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

String host =  "www.google.com";
String stream_id = "";


int i,j;
int point1;
int point2;
String save_request = "";
String str = "";
String temp = "";


void setup() {
  
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

  save_request  = SendWithMessage(host,stream_id);

  Serial.println(save_request);
  
  str = save_request;
  for(i=0;i<str.length();i++){
    if(str[i] == '<' && str[i+1] == 'B' && str[i+2] == 'O' && str[i+3] == 'D' && str[i+4] == 'Y' && str[i+5] == '>'){
      point1 = i+6;
    }
  }
  for(i=0;i<str.length();i++){
    if(str[i] == '<' && str[i+1] == '/' && str[i+2] == 'B' && str[i+3] == 'O' && str[i+4] == 'D' && str[i+5] == 'Y' && str[i+6] == '>'){
      point2 = i;
    }
  }

  for(i=point1;i<point2;i++){
    temp = temp + str[i];
  }

  Serial.println(temp); 
}


void loop() {
  // put your main code here, to run repeatedly:

}
