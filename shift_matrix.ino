const int latchPin = 3;
const int clockPin = 4;
const int dataPin = 2;
 
void setup() {
  // put your setup code here, to run once:
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}
 
void loop() {
  // put your main code here, to run repeatedly:
  byte rowData[8] = {4,0,4,4,14,14,31,0};
  shift_Out(rowData);
}
 
void shift_Out(byte rowData[]) {
  int i,j,k=0;
   
  //行ごとに出力する
  for(i=0; i<7; i++){  //row 0-6
    byte row = (1<<i);
    digitalWrite(clockPin, LOW);
    digitalWrite(dataPin, LOW);
    digitalWrite(latchPin, LOW);
   
    // i行（横）のデータ(5dots)
    for(k=7; k>=0; k--) {
      digitalWrite(clockPin, LOW);
      if(rowData[i] & (1<<k)) digitalWrite(dataPin, HIGH);
      else digitalWrite(dataPin, LOW);
      digitalWrite(clockPin, HIGH);
      digitalWrite(dataPin, LOW);
    }
    //列のデータ(7dots)
    //どの行を出力するかを選ぶ
    for(k=7; k>=0; k--) {
      digitalWrite(clockPin, LOW);
      if(row & (1<<k)) digitalWrite(dataPin, LOW);
      else digitalWrite(dataPin, HIGH);
      digitalWrite(clockPin, HIGH);
      digitalWrite(dataPin, LOW);
    }
     
    digitalWrite(clockPin, LOW);
    digitalWrite(latchPin, HIGH);
  }
}
