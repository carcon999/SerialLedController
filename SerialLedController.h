/*
  SerialLEDController.h

  SerialLEDController was developed by @carcon999 in 2014.  This Library is
  originally distributed at carcon999's Homepage. 
  <http://blogs.yahoo.co.jp/carcon999/folder/1250867.html>

  SerialLEDController is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation, either version 2.1 of the License, or
  (at your option) any later version.

  SerialLEDController is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with SerialLEDController.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef SERIALLEDCONTROLLER_H
#define SERIALLEDCONTROLLER_H

#include <avr/pgmspace.h>
#include <arduino.h>
#include <SoftwareSerial.h>
#include <HardwareSerial.h>

#define SERIALCOMMAND_FIXEDLEN  (8)   /* Serial Command Fixed Length */
#define PIN_RESET               (4)   /* LED Control Reset Port */
#define PIN_BAUDRATE            (5)   /* LED Control Baudrate Select Port */
#define PIN_NOTUSE              (-1)  /* Pin Not Used. */

class SerialLedController
{
private:
  const int pin_reset;    // reset pin
  const int pin_baudrate; // baudrate pin
  boolean is_hi_speed;
  Stream* pStream;

public:
  // constructor
  SerialLedController(const int _pinreset = PIN_RESET, const int _pinbr = PIN_BAUDRATE);

  // functions
  void begin(SoftwareSerial* _pSerial, const boolean _hispeed = true);
  void begin(HardwareSerial* _pSerial, const boolean _hispeed = true);
  boolean write(const uint8_t tbl[][SERIALCOMMAND_FIXEDLEN], int size);
  void start(void);
  void stop(void);
  void reset(void);

private:
  void init(void);
  void init_port(void);
  void select_baudrate(void);
  void shield_reset(void);
  void enable_trigger(void);
  char write_and_rsp(const uint8_t* pcmd);
  
}; // SerialLedController

#endif // #ifndef SERIALLEDCONTROLLER_H