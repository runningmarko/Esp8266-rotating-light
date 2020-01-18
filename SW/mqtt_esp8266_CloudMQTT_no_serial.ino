#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "";
const char* password =  "";
const char* mqttServer = "";
const int mqttPort =  ;
const char* mqttUser = "";
const char* mqttPassword = "";

const int ledPin =  D2;
const int piezoPin =  D1;
WiFiClient espClient;
PubSubClient client(espClient);

void setup() {

  pinMode(ledPin, OUTPUT);
  pinMode(piezoPin, OUTPUT);
 // Serial.begin(115200);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //Serial.println("Connecting to WiFi..");
  }
  //Serial.println("Connected to the WiFi network");

  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  while (!client.connected()) {
    //Serial.println("Connecting to MQTT...");

    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {

  //    Serial.println("connected");

    } else {
//
//      Serial.print("failed with state ");
//      Serial.print(client.state());
      delay(2000);

    }
  }

  client.publish("esp/test", "Hello from ESP8266");
  client.subscribe("esp/test");

}

void callback(char* topic, byte* payload, unsigned int length) {
  digitalWrite(ledPin, HIGH);
  delay(7000);
  digitalWrite(ledPin, LOW);
}

void loop() {
  client.loop();
}
