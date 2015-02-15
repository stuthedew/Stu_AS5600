#include "Stu_AS5600_D.h"


Stu_AS5600::Stu_AS5600():_I2CAddress(0x36){

}

void Stu_AS5600::begin( void ){
  I2c.begin();
  I2c.pullup(1);
  delay(100);
  I2c.timeOut(50);

  getRawAngle();




  delay(1); //Wait at least 1 ms.

}

AGC_e Stu_AS5600::getAGC( void ){

  uint8_t agc = _readI2C( STATUS );
  Serial.println(agc, BIN);
  switch(agc){
    case ( 1 << MH_BIT ):
      return MH;
      break;

    case ( 1 << ML_BIT ):
      return ML;
      break;

    case ( 1 << MD_BIT ):
      return MD;
      break;
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
/*
  Serial.println(pos.b[0], BIN);
  Serial.println(pos.b[1], BIN);
  Serial.println(pos.i);
  Serial.println();
*/
  return (pos.i);
}

void Stu_AS5600::setZeroPosition( void ){
  mag_data_t pos;
  pos.i = getRawAngle();



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

  uint8_t tempReg = _readI2C(regAddress);
  tempReg |= value;
  _overWriteI2C(regAddress, tempReg);

}

void Stu_AS5600::_overWriteI2C( uint8_t regAddress, uint8_t value ){
  uint8_t nackack = 100;
  while(nackack != 0){
    nackack = I2c.write(_I2CAddress, regAddress, value ); // Write to AS5600 Address with Value
    delay(2); // Wait 2 ms to prevent overpolling
  }
}
