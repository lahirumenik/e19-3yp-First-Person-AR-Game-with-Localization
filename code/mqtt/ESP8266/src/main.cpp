#include <ESP8266WiFi.h>
#include <PubSubClient.h>
 
const char* SSID = "Dasun's Galaxy M21";    // WiFi name
const char* PASSWORD =  "sise9444";         // WiFi password
const char* ID = "nodemcu01";               // Device ID
const char* TOPIC = "node/nodemcu01";
const char* NODESTATUS = "node/status";
const char* mqttServer = "192.168.182.122"; // Broker IP
const int mqttPort = 1883;                  // Broker port

int OB_LED = 16;        // Assign LED1 to pin GPIO2
int MQTT_LED = 2;    // Assign LED1 to pin GPIO16

int ob_sts = HIGH; 

unsigned long lasttime = 0;

// const char* mqttUser = "otfxknod";
// const char* mqttPassword = "nSuUc1dDLygF";
 
WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (unsigned int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  ob_sts = LOW;
}

void wifi_connect(){
  WiFi.begin(SSID, PASSWORD);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void mqtt_connect() {
  digitalWrite(MQTT_LED, LOW);

  // while (!client.connected()) {
    if (client.connect(ID)) {
      digitalWrite(MQTT_LED, HIGH);

      client.publish(NODESTATUS, ID); // Update Node Status
      client.subscribe(TOPIC);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 500 miliseconds");
      delay(500);
    }
  // }
}
 
void setup() {
 
  Serial.begin(115200);

  // initialize GPIO2 and GPIO16 as an output
  pinMode(OB_LED, OUTPUT);
  pinMode(MQTT_LED, OUTPUT);

  digitalWrite(OB_LED, HIGH);
  digitalWrite(MQTT_LED, LOW);

  // delay(500);
 
  wifi_connect();
 
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
 
  mqtt_connect();

}
 
void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    wifi_connect();
  }
  if (!client.connected()) {
    mqtt_connect();
  }else{
    client.loop();

    unsigned long now = millis();
    if (now - lasttime > 1000) {
      lasttime = now;
      client.publish(NODESTATUS, ID);
      digitalWrite(OB_LED, ob_sts);
      digitalWrite(MQTT_LED, LOW);
    }
    if (now - lasttime > 500) {
      digitalWrite(OB_LED, HIGH);
      digitalWrite(MQTT_LED, HIGH);
    }
  }
}