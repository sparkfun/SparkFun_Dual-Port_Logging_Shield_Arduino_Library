/*!
 * @file SparkFun_Dual-Port_Logging_Shield.h
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

#ifndef __SFE_DUAL_PORT_LOGGING__
#define __SFE_DUAL_PORT_LOGGING__

#include <Arduino.h>

#include "SparkFun_Dual-Port_Logging_Shield_Constants.h"
#include "SparkFun_Dual-Port_Logging_Shield_IO.h"

/** Communication interface for the SparkFun Dual-Port Logging Shield */
class sfeDualPortLoggingShield
{
public:
  /** @brief Class to communicate with the SparkFun Dual-Port Logging Shield */
  bool begin(byte deviceAddress = SFE_DUAL_PORT_LOGGING_DEFAULT_I2C_ADDRESS, TwoWire &wirePort = Wire);
  bool isConnected();
  bool setI2cAddress(byte address);
  byte getI2cAddress();
  byte getFirmwareVersion();
  bool setDefaultMode(sfe_dual_port_logging_mode_e mode);
  sfe_dual_port_logging_mode_e getDefaultMode();
  bool sleep();
  bool spiMode();
  bool sdioMode();

  // I2C communication object instance
  DUAL_PORT_LOGGING_SHIELD_IO sfeDualPortLoggingShield_io;
};

#endif // /__SFE_DUAL_PORT_LOGGING__
