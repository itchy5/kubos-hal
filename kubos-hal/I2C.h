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

#include "FreeRTOS.h"
#include "queue.h"
#include <stdint.h>

#include "pins.h"

#ifndef K_NUM_I2CS
#define K_NUM_I2CS 2
#endif

#ifndef DEFAULT_I2C
#define DEFAULT_I2C 0
#endif

#define I2C_TIMEOUT_FLAG          ((uint32_t)35)     /* 35 ms */
#define I2C_TIMEOUT_ADDR_SLAVE    ((uint32_t)10000)  /* 10 s  */

#define I2C_QUEUE_LEN    8

#define I2C_ADDRESS        0x30F

typedef enum {
    K_I2C1 = 0,
	K_I2C2
} KI2CNum;

typedef struct {
	uint32_t AddressingMode;
	uint32_t ClockSpeed;
	uint32_t DualAddressMode;
	uint32_t DutyCycle;
	uint32_t GeneralCallMode;
	uint32_t NoStretchMode;
	uint32_t OwnAddress1;
	uint32_t OwnAddress2;

    uint8_t rx_queue_len;
    uint8_t tx_queue_len;
} KI2CConf;

typedef struct {
	int dev;
    KI2CConf conf;
    QueueHandle_t rx_queue;
    QueueHandle_t tx_queue;
} KI2C;


/* functions */
void k_i2c_init(KI2CNum i2c, KI2CConf *conf);
KI2CConf k_i2c_conf_defaults(void);
void k_i2c_default_init(void);
int k_master_transmit_interrupt_i2c(KI2CNum i2c, uint16_t DevAddress, uint8_t *ptr, int len);
int k_master_receive_interrupt_i2c(KI2CNum i2c, uint16_t DevAddress);
int k_i2c_get_state();
int k_i2c_get_error();

// private APIs
KI2C* kprv_i2c_get(KI2CNum i2c);
void kprv_i2c_dev_init(KI2CNum i2c);
int kprv_i2c_transmit_i2c(KI2CNum i2c, uint16_t DevAddress, uint8_t *ptr, int len);
int kprv_i2c_receive_i2c(KI2CNum i2c, uint16_t DevAddress);
int kprv_i2c_get_state();
int kprv_i2c_get_error();

BaseType_t queue_push(QueueHandle_t *queue, uint8_t c, TickType_t timeout, void *task_woken);
