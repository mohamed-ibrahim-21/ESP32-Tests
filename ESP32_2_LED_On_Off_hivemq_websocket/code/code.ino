/***********************includes**************************************/
#include <WiFi.h> //use for wifi setup
#include <WiFiClient.h> //use for wifi setup
#include <WebServer.h>
#include <uri/UriBraces.h>
#include <PubSubClient.h> //use for mqtt setup
/***********************Micro**************************************/
#define LED 5
/*********************WIFI (user_name & password)********************/
#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASSWORD ""
/******************wifi setup function*****************************/
void WiFi_setup(){
  delay(100);
  Serial.print("\nConnecting to :- ");
  Serial.println(WIFI_SSID);

  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);

  while(WiFi.status() != WL_CONNECTED){
    delay(100);
    Serial.print(".");
  }

  Serial.print("\nConnected to :- ");
  Serial.println(WIFI_SSID);
}
/***********************MQTT**************************************/
#define mqttServer "mqtt-dashboard.com"
// const char* mqttUserName = "bqzbdodo";
// const char* mqttPwd = "5oU2W_QN2WD8";
#define clientID "nnUwnjr8HP" // Client ID username+0001
const char* topic = "Tempdata"; // Publish topic
// Setting up WiFi and MQTT client
WiFiClient espClient;
PubSubClient client(espClient);
/*********************mqtt setup function*************************/
void reconnect() {
  while (!client.connected()) {
    if (client.connect(clientID)) {
      Serial.println("MQTT connected");
      client.subscribe("lights");
      Serial.println("Topic Subscribed");
    }
    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);  // wait 5sec and retry
    }
  }
}

/*****************************call back*****************************/
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message: ");
  String data = "";
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    data += (char)payload[i];
  }
  Serial.println();
  Serial.print("Message size: ");
  Serial.println(length);
  Serial.println();
  Serial.println("-----------------------");
  Serial.println(data);

  if (String(topic) == "lights") {
    if (data == "ON") {
      Serial.println("LED");
      digitalWrite(LED, HIGH);
    }
    else {
      digitalWrite(LED, LOW);
    }
  }
}
/**********************setup*****************************************/
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  WiFi_setup();
  client.setServer(mqttServer, 1883); // Setting MQTT server
  client.setCallback(callback);
}
/*******************************loop***********************************/
void loop() {
  if (!client.connected()) { // If client is not connected
    reconnect(); // Try to reconnect
  }
  //client.publish("lights", "Hello from ESP32");
  client.loop();
}
