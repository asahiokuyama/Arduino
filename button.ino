int cnt = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(A0,INPUT_PULLUP);
  Serial.begin(9600);

}

void loop() {
  Serial.println(cnt);
  // put your main code here, to run repeatedly:
  if(digitalRead(A0)==LOW){
    cnt++;
    delay(100);
    while(digitalRead(A0)==LOW){}
  }
  
}
