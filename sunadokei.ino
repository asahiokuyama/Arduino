int anode[5]   = {A0,A1,A2,5,6 };
int cathode[7] = { 7,8,9,10,11,12,13 };
const int latchPin = 3;
const int clockPin = 4;
const int dataPin = 2;

unsigned long tm = 0;
int slide = 0;

#define SCROLL_TIME 120

boolean matrix_data[49][5]={
  { 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0},
  { 0, 0, 1, 0, 0},///
  { 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0},
  { 0, 0, 1, 0, 0},
  { 0, 0, 0, 0, 0},///
  { 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0},
  { 0, 0, 1, 0, 0},
  { 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0},///
  { 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0},
  { 0, 0, 1, 0, 0},
  { 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0},///
  { 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0},
  {0, 0, 1, 0, 0},
  { 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0},///
  { 0, 0, 0, 0, 0},
  { 0, 0, 1, 0, 0},
  {0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0},///
  { 0, 0, 1, 0, 0},
  { 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0}
};

boolean matrixX[7][5] = {};

boolean matrix[7][5] = {
  { 1, 1, 1, 1, 1},
  { 0, 1, 1, 1, 0},
  { 0, 1, 1, 1, 0},
  { 0, 0, 1, 0, 0},
  { 0, 0, 1, 0, 0},
  { 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0}
};

void setup()
{
  //ピンの初期化
  for ( int i = 0; i < 5; ++i )
  {
    pinMode( anode[i], OUTPUT );
    digitalWrite( anode[i], LOW );
  }
  for ( int i = 0; i < 7; ++i )
  {
    pinMode( cathode[i], OUTPUT );
    digitalWrite( cathode[i], HIGH );
  }

  for (int i = 0; i < 7 ; ++i)  {
    for (int j = 0; j < 5 ; ++j) {
      matrixX[i][j] = 0;
    }
  }

  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  tm = millis();
}
 
void loop()
{
//  digitalWrite( anode[0], HIGH);
//   digitalWrite( cathode[0], LOW );

  if (tm + SCROLL_TIME <= millis()) {
    for (int i = 0; i < 7 ; i++)  {
      for (int j = 0; j < 5 ; j++) {
        matrixX[i][j] = matrix_data[i+slide][j];
      }
    }
     
    //格納場所をスライド、末端に到達したら始めに戻る
    if (slide < 41) {
      ++slide;
    }
    else {
      slide = 0;
    }
     
    //経過時間を再計測
    tm = millis();
  }

   for(int i = 0;i<7;i++){
    digitalWrite( cathode[i], LOW);
    for(int j = 0;j<5;j++){
      digitalWrite( anode[j],  matrixX[i][j]);
    }
//    delay(50);
    for ( int j = 0; j < 5; j++ )
    {
      digitalWrite( anode[j], LOW ); 
    }
    digitalWrite( cathode[i], HIGH );
   }

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
