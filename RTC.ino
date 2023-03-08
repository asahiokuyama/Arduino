//Lesson 50 RTCモジュール（Real Time Clock Module）
//RTCモジュールの制御（ライブラリ使用なし）
//https://omoroya.com/

// ピン番号の設定
const int clkPin = 8;  //DS1302：SCLKピン
const int datPin = 9;  //DS1302：I/Oピン
const int rstPin = 10; //DS1302：CEピン

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
    Serial.print(bit);                         //シリアルモニタに表示
    
    //データの統合処理
    data |= (bit << i);                        //bitシフトさせて、前のデータとのORどり　 
    //clkをH->Lさせてトグルさせる
    digitalWrite(clkPin, HIGH);                //クロック "H"
    delayMicroseconds(1);                      //クロック "H"期間 1usに設定
    digitalWrite(clkPin, LOW);                 //クロック "L"
  }
  digitalWrite(rstPin, LOW);                   //RSTピン(CE)　"L"　アクセス終了
  Serial.print(" ");                           //シリアルモニタにスペースの表示
  //
  int t = (10 * (data  >> 4))+(data & 0b1111); //上位4bit + 下位4bitを統合　※数値に変換
  return(t);                                   //戻り値
}

void setup()
{
  //PINモード設定
  pinMode(clkPin,OUTPUT);                           //OUTPUT指定
  pinMode(rstPin,OUTPUT);                           //OUTPUT指定
  
  Serial.begin(9600);                               //データ転送レートを指定
  Serial.println("時刻を設定値にしますか？  [y or n]");
  while(Serial.available() == 0){}                  //データが入るまでループ
  int val = Serial.read();                          //受信データの読み込み
  if(val == 0x79){                                  //y,nの判定（ASCIIコード y = 0x79
    //アドレスの値に関してはdatasheetで確認。※下記は16進数表示
    s_b_write(0x80,0x55); //秒の設定　　※55秒
    s_b_write(0x82,0x59); //分の設定　　※59分
    s_b_write(0x84,0x23); //時間の設定　※23時
    s_b_write(0x86,0x11); //日付の設定　※11日
    s_b_write(0x88,0x04); //月の設定　　※4月
    s_b_write(0x8c,0x21); //年の設定　　※21年
    s_b_write(0x8a,0x01); //曜日の設定　※日曜日　　　　　　　　　　　　　　　　　
  }else{
    pinMode(datPin, INPUT); //時刻を設定値にしない場合、INPUT指定
  }
  Serial.println("### 2進数表示 ###");
  Serial.println("|second |minutes |hour    |date    |month   |year    |day     |");
  Serial.println("01234567|01234567|01234567|01234567|01234567|01234567|01234567|"); 
}

void loop(){
  int v_s    = s_b_read(0x81);//read 秒レジスタ
  int v_mi   = s_b_read(0x83);//read 分レジスタ
  int v_h    = s_b_read(0x85);//read 時レジスタ
  int v_date = s_b_read(0x87);//read 日レジスタ
  int v_mo   = s_b_read(0x89);//read 月レジスタ
  int v_y    = s_b_read(0x8d);//read 年レジスタ
  int v_day  = s_b_read(0x8b);//read 曜日レジスタ
  
  Serial.print("  ");        
  Serial.print(v_s);     
  Serial.print("秒 ");        
  Serial.print(v_mi);     
  Serial.print("分 ");        
  Serial.print(v_h);        
  Serial.print("時 ");
  Serial.print(v_date);        
  Serial.print("日 ");
  Serial.print(v_mo);        
  Serial.print("月 ");
  Serial.print("20");
  Serial.print(v_y);        
  Serial.print("年 ");
  
  //数値を曜日としてシリアルモニタに表示
  char day_week;
  switch (v_day) {
  case 1:
    Serial.print("日");
    break;
  case 2:
    Serial.print("月");
    break;
  case 3:
    Serial.print("火");
    break;
  case 4:
    Serial.print("水");
    break;
  case 5:
    Serial.print("木");
    break;
  case 6:
    Serial.print("金");
    break;
  case 7:
    Serial.print("土");
    break;
  }       
  Serial.println("曜日 ");
  
  delay(1000);
}
