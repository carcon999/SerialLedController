/*
  SerialCtrlDirect.ino

  Windows用のシリアルLEDプログラマーから演出確認が行えます。
  Windows用のツールは以下のサイトからダウンロード可能です。
  http://blogs.yahoo.co.jp/carcon999/37808488.html

  Windowsアプリ側の通信速度は57600bpsにしてください。
  ※Windowsアプリの「ツール」->「オプション」-> Baudrate(bps)に57600を指定します。

  Arduinoのシリアルモニタは利用できません。

  This example code is in the public domain.
*/
// include library codes
#include <SoftwareSerial.h>
#include <SerialLedController.h> // library

// ソフトウェアシリアルのインスタンスを生成する。
// TXとRXのPIN番号を指定する。
// ※シールドのJP1の設定は、上段・下段共に2-3をショート（デフォルト）
SoftwareSerial softSerial(2, 3);

// シリアルコントローラ用ライブラリのインスタンスを生成する。
// リセットとボーレート指定用のPIN番号を指定する。もし利用しない場合は－１を指定する。
SerialLedController controller(4, 5);

void setup()
{
  Serial.begin(57600);
  Serial.setTimeout(100);
  
  // シリアルクラスと、通信速度（true:57600, false:19200）を指定する
  controller.begin(&softSerial, true);
  softSerial.setTimeout(100);
}

void loop()
{
  delay(1);

  if (softSerial.available())
  {
    Serial.write(softSerial.read());
  }

  if (Serial.available())
  {
    char buff[8];
    if(Serial.readBytes(buff, 8) == 8)
    {
      softSerial.write((const uint8_t*)buff, 8);
    }
  }
}
