#include "Stu_AS5600_D.h"


Stu_AS5600::Stu_AS5600():_I2CAddress(0x36){

}

void Stu_AS5600::begin( void ){
  I2c.begin();
  I2c.pullup(1);
  delay(100);
  I2c.timeOut(50);

  delay(1); //Wait at least 1 ms.

}

AGC_e Stu_AS5600::getAGC( void ){

  union{
    struct{
      uint8_t MH:1;
      uint8_t ML:1;
      uint8_t MD:1;

    };
    uint8_t byte;

  }agc;

  agc.byte = _readI2C( STATUS ) >> 3;


  if(agc.MH){
      return MH;
    }

  else if(agc.ML){
      return ML;
    }

  else if(agc.MD){
      return MD;
    }

  return READ_ERROR;

}

uint16_t Stu_AS5600::getRawAngle( void ){

  return( _readAngle( angle_raw ) );

}

uint16_t Stu_AS5600::getAngle( void ){


   //Read the RAW ANGLE register.

  return( _readAngle( angle_filtered ) );

}

uint16_t Stu_AS5600::_readAngle( angle_e e ){
  mag_data_t pos;
  uint8_t address;

  switch(e){
    case angle_raw:
      address = RAW_ANGLE_H;
      break;

    case angle_filtered:
      address = ANGLE_H;
      break;

    default:
      address = RAW_ANGLE_H;
      break;

  }
  _readI2C(address, 2, pos.b);
  
  return (pos.i);
}

void Stu_AS5600::setOutPinMode( out_mode_e mode ){
  uint8_t modeByte;
  switch(mode){
    case analog_full:
      modeByte = 0b00 ;
      break;

    case analog_reduced:
      modeByte = 0b01 ;
      break;

    case digital_PWM:
      modeByte = 0b10 ;
      break;
  }
  modeByte <<= OUT_BIT;

  uint8_t reg = _readI2C(CONF_L);
  delay(2);

  reg &= ~OUT_MASK;
  reg |= modeByte;

  _overWriteI2C( CONF_L, (modeByte) );
  delay(2);


}



bool Stu_AS5600::setZeroPosition( void ){
  mag_data_t pos;

  int maxTries = 10;
/*
  Serial.println();
  Serial.println(pos.hb, BIN);
  Serial.println(pos.lb, BIN);
  Serial.println(pos.b[0], BIN);
  Serial.println(pos.b[1] << 8, BIN);
  Serial.println(pos.i, BIN);
  Serial.println(pos.i);
  //Serial.println();
*/
int i = 0;
while(getAGC() != MD && i < maxTries){
  delay(200);
  i++;
}
if(i >= maxTries){
  return 0;
}

pos.i = getRawAngle();
  _overWriteI2C(ZPOS_H, pos.hb);
  _overWriteI2C(ZPOS_L, pos.lb);
  return 1;

}

uint8_t Stu_AS5600::_readI2C( uint8_t regAddress ){
  uint8_t readAry[1];

    I2c.read( _I2CAddress, regAddress, 1, readAry ); // Read 1-2 Bytes from AS5600 Address and store in array


  return readAry[0]; // Return array for use in other functions

}


void Stu_AS5600::_readI2C( uint8_t regAddress, int16_t numBytes, uint8_t* destAry ){
    I2c.read(_I2CAddress, regAddress, numBytes, destAry ); // Read 1-2 Bytes from AS5600 Address and store in array

}


void Stu_AS5600::_writeI2C( uint8_t regAddress, uint8_t value ){

  //uint8_t tempReg = _readI2C(regAddress);
  //tempReg &= (value) & 0xFF;
  _overWriteI2C(regAddress, value);

}

void Stu_AS5600::_overWriteI2C( uint8_t regAddress, uint8_t value ){

  I2c.write(_I2CAddress, regAddress, value ); // Write to AS5600 Address with Value


}
