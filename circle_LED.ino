const int INPUT_PIN = A4;    // 入力ピンをA4に固定
int VOLUME;                  // 変数を整数型で宣言
 
void setup(){
 
  Serial.begin(9600);  // シリアル通信の開始

  for(int i = 5;i<=12;i++){
    pinMode(i,OUTPUT);
  }
  
}
 
 
void loop(){
 
  VOLUME = analogRead(INPUT_PIN);  // アナログ値の読み取り
 
  Serial.print("Volume: ");        // シリアルモニタに出力
  Serial.println(VOLUME);
 
  delay(100);

  if(VOLUME<300){
    digitalWrite(5,HIGH);
    for(int i=5;i<=12;i++){
      if(i != 5){
        digitalWrite(i,LOW);
      }
    }
  }
    
  if(VOLUME>300 && VOLUME<305){
    digitalWrite(5,HIGH);
    digitalWrite(6,HIGH);
    for(int i=7;i<=12;i++){
        digitalWrite(i,LOW); 
    }
  }

  if(VOLUME>305 && VOLUME<310){
    digitalWrite(5,HIGH);
    digitalWrite(6,HIGH);
    digitalWrite(7,HIGH);
    for(int i=8;i<=12;i++){
        digitalWrite(i,LOW); 
    }
  }

  if(VOLUME>315 && VOLUME<320){
    for(int i=5;i<=8;i++){
        digitalWrite(i,HIGH); 
    }
    for(int i=9;i<=12;i++){
        digitalWrite(i,LOW); 
    }
  }

  if(VOLUME>320 && VOLUME<325){
    for(int i=5;i<=9;i++){
        digitalWrite(i,HIGH); 
    }
    for(int i=10;i<=12;i++){
        digitalWrite(i,LOW); 
    }
  }

  if(VOLUME>325 && VOLUME<330){
    for(int i=5;i<=10;i++){
        digitalWrite(i,HIGH); 
    }
    for(int i=11;i<=12;i++){
        digitalWrite(i,LOW); 
    }
  }

  if(VOLUME>330 && VOLUME<335){
    for(int i=5;i<=11;i++){
        digitalWrite(i,HIGH); 
    }
    digitalWrite(12,LOW);
  }

  if(VOLUME>335){
    for(int i=5;i<=12;i++){
        digitalWrite(i,HIGH); 
    }
  }

}
  
  
 
