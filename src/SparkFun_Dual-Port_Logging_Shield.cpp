/*!
 * @file SparkFun_Dual-Port_Logging_Shield.cpp
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

#include "SparkFun_Dual-Port_Logging_Shield.h"

/**************************************************************************/
/*!
    @brief  Begin communication with the SparkFun Dual-Port Logging Shield
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
bool sfeDualPortLoggingShield::begin(byte deviceAddress, TwoWire &wirePort)
{
  return (sfeDualPortLoggingShield_io.begin(deviceAddress, wirePort));
}

/**************************************************************************/
/*!
    @brief  Check that the SparkFun Dual-Port Logging Shield is awake and communicating.
            This function is called by begin
    @return True if communication with the Dual-Port Logging Shield was successful, otherwise false.
*/
/**************************************************************************/
bool sfeDualPortLoggingShield::isConnected()
{
  return (sfeDualPortLoggingShield_io.isConnected());
}

/**************************************************************************/
/*!
    @brief  Change the Dual-Port Logging Shield's I2C address.
            You will need to call .begin again using the new address to
            re-establish communication with the Dual-Port Logging Shield.
    @param  address
            The new I2C address.
    @return True if communication with the Dual-Port Logging Shield was successful, otherwise false.
*/
/**************************************************************************/
bool sfeDualPortLoggingShield::setI2cAddress(byte address)
{
  bool result = sfeDualPortLoggingShield_io.writeSingleByte(SFE_DUAL_PORT_LOGGING_REGISTER_I2C_ADDRESS, address);
  if (result)
    delay(SFE_DUAL_PORT_LOGGING_EEPROM_UPDATE_DELAY); // Wait for the eeprom to be updated
  return (result);
}

/**************************************************************************/
/*!
    @brief  Just for fun, read back the Dual-Port Logging Shield's I2C address.
            This proves that I2C communication is possible and that the Dual-Port Logging Shield
            has the correct address stored in eeprom.
    @return The Dual-Port Logging Shield's I2C address. Returns zero if an error occurred.
*/
/**************************************************************************/
byte sfeDualPortLoggingShield::getI2cAddress()
{
  byte address;
  bool result = sfeDualPortLoggingShield_io.readSingleByte(SFE_DUAL_PORT_LOGGING_REGISTER_I2C_ADDRESS, &address);
  if (!result)
    address = 0;
  return (address);
}

/**************************************************************************/
/*!
    @brief  Get the Dual-Port Logging Shield firmware version.
    @return The firmware version if read successfully, 0x00 if not.
            The firmware version is: Major Version (4-bits << 4) | Minor Version (4-bits).
            E.g. 0x10 is: v1.0, Major Version 1, Minor Version 0.
*/
/**************************************************************************/
byte sfeDualPortLoggingShield::getFirmwareVersion()
{
  byte version;
  bool result = sfeDualPortLoggingShield_io.readSingleByte(SFE_DUAL_PORT_LOGGING_REGISTER_FIRMWARE_VERSION, &version);
  if (!result)
    version = 0;
  return (version);
}

/**************************************************************************/
/*!
    @brief  Change the Dual-Port Logging Shield's default mode.
    @param  mode
            The new default mode.
    @return True if communication with the Dual-Port Logging Shield was successful, otherwise false.
*/
/**************************************************************************/
bool sfeDualPortLoggingShield::setDefaultMode(sfe_dual_port_logging_mode_e mode)
{
  bool result = sfeDualPortLoggingShield_io.writeSingleByte(SFE_DUAL_PORT_LOGGING_REGISTER_DEFAULT_MODE, mode);
  if (result)
    delay(SFE_DUAL_PORT_LOGGING_EEPROM_UPDATE_DELAY); // Wait for the eeprom to be updated
  return (result);
}

/**************************************************************************/
/*!
    @brief  Read the Dual-Port Logging Shield's default mode.
    @return The Dual-Port Logging Shield's default mode. SFE_DUAL_PORT_LOGGING_MODE_UNKNOWN indicates a read error.
*/
/**************************************************************************/
sfe_dual_port_logging_mode_e sfeDualPortLoggingShield::getDefaultMode()
{
  sfe_dual_port_logging_mode_e mode = SFE_DUAL_PORT_LOGGING_MODE_UNKNOWN;
  bool result = sfeDualPortLoggingShield_io.readSingleByte(SFE_DUAL_PORT_LOGGING_REGISTER_DEFAULT_MODE, (byte *)&mode);
  if (!result)
    mode = SFE_DUAL_PORT_LOGGING_MODE_UNKNOWN;
  return (mode);
}

/**************************************************************************/
/*!
    @brief  Power off the microSD card and put the Dual-Port Logging Shield into deep sleep.
            You will need to call .sdioMode or .spiMode to wake the shield.
    @return True if communication with the Dual-Port Logging Shield was successful, otherwise false.
*/
/**************************************************************************/
bool sfeDualPortLoggingShield::sleep()
{
  bool result = sfeDualPortLoggingShield_io.writeRegisterAddress(SFE_DUAL_PORT_LOGGING_REGISTER_SLEEP);
  return (result);
}

/**************************************************************************/
/*!
    @brief  Put the Dual-Port Logging Shield into SPI mode.
    @return True if communication with the Dual-Port Logging Shield was successful, otherwise false.
*/
/**************************************************************************/
bool sfeDualPortLoggingShield::spiMode()
{
  bool result = sfeDualPortLoggingShield_io.writeRegisterAddress(SFE_DUAL_PORT_LOGGING_REGISTER_SPI_MODE);
  return (result);
}

/**************************************************************************/
/*!
    @brief  Put the Dual-Port Logging Shield into SDIO mode.
    @return True if communication with the Dual-Port Logging Shield was successful, otherwise false.
*/
/**************************************************************************/
bool sfeDualPortLoggingShield::sdioMode()
{
  bool result = sfeDualPortLoggingShield_io.writeRegisterAddress(SFE_DUAL_PORT_LOGGING_REGISTER_SDIO_MODE);
  return (result);
}

