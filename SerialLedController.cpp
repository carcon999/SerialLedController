/*
  Serial Led Controller Library v1.0  2014/05/11
 */

#include "SerialLedController.h"

#define ACK                  (0x06)         /* Return value of success. */
#define UART_HI_SPEED        (57600)        /* 57600bps */
#define UART_LO_SPEED        (19200)        /* 19200bps */
#define UART_RES_TOUT        (1000)         /* 1000ms time out */

/* Run. ACK command, returned to play after completion. */
const uint8_t play_cmd[SERIALCOMMAND_FIXEDLEN] = 
{
    0x94, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* Stop. */
const uint8_t stop_cmd[SERIALCOMMAND_FIXEDLEN] = 
{
    0x94, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// constructor
SerialLedController::SerialLedController(const int _pinreset, const int _pinbr)
  : pin_reset(_pinreset), pin_baudrate(_pinbr)
{
}

void SerialLedController::begin(SoftwareSerial* _pSerial, const boolean _hispeed)
{
  is_hi_speed = _hispeed;

  /* Initialization process of software serial */
  if(is_hi_speed){
    _pSerial->begin(UART_HI_SPEED);
  }else{
    _pSerial->begin(UART_LO_SPEED);
  }
  _pSerial->setTimeout(UART_RES_TOUT);

  pStream = _pSerial;

  /* initialize */
  init();
}

void SerialLedController::begin(HardwareSerial* _pSerial, const boolean _hispeed)
{
  is_hi_speed = _hispeed;

  /* Initialization process of software serial */
  if(is_hi_speed){
    _pSerial->begin(UART_HI_SPEED);
  }else{
    _pSerial->begin(UART_LO_SPEED);
  }
  _pSerial->setTimeout(UART_RES_TOUT);

  pStream = _pSerial;

  /* initialize */
  init();
}


void SerialLedController::reset(void)
{
  init();
}

void SerialLedController::init(void)
{
  /* port initialize*/
  init_port();

  /* select the communication speed. */
  select_baudrate();

  /* reset the controller. */
  shield_reset();

  /* enable the trigger port. */
  enable_trigger();
}

void SerialLedController::init_port(void)
{
  /* Set Output Reset Port */
  if(pin_reset != PIN_NOTUSE)
  {
    pinMode(pin_reset, OUTPUT);
  }

  /* Set Output Baudrate Select Port */
  if(pin_baudrate != PIN_NOTUSE)
  {
    pinMode(pin_baudrate, OUTPUT);
  }
}

void SerialLedController::select_baudrate(void)
{
  if(pin_baudrate != PIN_NOTUSE)
  {
    if(is_hi_speed)
    {
      digitalWrite(pin_baudrate, LOW);
    }
    else
    {
      digitalWrite(pin_baudrate, HIGH);
    }
  }
}

void SerialLedController::shield_reset(void)
{
  if(pin_reset != PIN_NOTUSE)
  {
    /* LED Contorl Reset. 50ms Low */
    digitalWrite(pin_reset, LOW);
    delay(50);
    digitalWrite(pin_reset, HIGH);

    /* It is necessary to wait for 200ms or more. */
    /* waits for the completion of the initialization process. */
    delay(200);
  }
}

void SerialLedController::enable_trigger(void)
{
  if(pin_baudrate != PIN_NOTUSE)
  {
    digitalWrite(pin_baudrate, HIGH);
  }
}

char SerialLedController::write_and_rsp(const uint8_t* pcmd)
{
  char rsp = NULL;

  if(pStream)
  {
    /* dammy Read */  
    if (pStream->available())
    {
      pStream->read();
    }

    /* send 8byte command. */
    pStream->write(pcmd, SERIALCOMMAND_FIXEDLEN);
    
    /* wait return command. */
    if(1 != pStream->readBytes( &rsp, 1))
    {
      rsp = NULL;
    }
  }

  return rsp;  
}

boolean SerialLedController::write(const uint8_t tbl[][SERIALCOMMAND_FIXEDLEN], int size)
{
  int i;
  char rsp;
  boolean ret = false;
  int lines = size / SERIALCOMMAND_FIXEDLEN;

  /* play stop. */
  write_and_rsp(stop_cmd);

  /* Batch Transfer the data */
  for(i = 0 ; i < lines ; i++)
  {
    /* Send 8byte command and wait response. */
    rsp = write_and_rsp(&tbl[i][0]);
    
    /* check ack command. */
    if(rsp != ACK)
    {
      break;
    }
  }

  if(rsp == ACK)
  {
    ret = true;
  }

  return ret;
}

void SerialLedController::start(void)
{
  if(pStream)
  {
    pStream->write(play_cmd, sizeof(play_cmd));
  }
}

void SerialLedController::stop(void)
{
  write_and_rsp(stop_cmd);
}
