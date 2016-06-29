/*
 * KubOS HAL
 * Copyright (C) 2016 Kubos Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/**
 * @defgroup I2C
 * @addtogroup I2C
 * @{
 */
/**
 * @brief KubOS-HAL I2C Interface
 * @author kubos.co
 */

#ifndef K_I2C_H
#define K_I2C_H

#include <stdint.h>
#include "FreeRTOS.h"
#include "semphr.h"

/**
 * Number of i2c buses available. Derived from value in target.json
 * @code
 * "config": {
 *   "hardware": {
 *     "i2ccount": "2"
 *   }
 * }
 * @endcode
 */
#ifndef K_NUM_I2CS
#define K_NUM_I2CS YOTTA_CFG_HARDWARE_I2CCOUNT
#endif

/**
 * Default i2c bus. Derived from value in target.json
 * @code
 * "config": {
 *   "defaults": {
 *     "i2c": "K_I2C1"
 *   }
 * }
 * @endcode
 */
#define DEFAULT_I2C YOTTA_CFG_HARDWARE_DEFAULTS_I2C

/**
 * Available i2c buses
 */
typedef enum {
    K_I2C1 = 0,
    K_I2C2 = 1
} KI2CNum;

/**
 * Expected addressing mode of i2c bus
 */
typedef enum {
    K_ADDRESSINGMODE_7BIT = 0,
    K_ADDRESSINGMODE_10BIT
} I2CAddressingMode;

/**
 * Expected role of i2c bus
 * @warning Only the Master role is available as of v0.0.4
 */
typedef enum {
    K_MASTER = 0,
    K_SLAVE
} I2CRole;

/**
 * i2c configuration structure
 */
typedef struct {
	I2CAddressingMode AddressingMode;
    I2CRole Role;
	uint32_t ClockSpeed;
} KI2CConf;

/**
 * i2c bus data structure
 */
typedef struct {
	KI2CNum bus_num;
    KI2CConf conf;
    SemaphoreHandle_t i2c_lock;
} KI2C;

/**
 * i2c function status
 */
typedef enum {
    I2C_OK = 0,
    I2C_ERROR
} KI2CStatus;

/**
 * Setup and enable i2c bus
 * @param i2c i2c bus to initialize
 * @param conf config values to initialize with
 */
void k_i2c_init(KI2CNum i2c, KI2CConf *conf);

/**
 * Terminate i2c bus
 * @param i2c i2c bus to terminate
 */
void k_i2c_terminate(KI2CNum i2c);

/**
 * Generate KI2CConf with default I2C values
 * @return KI2CConf
 */
KI2CConf k_i2c_conf_defaults(void);

/**
 * Init DEFAULT_I2C bus with default config values
 */
void k_i2c_default_init();

/**
 * Initialize i2c device with default config values
 * @param i2c I2C bus num to initialize
 */
void k_i2c_default_dev_init(KI2CNum i2c);

/**
 * Transmit data over i2c bus to specified address
 * @param i2c i2c bus to transmit over
 * @param addr address of target i2c device
 * @param ptr pointer to data buffer
 * @param len length of data in buffer
 * @return int I2C_OK on success, I2C_ERROR on error
 */
KI2CStatus k_i2c_write(KI2CNum i2c, uint16_t addr, uint8_t *ptr, int len);

/**
 * Read data over i2c bus from specified address
 * @param i2c i2c bus to read from
 * @param addr address of target i2c device
 * @param ptr pointer to data buffer
 * @param len length of data to read
 * @return int I2C_OK on success, I2C_ERROR on error
 */
KI2CStatus k_i2c_read(KI2CNum i2c, uint16_t addr, uint8_t *ptr, int len);

/**
 * Fetches i2c bus data structure
 * @param i2c number of i2c bus to fetch
 * @return KI2C* pointer to data structure
 */
KI2C* kprv_i2c_get(KI2CNum i2c);

/**
 * Low level hal device initialization
 * This is implemented by the device specific hal
 * @param i2c i2c bus to initialize
 */
void kprv_i2c_dev_init(KI2CNum i2c);

/**
 * Low level hal i2c termination
 * This is implemented by the device specific hal
 * @param i2c i2c bus to terminate
 */
void kprv_i2c_dev_terminate(KI2CNum i2c);

/**
 * Low level hal i2c write (as master)
 * This is implemented by the device specific hal
 * @param i2c i2c bus to write from
 * @param addr i2c addr to write to
 * @param ptr data buffer
 * @param len length of data in buffer
 * @return KI2CStatus I2C_OK on success, I2C_ERROR on error
 */
KI2CStatus kprv_i2c_master_write(KI2CNum i2c, uint16_t addr, uint8_t *ptr, int len);

/**
 * Low level hal i2c read (as master)
 * This is implemented by the device specific hal
 * @param i2c i2c bus to read from
 * @param addr i2c addr to read from
 * @param ptr data buffer
 * @param len length of data expected to read
 * @return KI2CStatus I2C_OK on success, I2C_ERROR on error
 */
KI2CStatus kprv_i2c_master_read(KI2CNum i2c, uint16_t addr, uint8_t *ptr, int len);

/**
 * Low level hal i2c write (as slave)
 * This is implemented by the device specific hal
 * @warning Not implemented as of v0.0.4
 * @param i2c i2c bus to write from
 * @param addr i2c addr to write to
 * @param ptr data buffer
 * @param len length of data in buffer
 * @return KI2CStatus I2C_OK on success, I2C_ERROR on error
 */
KI2CStatus kprv_i2c_slave_write(KI2CNum i2c, uint16_t addr, uint8_t *ptr, int len);

/**
 * Low level hal i2c read (as slave)
 * This is implemented by the device specific hal
 * @warning Not implemented as of v0.0.4
 * @param i2c i2c bus to read from
 * @param addr i2c addr to read from
 * @param ptr data buffer
 * @param len length of data expected to read
 * @return KI2CStatus I2C_OK on success, I2C_ERROR on error
 */
KI2CStatus kprv_i2c_slave_read(KI2CNum i2c, uint16_t addr, uint8_t *ptr, int len);

#endif

/* @} */
