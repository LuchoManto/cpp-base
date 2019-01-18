#include <WiFi.h>
#include <PubSubClient.h>
 
const char* ssid = "Hobbiton";
const char* password =  "200525bombita";
const char* mqttServer = "m16.cloudmqtt.com";
const int mqttPort = 19658;
const char* mqttUser = "qwxrmrsh";
const char* mqttPassword = "k7-aY3Ao1Q2t";
 
WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
//  int i=0;
//  for (i=0;i<length;i++) {
//    Serial.print((char)payload[i]);
//  }
  payload[length] = NULL;
  Serial.print(String((char*)payload));
  Serial.println();
 // payload[i-1] = NULL;  // adds null terminating to payload to enable String comparison 

  if(!strcmp(topic,"esp/led")){
    pinMode(LED_BUILTIN,OUTPUT);
    if (!strcmp((char*)payload,"turn led on"))
        digitalWrite(LED_BUILTIN,HIGH);
    else if (!strcmp((char*)payload,"turn led off"))
        digitalWrite(LED_BUILTIN,LOW);
  }
}
 
void setup() {
 
  Serial.begin(115200);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
 
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
 
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
  client.subscribe("esp/talk");
  client.subscribe("esp/led");
 
}
 
void loop() {
  client.loop();
}
