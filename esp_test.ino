

#define BLYNK_TEMPLATE_ID "TMPLl1P59vq1"
#define BLYNK_TEMPLATE_NAME "test"
#define BLYNK_AUTH_TOKEN "oyi4qsi4HlolKvlhKeUtpR7gdvj5l5dj"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "SSID-398851";
char pass[] = "62cb76fe";
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Blynk.begin(auth,ssid,pass);
  pinMode(5,OUTPUT);

}

BLYNK_WRITE(V1){
  digitalWrite(5,HIGH);
}

BLYNK_WRITE(V2){
  digitalWrite(5,LOW);
}


void loop() {
  // put your main code here, to run repeatedly:
  
  Blynk.run();
  Serial.print(V1);

}
