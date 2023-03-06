int s;
unsigned long runtime;
unsigned long starttime;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for(int num = 3;num<=6;num++){
    pinMode(num,OUTPUT);
    digitalWrite(num,LOW);
  }

}


void loop() {
  // put your main code here, to run repeatedly:
  starttime = millis()/1000;
  runtime=starttime-runtime;
  Serial.println(runtime);

  if(digitalRead(2) == LOW){
    s++;
    runtime = 0;
    delay(1000);
    digitalWrite(3,LOW);
    while(digitalRead(2) == LOW){}
  }

  if(runtime>3){
    digitalWrite(3,HIGH);
    }
    else{
      digitalWrite(3,LOW);
    }


}
