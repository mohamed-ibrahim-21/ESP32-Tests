/***********************includes**************************************/
#include <WiFi.h> //use for wifi setup
#include <WiFiClient.h> //use for wifi setup
#include "ESP32Firebase.h"
/********************macro********************************************/
#define led 5
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


/********************firebase****************************************/
#define fire_base_host "https://drone-test-d3dfd-default-rtdb.firebaseio.com/"
Firebase firebase(fire_base_host);



void setup() {
  
  Serial.begin(115200);
  WiFi_setup();
  pinMode(led, OUTPUT);
}

void loop() {

  String data1 = firebase.getString("Example/setString");
  Serial.print("Received String:\t");
  Serial.println(data1);

  if(data1 == "ON"){
    delay(10);
    digitalWrite(led, HIGH);
  }
  else{
    delay(10);
    digitalWrite(led, LOW);
  }
}
