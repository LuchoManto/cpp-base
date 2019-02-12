#include <WiFi.h>
#include <PubSubClient.h>
 
const char* ssid = "Hobbiton";
const char* password =  "20025bombita";
const char* mqttServer = "m16.cloudmqtt.com";
const int mqttPort = 19658;
const char* mqttUser = "qwxrmrsh";
const char* mqttPassword = "k7-aY3Ao1Q2t";
 
WiFiClient espClient;
PubSubClient client(espClient);
 
void setup() {
 
  Serial.begin(115200);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
 
  client.setServer(mqttServer, mqttPort);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP32Client", mqttUser, mqttPassword )) {
 
      Serial.println("connected");
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }
 
  client.publish("esp/test", "Hello from ESP32");
 
}
 
void loop() {
  client.loop();
}
