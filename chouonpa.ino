#include <Servo.h>      // Servoライブラリの読み込み
 
Servo myservo;

int TRIG = 3;
int ECHO = 2;

const int SV_PIN = 7;       // サーボモーターをデジタルピン7に

double duration = 0;
double distance = 0;
double speed_of_sound = 331.5 + 0.6 * 25; // 25℃の気温の想定

void setup() {
  Serial.begin( 9600 );

  pinMode(ECHO, INPUT );
  pinMode(TRIG, OUTPUT );
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);

 

   myservo.attach(SV_PIN, 500, 2400);
}

void loop() {
  
  digitalWrite(TRIG, LOW); 
  delayMicroseconds(2); 
  digitalWrite( TRIG, HIGH );
  delayMicroseconds( 10 ); 
  digitalWrite( TRIG, LOW );
  duration = pulseIn( ECHO, HIGH ); // 往復にかかった時間が返却される[マイクロ秒]

  if (duration > 0) {
    duration = duration / 2; // 往路にかかった時間
    distance = duration * speed_of_sound * 100 / 1000000;
    Serial.print("Distance:");
    Serial.print(distance);
    Serial.println(" cm");
  }

  if(distance>5){
    digitalWrite(8,HIGH);
    digitalWrite(9,LOW);
    
    myservo.write(20);
  }else{
    digitalWrite(8,LOW);
    digitalWrite(9,HIGH);

    myservo.write(100);
  }

  delay(200);
}
