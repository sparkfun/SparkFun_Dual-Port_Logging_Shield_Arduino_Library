/*!
 * @file SparkFun_Dual-Port_Logging_Shield_IO.h
 *
 * SparkFun Dual-Port Logging Shield Arduino Library
 * 
 * This library facilitates communication with the Thing Plus Dual-Port Logging Shield over I<sup>2</sup>C.
 * 
 * Want to support open source hardware? Buy a board from SparkFun!
 * <br>SparkFun Thing Plus Dual-Port Logging Shield (DEV-19217): https://www.sparkfun.com/products/19217
 * 
 * This library was written by:
 * Paul Clark
 * SparkFun Electronics
 * March 2022
 * 
 * Please see LICENSE.md for the license information
 * 
 */

#ifndef __SFE_DUAL_PORT_LOGGING_IO__
#define __SFE_DUAL_PORT_LOGGING_IO__

#include <Arduino.h>
#include <Wire.h> // Needed for I2C communication

#include "SparkFun_Dual-Port_Logging_Shield_Constants.h"

/** Communication interface for the SparkFun Dual-Port Logging Shield */
class DUAL_PORT_LOGGING_SHIELD_IO
{
private:
  TwoWire* _i2cPort;
  byte _address;

public:
  /** @brief Create an object to communicate with the SparkFun Dual-Port Logging Shield over I2C. */
  DUAL_PORT_LOGGING_SHIELD_IO() {}

  /** Starts two wire interface. */
  bool begin(byte address, TwoWire& wirePort);

  /** Returns true if we get a reply from the I2C device. */
  bool isConnected();

  /** Read a single byte from a register. */
  bool readSingleByte(byte registerAddress, byte* buffer, byte waitMS = 0);

  /** Writes a single byte into a register. */
  bool writeSingleByte(byte registerAddress, byte value);

  /** Writes the register address only (as a command). */
  bool writeRegisterAddress(byte registerAddress);

  /** Reads multiple bytes from a register into buffer byte array. */
  bool readMultipleBytes(byte registerAddress, byte* buffer, byte packetLength, byte waitMS = 0);

  /** Writes multiple bytes to register from buffer byte array. */
  bool writeMultipleBytes(byte registerAddress, const byte* buffer, byte packetLength);
};

#endif // /__SFE_DUAL_PORT_LOGGING_IO__
