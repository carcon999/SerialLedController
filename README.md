SerialLedController
===================
[フルカラーLEDコントローラ用シールド](http://blogs.yahoo.co.jp/carcon999/folder/1250867.html)
をArduinoで簡単に利用するためのライブラリです。  本ライブラリを利用することで、シリアルコマンドのテーブルを指定するだけで、LEDの演出を切り替えることができるようになります。  
![Image](https://raw.githubusercontent.com/carcon999/SerialLedController/master/image/redbd.jpg)

# Arduino IDEへのインストール方法

 1. Releaseされた[SerialLedContorller.zip](https://github.com/carcon999/SerialLedController/releases)をダウンロードします。（ファイル名やフォルダ名は変更しないでください。）
 2. Arduino IDEを起動し、メニューから以下の順序で指定しライブラリを追加してください。  
 3. 「スケッチ」->「ライブラリを使用」->「Add Library...」でZipファイルを指定します。
 4. 「ファイル」->「スケッチブック」->「Libraries」->「SerialLedController」->「SerialLedShield」より各種サンプルスケッチを実行することができます。

# 使い方

 TBD

## 基本的な流れ

 TBD

## その他

その他の利用方法については、examplesが参考になります。

# Functions

## コンストラクタ



- SerialLedController(const int _pinreset, const int _pinbr)
 + `const int _pinreset` :
    リセット制御端子を指定する。制御端子を利用しない場合は、-1を指定する。
 + `const int _pinbr` :
    通信速度制御端子を指定する。制御端子を利用しない場合は、-1を指定する。

## begin

利用開始指示。利用開始前に必ず指定する。  
利用するシリアルオブジェクト（ソフトウェア or ハードウェア）とその通信レート（57600bps/19200bps）を指定する必要があります。

- void begin(SoftwareSerial* _pSerial, const boolean _hispeed = true)
 + `SoftwareSerial* _pSerial` :
    ソフトウェアシリアルのオブジェクトを指定する
 + `const boolean _hispeed` :
    シリアル通信速度の高低を指定する。省略時:true。true:57600bps, false:19200bps

- void begin(HardwareSerial* _pSerial, const boolean _hispeed = true)
 + `HardwareSerial* _pSerial` :
    ハードウェアシリアルのオブジェクトを指定する
 + `const boolean _hispeed` :
    シリアル通信速度の高低を指定する。省略時:true。true:57600bps, false:19200bps

## write

LEDコントローラに制御コマンドを送る。制御コマンドには、LEDの演出だけでなく各種制御コマンドも含まれる。

- boolean write(const uint8_t tbl[][SERIALCOMMAND_FIXEDLEN], int size)
 + `const uint8_t tbl[][SERIALCOMMAND_FIXEDLEN]` :
    制御コマンドのテーブルを指定する。（8byte境界であること）
 + `int size` :
    指定したテーブルのサイズ

## start

演出開始用のコマンドを送る。
{0x94, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00} を送信します。

- void start(void)
 + `void` :
    なし

## stop

演出停止用のコマンドを送る。
{0x94, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00} を送信します。

- void stop(void)
 + `void` :
    なし

## reset

LEDコントローラのリセット端子を操作しリセットする。
コンストラクタでリセット制御端子が指定されている場合のみ有効です。
また、通信速度制御端子が指定されていれば、合わせて通信速度の指定（HI/LOW）を行います。

- void reset(void)
 + `void` :
    なし
