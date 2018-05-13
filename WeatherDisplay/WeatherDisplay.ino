#include <LiquidCrystalFast.h>
#include <ESP8266MQTTClient.h>
#include <ESP8266WiFi.h>
MQTTClient mqtt;
const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.begin("ssid", "pass");
  lcd.begin(20, 4);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //topic, data, data is continuing
  mqtt.onData([](String topic, String data, bool cont) {
    Serial.print(data);
    lcd.clear();
    lcd.print(data);
  });
  mqtt.onConnect([]() {
    mqtt.subscribe("/Weather", 2);
  });

  mqtt.begin("mqtt://test.mosquitto.org:1883");
  //  mqtt.begin("mqtt://test.mosquitto.org:1883", {.lwtTopic = "hello", .lwtMsg = "offline", .lwtQos = 0, .lwtRetain = 0});
  //  mqtt.begin("mqtt://user:pass@mosquito.org:1883");
  //  mqtt.begin("mqtt://user:pass@mosquito.org:1883#clientId");

}
}

void loop() {
  // put your main code here, to run repeatedly:
  mqtt.handle();
}

