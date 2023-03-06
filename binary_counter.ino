int s;
int c4;
int c5;

void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);
    for(int num = 3;num<=6;num++){
      pinMode(num,OUTPUT);
//      digitalWrite(num,HIGH);
    }
}

void loop() {
  // put your main code here, to run repeatedly:
    Serial.println(s);
    
    //push
    if(digitalRead(2)==LOW) {
      s++;
      c4++;
      c5++;
      
      if(s>=16)s=0;

      if(c4>=4)c4 = 0;

      if(c5>=8)c5 = 0;
       
      delay(100);
      while(digitalRead(2)==LOW) {}
    }
    
    if(s%2!=0){//LED1
      digitalWrite(3,HIGH);
    }else{
      digitalWrite(3,LOW);
    }

    if(c4>=2){//LED2
      digitalWrite(4,HIGH);
    }else{
      digitalWrite(4,LOW);
    }

    if(c5>=4){//LED3
      digitalWrite(5,HIGH);
    }else{
      digitalWrite(5,LOW);
    }

    if(s>=8){//LED4
      digitalWrite(6,HIGH);
    }else{
      digitalWrite(6,LOW);
    }

}
