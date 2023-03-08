#define BLYNK_TEMPLATE_ID "TMPLl1P59vq1"
#define BLYNK_TEMPLATE_NAME "test"
#define BLYNK_AUTH_TOKEN "oyi4qsi4HlolKvlhKeUtpR7gdvj5l5dj"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "SSID-398851";
char pass[] = "62cb76fe";

#include <ESP32Servo.h>

#define SERVO_PIN 5

Servo myServo;

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth,ssid,pass);
  
  myServo.attach(SERVO_PIN);
}

BLYNK_WRITE(V1){
  myServo.write(120);
}

BLYNK_WRITE(V2){
  myServo.write(20);
}

void loop() {
  Blynk.run();
//  myServo.write(20);
//  delay(1000);
//  myServo.write(120);
//  delay(1000);
}
