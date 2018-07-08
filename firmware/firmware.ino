#include <ESP8266WiFi.h>

/*
 * NAME Loallas   Pin. no
 * D3   1         0
 * D1   2         5
 * D8   3         15
 * D0   4         14
 * D5   5         16
 * 
 */

unsigned int OUT1 = 0;
unsigned int OUT2 = 5;
unsigned int OUT3 = 15;
unsigned int OUT4 = 14;
unsigned int OUT5 = 16;

static const char WIFI_SSID[] = "example";
static const char WIFI_PASSWORD[] = "example";

WiFiServer server(1993);
WiFiClient client;

unsigned long SIGNAL_DURATION = 2000;

unsigned long DISABLE_1 = 0;
unsigned long DISABLE_2 = 0;
unsigned long DISABLE_3 = 0;
unsigned long DISABLE_4 = 0;
unsigned long DISABLE_5 = 0;

void setup() {
  Serial.begin(57600);
  connectWifi();
  startServer();

  pinMode(OUT1, OUTPUT);
  pinMode(OUT2, OUTPUT);
  pinMode(OUT3, OUTPUT);
  pinMode(OUT4, OUTPUT);
  pinMode(OUT5, OUTPUT);
}

void loop() {
  unsigned long now = millis();
  
  if (DISABLE_1 < now && DISABLE_1 > 0) {
    digitalWrite(OUT1, LOW);
    DISABLE_1 = 0;
  }
  
  if (DISABLE_2 < now && DISABLE_2 > 0) {
    digitalWrite(OUT2, LOW);
    DISABLE_2 = 0;
  }
  
  if (DISABLE_3 < now && DISABLE_3 > 0) {
    digitalWrite(OUT3, LOW);
    DISABLE_3 = 0;
  }
  
  if (DISABLE_4 < now && DISABLE_4 > 0) {
    digitalWrite(OUT4, LOW);
    DISABLE_4 = 0;
  }
  
  if (DISABLE_5 < now && DISABLE_5 > 0) {
    digitalWrite(OUT5, LOW);
    DISABLE_5 = 0;
  }
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  
  if (! client.connected()) {
    client = server.available();
    return;
  }

  if (client.available()) {
    String line = client.readStringUntil('\n');
    Serial.println(line);

    if (line == "rotate1") {
      DISABLE_1 = now + SIGNAL_DURATION;
      digitalWrite(OUT1, HIGH);
    }

    if (line == "rotate2") {
      DISABLE_2 = now + SIGNAL_DURATION;
      digitalWrite(OUT2, HIGH);
    }

    if (line == "rotate3") {
      DISABLE_3 = now + SIGNAL_DURATION;
      digitalWrite(OUT3, HIGH);
    }

    if (line == "rotate4") {
      DISABLE_4 = now + SIGNAL_DURATION;
      digitalWrite(OUT4, HIGH);
    }

    if (line == "rotate5") {
      DISABLE_5 = now + SIGNAL_DURATION;
      digitalWrite(OUT5, HIGH);
    }
  }
}

void startServer() {
    server.begin();
    server.setNoDelay(true);
}

void connectWifi() {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting");
    while (WiFi.status() != WL_CONNECTED)
    {
      delay(500);
      Serial.print(".");
    }

    Serial.print("Connected, IP address: ");
    Serial.println(WiFi.localIP());
}

