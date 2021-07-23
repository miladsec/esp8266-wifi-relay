#include <ESP8266WiFi.h>
 
const char* ssid = "ca";
const char* password = "1234567899";

IPAddress ip(192, 168, 1, 85); 
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0); 

int relayPin = D5;
WiFiServer server(85);
 
void setup() {
  Serial.begin(9600);
  delay(10);
 
 
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
 // Configures static IP address
  WiFi.config(ip, gateway, subnet);
  
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");


 WiFi.softAP("HACK ME!!!", ")*#)*$&#@)*(%U)#@U(*HIHG");
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");

  unsigned long timeout = millis();
  while(!client.available()){
    if (millis() - timeout > 10) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
  if (request.indexOf("/open") != -1) {
    digitalWrite(relayPin, LOW);
    delay(500);
    digitalWrite(relayPin, HIGH);
  } 
 
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head>");
  client.println("<meta charset='utf-8'>");
  client.println("<meta name='viewport' content='width=device-width, initial-scale=1'>");
  client.println("<link href='https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css' rel='stylesheet' integrity='sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC' crossorigin='anonymous'>");
  client.println("<title>FBI open up!</title>");
  client.println("</head>");
  client.println("<body>");
  client.println("<div class='container'><div class='row'><div class='col-12 text-center'>");
  client.println("<p style='margin-top: 30px;color: red; font-size: 20px'>درب باز کن هوشمند</p>");
  client.println("<div><img src='https://www.nicepng.com/png/detail/82-822081_door-open-door.png' height='100px' alt=''></div>");
  client.println("<div><a style='margin-top: 30px' href='/open' class='btn btn-success'>باز کردن درب</a></div>");
  client.println("</div></div></div>");
  client.println("</body>");
 
  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
 
}
