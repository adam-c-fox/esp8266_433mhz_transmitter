#include <RCSwitch.h>
#include <PubSubClient.h>
#include "ESP8266WiFi.h"
#include "secrets.h"
#define DHTPIN 2  //DHT11 digital pin
#define DHTTYPE DHT11

WiFiClient wifiClient;
PubSubClient client(mqtt_server, mqtt_port, wifiClient);
RCSwitch mySwitch = RCSwitch();

void callback(char* topic, byte* payload, unsigned int length) {
 Serial.print("Message arrived [");
 Serial.print(topic);
 Serial.print("] ");

 String topicStr = topic;
 String received;
 for (int i=0;i<length;i++) {
  received = received + (char)payload[i];
  }

  if (topicStr.equals("433transmitter/rfcode")) {
    transmit(received.toInt());
  }
  else {
    Serial.println("error, topic not recognised");
  }
  
  Serial.println();
}

void setup() {
  Serial.begin(115200);
  Serial.println("MQTT based 433Mhz Transmitter \n");

  wifiConnect();
  mqttConnect();
  
  client.subscribe("433transmitter/rfcode");
  client.setCallback(callback);
  mySwitch.enableTransmit(0); //argument is pin
}

void loop() {
  
  if (!client.connected()) {
  wifiConnect();
  }
  client.loop();

}

void transmit(int code) {
  mySwitch.send(code, 24);
  Serial.println("Code sent: " + code);
}

void wifiConnect() {
  Serial.begin(115200);
  Serial.print("Connecting to ");
  Serial.println(wifi_ssid);  
  WiFi.begin(wifi_ssid, wifi_password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void mqttConnect() {
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Connecting to MQTT server");
      if (client.connect(mqtt_client_name)) {
        Serial.println("Connected to MQTT server");
      } else {
        Serial.println("Could not connect to MQTT server");   
      }
  }
}
