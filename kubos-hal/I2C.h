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

#include <stdint.h>


#define K_NUM_I2CS 2

/* default I2C */
#define DEFAULT_I2C 0

/* other devices */
#define I2C_DEVICE_1 0
#define I2C_DEVICE_2 1


typedef enum {
    K_I2CDev1 = 0,
	K_I2CDev2
} KI2CDevNum;

typedef enum {
	K_I2C1 = 0,
	K_I2C2
} KI2CBusNum;

typedef struct {
	uint32_t AddressingMode;
	uint32_t ClockSpeed;
	uint32_t DualAddressMode;
	uint32_t DutyCycle;
	uint32_t GeneralCallMode;
	uint32_t NoStretchMode;
	uint32_t OwnAddress1;
	uint32_t OwnAddress2;
	uint32_t SlaveAddress;
} KI2CConf;

typedef struct {
	KI2CBusNum bus_num;
    KI2CConf conf;
    int status;
} KI2C;

/* functions */
void k_i2c_init(KI2CDevNum i2c, KI2CBusNum i2c_bus, KI2CConf *conf);
KI2CConf k_i2c_conf_defaults(void);
void k_i2c_default_init(void);
void k_i2c_default_dev_init(KI2CDevNum i2c, KI2CBusNum i2c_bus);
int k_master_transmit_i2c(KI2CDevNum i2c, uint8_t *ptr, int len);
int k_master_receive_i2c(KI2CDevNum i2c, uint8_t *ptr, int len);

// private APIs
KI2C* kprv_i2c_get(KI2CDevNum i2c);
void kprv_i2c_dev_init(KI2CDevNum i2c);
int kprv_i2c_transmit_i2c(KI2CDevNum i2c, uint8_t *ptr, int len);
int kprv_i2c_receive_i2c(KI2CDevNum i2c, uint8_t *ptr, int len);


