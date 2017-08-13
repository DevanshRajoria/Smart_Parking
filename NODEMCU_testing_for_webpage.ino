#include<ESP8266WiFi.h>
#include<ESP8266HTTPClient.h>

HTTPClient http;

WiFiServer server(80);

char* ssid     = "***";
char* password = "**";

String  i;
uint8_t  NewVar,ledpin = 16;
String  httpurl;
String  AnswerOfClient;

String SendWithAnswer(String IP) 
{
  httpurl = "http://";
  httpurl+=IP;
  httpurl+="/park/create/1000"; //"/zyro/1.html/1.html";
  http.begin(httpurl);
  http.GET();
  AnswerOfClient = (http.getString());
  http.end();
  return AnswerOfClient;
}

void setup()
{
  i = "";
  pinMode(ledpin,OUTPUT);
  Serial.begin(115200);
  WiFi.begin(ssid,password);

   while(WiFi.status() != WL_CONNECTED)
  {
    Serial.println("..");
    delay(500); 
  }
  Serial.println("IP : ");
  Serial.print(WiFi.localIP());
  delay(100);

  server.begin();  
}


String request = "";

void loop()
{
  WiFiClient client = server.available();
  i = SendWithAnswer("harshnigm.pythonanywhere.com");

  Serial.println(i);
  
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");                           //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  
  client.println("<HTML>");
  client.println("hello world");
  
  client.println(i);
  client.println("</HTML>");
 
}

