/*
  Default.ino

  デフォルトの（演出）設定で動作確認します。

  This example code is in the public domain.
*/
// include library codes
#include <SoftwareSerial.h>
#include <SerialLedController.h> // library

/* Commands Table. Run sequentially. */
const uint8_t led_play_list[][SERIALCOMMAND_FIXEDLEN] =
{
  { 0x94, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* Rec Start. */
  { 0x90, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00 }, /* system */
  { 0x95, 0x1E, 0x01, 0x0A, 0xFF, 0x00, 0x00, 0x00 }, /* rainbow */
  { 0x97, 0x20, 0x03, 0x14, 0x02, 0x00, 0x00, 0x00 }, /* seesaw */
  { 0x92, 0x00, 0x00, 0x00, 0x20, 0x00, 0x64, 0x00 }, /* shift */
  { 0x94, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* Rec End. */
};

// ソフトウェアシリアルのインスタンスを生成する。
// TXとRXのPIN番号を指定する。
// ※シールドのJP1の設定は、上段・下段共に2-3をショート（デフォルト）
SoftwareSerial softSerial(2, 3);

// シリアルコントローラ用ライブラリのインスタンスを生成する。
// リセットとボーレート指定用のPIN番号を指定する。もし利用しない場合は－１を指定する。
SerialLedController controller(4, 5);

void setup()
{
  // シリアルクラスと、通信速度（true:57600, false:19200）を指定する
  controller.begin(&softSerial, true);

  // もしハードウェアシリアルを利用する場合は、以下のように与える
  // ※シールドのJP1の設定は、上段・下段共に1-2をショートとする。
  // Arduinoのシリアルモニタは使えなくなります。
  //controller.begin(&Serial, true);

  // 演出用のテーブルを与える。（コントローラにデータを転送する）  
  if(controller.write(led_play_list, sizeof(led_play_list))){
    // 転送に成功したら演出を開始する。
    controller.start();
  }
}

void loop()
{
}
