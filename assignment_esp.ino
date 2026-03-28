#include <WiFi.h>
#include <PubSubClient.h>

#define RXD2 16
#define TXD2 17

const char* ssid = "Revati";
const char* passwd = "11062003";
const char* mqtt_server = "broker.emqx.io";

WiFiClient espClient;
PubSubClient client(espClient);

void setup_WiFi()
{
  // Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, passwd);

  int attempts = 0;

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    // Serial.print(".");
    attempts++;

    if (attempts > 20)
    {
      // Serial.println("\nFailed to connect!");
      // Serial.print("Status: ");
      // Serial.println(WiFi.status());
      break;
    }
  }

  if (WiFi.status() == WL_CONNECTED)
  {
    // Serial.println("\nWiFi connected");
    // Serial.println(WiFi.localIP());
  }
}



void callback(char* topic, byte* payload, int length)
{
  String msg = "";

  for (int i = 0; i < length; i++)
  {
    msg += (char)payload[i];
  }

  msg.trim();

  Serial.println("Received: " + msg);

  Serial2.println(msg);   
}

void reconnect()
{
  while (!client.connected())
  {
    Serial.print("Connecting to MQTT...");
    String clientId = "ESP32_" + String(random(10000));
  

    if (client.connect(clientId.c_str()))
    {
      Serial.println("connected");
      client.subscribe("revati/epicure/commands");
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" retrying in 2 sec");
      delay(2000);
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial2.begin(115200,SERIAL_8N1,RXD2,TXD2);

  setup_WiFi();
  client.setServer(mqtt_server,1883);
  client.setCallback(callback);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(!client.connected())
  {
    reconnect();
  }
  client.loop();
  // Serial2.println("HELLO");
  // delay(1000);
}
