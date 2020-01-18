#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "***";
const char* password =  "***";
const char* mqttServer = "***";
const int mqttPort =  ***;
const char* mqttUser = "***";
const char* mqttPassword = "***";

const int ButtonPin =  D2;
//const int piezoPin =  D1;

WiFiClient espClient;
PubSubClient client(espClient);
int button_old = 0;

void setup() {

  pinMode(ButtonPin, INPUT);
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
      //      Serial.print("failed with state ");
      //      Serial.print(client.state());
      delay(2000);

    }
  }

  client.publish("esp/test", "Reset... Start -->");
  client.subscribe("esp/test");

}

void callback(char* topic, byte* payload, unsigned int length) {
  delay(1000);
}

void loop() {
  client.loop();
  if (digitalRead(ButtonPin) && button_old == 0)
  {
    client.publish("esp/test", "ALARM!");
    delay(1000);
    button_old = 1;
  }
  if (digitalRead(ButtonPin) == 0) button_old = 0;
}
