//Lesson 51 デジタル時計を作って遊ぶスケッチ
//https://omoroya.com/
//使用部品について解説しているLesson
//RTCモジュール：https://omoroya.com/arduino-lesson50/
//4桁7セグメントLED：https://omoroya.com/arduino-lesson25/
//8bitシフトレジスタ：https://omoroya.com/arduino-lesson20/

// Pin No. (for RTC Module)
const int clkPin = 8;  //DS1302：SCLKピン
const int datPin = 9;  //DS1302：I/Oピン
const int rstPin = 10; //DS1302：CEピン

// Pin No.(for 8bit shift register)
const int rclkPin  = 12;  // (12) ST_CP [RCLK] on 74HC595
const int srclkPin = 11;  // (11)  SH_CP [SRCLK] on 74HC595
const int dsPin    = 13;  // (13) DS [SER] on 74HC595
const int dig1 = 5;       // DIG1を1番ピンに割り当て
const int dig2 = 2;       // DIG2を2番ピンに割り当て
const int dig3 = 3;       // DIG3を3番ピンに割り当て
const int dig4 = 4;       // DIG4を4番ピンに割り当て

// 変数の設定
int tDelay = 1;   // 1ms遅延設定←ここの時間で4桁7セグメントLED表示調整

// seven_ledsをbyte型として定義
// 配列にDisplay表示用のデータ0~9と全消灯を設定
// 1 = LED on, 0 = LED off
byte seven_leds[12] =       { B11111100,  // 0
                              B01100000,  // 1
                              B11011010,  // 2
                              B11110010,  // 3
                              B01100110,  // 4
                              B10110110,  // 5
                              B10111110,  // 6
                              B11100000,  // 7
                              B11111110,  // 8
                              B11100110,  // 9
                              B00000001,  // D.P 
                              B00000000,  // OFF
                             };


//シフトレジスタ部分の関数
void funcShiftReg(int x)
{
  digitalWrite(rclkPin, LOW);                         //送信中のRCLKをLowにする
  shiftOut(dsPin, srclkPin, LSBFIRST, seven_leds[x]); //シフト演算を使って点灯するLEDを選択
  digitalWrite(rclkPin, HIGH);                        //送信終了後RCLKをHighにする
}

// Single-Byte Write関数　「時刻の初期値設定」
void s_b_write(int command, int data){
  pinMode(datPin,OUTPUT);                      //DAT(I/O)のOUTPUT指定
  digitalWrite(clkPin, LOW);                   //クロック "L"　L始まりを確定させるため
  digitalWrite(rstPin, HIGH);                  //RSTピン(CE)　"H"　アクセスを許可
  shiftOut(datPin, clkPin, LSBFIRST, command); //コマンド送信（日時格納アドレス）
  shiftOut(datPin, clkPin, LSBFIRST, data);    //データ書き込み（設定日時のデータ）
  digitalWrite(rstPin, LOW);                   //RSTピン(CE)　"L"　アクセス終了
  pinMode(datPin, INPUT);                      //DAT(I/O)をINPUTへ戻す
}

//Single-Byte Read関数　「時刻の読み出し」
int s_b_read(int command){
  int bit = 0;
  int data = 0;
  digitalWrite(clkPin, LOW);                   //クロック "L"　L始まりを確定させるため
  digitalWrite(rstPin, HIGH);                  //RSTピン(CE)　"H"　アクセスを許可
  shiftOut(datPin, clkPin, LSBFIRST, command); //コマンド送信（日時格納アドレス）
  //data（日時）の読み取り動作　8回繰り返し8bitぶん読み出す
  for (int i = 0; i < 8; ++i)                  //8回繰り返し
  {
    bit = digitalRead(datPin);                 //DAT(I/O)の値を読み取り
    //データの統合処理
    data |= (bit << i); //bitシフトさせて、前のデータとのORどり　 //clkをH->Lさせてトグルさせる
    digitalWrite(clkPin, HIGH);                //クロック "H"
    delayMicroseconds(1);                      //クロック"H"期間 1usに設定
    digitalWrite(clkPin, LOW);                 //クロック "L"
  }
  digitalWrite(rstPin, LOW);                   //RSTピン(CE)　"L"　アクセス終了
  return(data);                                //戻り値
}

void setup()
{
  //PINモード設定 for shift register
  pinMode(rclkPin, OUTPUT);   //OUTPUT指定
  pinMode(dsPin, OUTPUT);     //OUTPUT指定
  pinMode(srclkPin, OUTPUT);  //OUTPUT指定
  pinMode(dig1, OUTPUT);      //OUTPUT指定
  pinMode(dig2, OUTPUT);      //OUTPUT指定
  pinMode(dig3, OUTPUT);      //OUTPUT指定
  pinMode(dig4, OUTPUT);      //OUTPUT指定
  digitalWrite(dig1, LOW);    //1番ピンをLOW DI1 OFF
  digitalWrite(dig2, LOW);    //2番ピンをLOW DI2 OFF
  digitalWrite(dig3, LOW);    //3番ピンをLOW DI3 OFF
  digitalWrite(dig4, LOW);    //4番ピンをLOW DI4 OFF
  
  //PINモード設定 for RTC Module
  pinMode(clkPin,OUTPUT);     //OUTPUT指定
  pinMode(rstPin,OUTPUT);     //OUTPUT指定

  //4桁7セグメントLED
  funcShiftReg(12);           //信号初期化
  
  //RTC Module 時刻の設定
  s_b_write(0x80,0x50); //秒の設定　　※50秒
  s_b_write(0x82,0x50); //分の設定　　※59分
  s_b_write(0x84,0x19); //時間の設定　※19時
  s_b_write(0x86,0x26); //日付の設定　※26日
  s_b_write(0x88,0x04); //月の設定　　※4月
  s_b_write(0x8c,0x91); //年の設定　　※21年
  s_b_write(0x8a,0x01); //曜日の設定　※日曜日　　　　　　　　　　　　　　　　　
}

void loop(){
  //時刻の読み出し
  int v_s    = s_b_read(0x81);//read 秒レジスタ
  int v_mi   = s_b_read(0x83);//read 分レジスタ
  int v_h    = s_b_read(0x85);//read 時レジスタ
  int v_date = s_b_read(0x87);//read 日レジスタ
  int v_mo   = s_b_read(0x89);//read 月レジスタ
  int v_y    = s_b_read(0x8d);//read 年レジスタ
  int v_day  = s_b_read(0x8b);//read 曜日レジスタ

int v_h1 = v_mi >> 4;
int v_h2 = v_mi & 0b00001111;
int v_mi1 = v_s >> 4;
int v_mi2 = v_s & 0b00001111;
  
  //DIG1の表示
  delay(tDelay);
  digitalWrite(dig1, LOW); 
  digitalWrite(dig2, HIGH);
  digitalWrite(dig3, HIGH);
  digitalWrite(dig4, HIGH);
  //DIG1 10の位の時間を表示
  funcShiftReg(v_h1);
  delay(tDelay);
  funcShiftReg(11);

  //DIG2の表示
  delay(tDelay);
  digitalWrite(dig1, HIGH); 
  digitalWrite(dig2, LOW);
  digitalWrite(dig3, HIGH);
  digitalWrite(dig4, HIGH);
  //DIG2 1の位の時間を表示
  funcShiftReg(v_h2);
  delay(tDelay);
  funcShiftReg(11);

  //DIG3の表示
  delay(tDelay);
  digitalWrite(dig1, HIGH); 
  digitalWrite(dig2, HIGH);
  digitalWrite(dig3, LOW);
  digitalWrite(dig4, HIGH);
  //DIG3 10の位の分を表示
  funcShiftReg(v_mi1);
  delay(tDelay);
  funcShiftReg(11);

  //DIG4の表示
  delay(tDelay);
  digitalWrite(dig1, HIGH); 
  digitalWrite(dig2, HIGH);
  digitalWrite(dig3, HIGH);
  digitalWrite(dig4, LOW);
  //DIG4 1の位の分を表示
  funcShiftReg(v_mi2);
  delay(tDelay);
  funcShiftReg(11);
}
