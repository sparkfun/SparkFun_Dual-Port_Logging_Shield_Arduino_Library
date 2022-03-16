/*!
 * @file SparkFun_Dual-Port_Logging_Shield_IO.cpp
 *
 * @mainpage SparkFun Dual-Port Logging Shield Arduino Library
 * 
 * @section intro_sec Introduction
 * 
 * This library facilitates communication with the Thing Plus Dual-Port Logging Shield over I<sup>2</sup>C.
 * 
 * Want to support open source hardware? Buy a board from SparkFun!
 * <br>SparkFun Thing Plus Dual-Port Logging Shield (DEV-19217): https://www.sparkfun.com/products/19217
 * 
 * @section author Author
 * 
 * This library was written by:
 * Paul Clark
 * SparkFun Electronics
 * March 2022
 * 
 * @section license License
 * 
 * MIT: please see LICENSE.md for the full license information
 * 
 */

#include "SparkFun_Dual-Port_Logging_Shield_IO.h"

/**************************************************************************/
/*!
    @brief  Begin communication with the SparkFun Dual-Port Logging Shield over I2C
    @param  deviceAddress
            The I2C address of the Dual-Port Logging Shield.
            Default is SFE_DUAL_PORT_LOGGING_DEFAULT_I2C_ADDRESS 0x51.
            Can be changed with setI2CAddress.
    @param  wirePort
            The TwoWire (I2C) port used to communicate with the Dual-Port Logging Shield.
            Default is Wire.
    @return True if communication with the Dual-Port Logging Shield was successful, otherwise false.
*/
/**************************************************************************/
bool DUAL_PORT_LOGGING_SHIELD_IO::begin(byte address, TwoWire& wirePort)
{
  _i2cPort = &wirePort;
  _address = address;
  return isConnected();
}

/**************************************************************************/
/*!
    @brief  Reads the Dual-Port Logging Shield's I2C address and confirms it matches _address.
    @return True if communication with the Dual-Port Logging Shield was successful, otherwise false.
*/
/**************************************************************************/
bool DUAL_PORT_LOGGING_SHIELD_IO::isConnected()
{
  _i2cPort->beginTransmission(_address);
  if (_i2cPort->endTransmission() == 0)
  {
    _i2cPort->beginTransmission(_address);
    _i2cPort->write(SFE_DUAL_PORT_LOGGING_REGISTER_I2C_ADDRESS);
    _i2cPort->endTransmission(); // Send data and release the bus (the 43 (WireS) doesn't like it if the Controller holds the bus!)
    byte bytesReturned = _i2cPort->requestFrom(_address, (byte)1);
    if (bytesReturned != 1)
        return (false);
    byte incomingByte = _i2cPort->read();
    if (incomingByte == _address)
      return (true);
  }
  return (false);
}

/**************************************************************************/
/*!
    @brief  Write multiple bytes to the SparkFun Dual-Port Logging Shield over I2C
    @param  registerAddress
            The (software) register address being written to.
    @param  buffer
            A pointer to the byte array to be written.
    @param  packetLength
            The number of bytes to be written.
    @return True if communication with the Dual-Port Logging Shield was successful, otherwise false.
*/
/**************************************************************************/
bool DUAL_PORT_LOGGING_SHIELD_IO::writeMultipleBytes(byte registerAddress, const byte* buffer, byte const packetLength)
{
  _i2cPort->beginTransmission(_address);
  _i2cPort->write(registerAddress);

  for (byte i = 0; i < packetLength; i++)
    _i2cPort->write(buffer[i]);

  return (_i2cPort->endTransmission() == 0);
}

/**************************************************************************/
/*!
    @brief  Read multiple bytes from the SparkFun Dual-Port Logging Shield over I2C.
            First the register address is written, then the data bytes are read.
    @param  registerAddress
            The (software) register address being read from.
    @param  buffer
            A pointer to the byte array which will hold the read data.
    @param  packetLength
            The number of bytes to be read.
    @param  waitMS
            The number of ms to wait before attempting to read the data.
            This gives the ATtiny43U time to collect the data.
    @return True if the data was read successfully, otherwise false.
*/
/**************************************************************************/
bool DUAL_PORT_LOGGING_SHIELD_IO::readMultipleBytes(byte registerAddress, byte* buffer, byte packetLength, byte waitMS)
{
  _i2cPort->beginTransmission(_address);
  _i2cPort->write(registerAddress);
  _i2cPort->endTransmission(); // Send data and release the bus (the 43 (WireS) doesn't like it if the Controller holds the bus!)

  delay(waitMS); // Give the ATtiny43U time to collect the requested data

  byte bytesReturned = _i2cPort->requestFrom(_address, packetLength);

  byte i;
  for (i = 0; (i < bytesReturned); i++)
    buffer[i] = _i2cPort->read();

  return (bytesReturned == packetLength);
}

/**************************************************************************/
/*!
    @brief  Read a single byte from the SparkFun Dual-Port Logging Shield over I2C.
            First the register address is written, then the data byte is read.
    @param  registerAddress
            The (software) register address being read from.
    @param  buffer
            A pointer to the byte which will hold the read data.
    @param  waitMS
            The number of ms to wait before attempting to read the data.
            This gives the ATtiny43U time to collect the data.
    @return True if the data byte was read successfully, otherwise false.
*/
/**************************************************************************/
bool DUAL_PORT_LOGGING_SHIELD_IO::readSingleByte(byte registerAddress, byte* buffer, byte waitMS)
{
  _i2cPort->beginTransmission(_address);
  _i2cPort->write(registerAddress);
  _i2cPort->endTransmission(); // Send data and release the bus (the 43 (WireS) doesn't like it if the Controller holds the bus!)

  delay(waitMS); // Give the ATtiny43U time to collect the requested data

  byte bytesReturned = _i2cPort->requestFrom(_address, (byte)1);

  *buffer = _i2cPort->read();

  return (bytesReturned == 1);
}

/**************************************************************************/
/*!
    @brief  Write a single byte to the SparkFun Dual-Port Logging Shield over I2C
    @param  registerAddress
            The (software) register address being written to.
    @param  value
            The data byte to be written.
    @return True if communication with the Dual-Port Logging Shield was successful, otherwise false.
*/
/**************************************************************************/
bool DUAL_PORT_LOGGING_SHIELD_IO::writeSingleByte(byte registerAddress, byte const value)
{
  _i2cPort->beginTransmission(_address);
  _i2cPort->write(registerAddress);
  _i2cPort->write(value);
  return (_i2cPort->endTransmission() == 0);
}

/**************************************************************************/
/*!
    @brief  Write a register address (only) to the SparkFun Dual-Port Logging Shield over I2C
    @param  registerAddress
            The (software) register address - as a command.
    @return True if communication with the Dual-Port Logging Shield was successful, otherwise false.
*/
/**************************************************************************/
bool DUAL_PORT_LOGGING_SHIELD_IO::writeRegisterAddress(byte registerAddress)
{
  _i2cPort->beginTransmission(_address);
  _i2cPort->write(registerAddress);
  return (_i2cPort->endTransmission() == 0);
}
