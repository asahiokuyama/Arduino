//ESP32 Lesson 03 Wi-Fiのアクセスポイントへ接続
//https://omoroya.com/

#include <WiFi.h>;

WiFiServer server(80);

void setup() {
  Serial.begin(115200);                   //シリアル通信のデータ転送レートを115200bpsで指定
  WiFi.begin("SSID-398851", "62cb76fe");          //アクセスポイント接続のためのIDとパスワードの設定
  while (WiFi.status() != WL_CONNECTED) { //接続状態の確認
    Serial.print(".");                    //接続しなかったらシリアルモニタに「.」と表示
    delay(300);                           //接続していなければ0.3秒待つ
  }
  Serial.println("");                     //シリアルモニタ改行
  Serial.println("WiFi Connected");       //接続したらシリアルモニタに「WiFi Connected」と表示
  Serial.print("IP Address : ");          //シリアルモニタに表示
  Serial.println(WiFi.localIP());         //割り当てられたIPアドレスをシリアルモニタに表示
}

void loop() {
}
