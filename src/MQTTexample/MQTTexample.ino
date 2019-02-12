#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Iphone de Lucho";
const char* password =  "lucho1231";
//const char* ssid = "MLM";
//const char* password =  "12365390aa";
const char* mqttServer = "11mltech.com";
const int mqttPort = 1883;
const char* mqttUser = "daniel";
const char* mqttPassword = "daml1477";
 
WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");


  payload[length] = NULL;
  Serial.print(String((char*)payload));
  Serial.println();

  if(!strcmp(topic,"esp/led")){
    pinMode(LED_BUILTIN,OUTPUT);
    if (!strcmp((char*)payload,"turn led on"))
        digitalWrite(LED_BUILTIN,HIGH);
    else if (!strcmp((char*)payload,"turn led off"))
        digitalWrite(LED_BUILTIN,LOW);
  }
}



void connectWifi() {
  Serial.print("checking wifi...");
  int count = 0;
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
    if (count == 15){
      WiFi.begin(ssid, password);
      count = 0;
      Serial.println();
      Serial.print("Retrying connection...");
      delay(5000);
    }
    Serial.println(WiFi.status());
    count ++;
  }

  Serial.println("Connected to the WiFi network");
}

void connectMQTT(){
   
    client.setServer(mqttServer, mqttPort);
    client.setCallback(callback);
  
    while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP32Client",         //client ID
                       mqttUser,              //client user name
                       mqttPassword,          //client password
                       "esp/will",            //will topic
                       0,                     //will QoS
                       0,                     //will retain
                       "esp32 disconnected",  //will message
                       false )) {             //clean_session
 
      Serial.println("connected");
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }
  
}
 
void setup() {
 
  esp_log_level_set("*", ESP_LOG_VERBOSE);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
 
  connectWifi();
  connectMQTT();

  
  client.publish("esp/test", "Hello!");
  client.subscribe("esp/talk",1);
  client.subscribe("esp/led",1);
 
}
 
void loop() {
  client.loop();

  if(WiFi.status() != WL_CONNECTED){
    connectWifi();
    connectMQTT();
  }
}
