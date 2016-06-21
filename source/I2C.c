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

#include "kubos-hal/I2C.h"
//#include "msp430f5529-hal/I2C.h"

#include <string.h>

static KI2C k_i2cs[K_NUM_I2CS];

KI2C* kprv_i2c_get(KI2CDevNum i2c)
{
    return &k_i2cs[i2c];
}

void k_i2c_init(KI2CDevNum i2c, KI2CBusNum i2c_bus, KI2CConf *conf)
{
    KI2C *k_i2c = &k_i2cs[i2c];
    memcpy(&k_i2c->conf, conf, sizeof(KI2CConf));

    /* select bus */
    k_i2c->bus_num = i2c_bus;
    /* call device init */
    kprv_i2c_dev_init(i2c);
}

KI2CConf k_i2c_conf_defaults(void)
{
    return (KI2CConf) {
        .AddressingMode = 0,
        .ClockSpeed = 0,
        .DualAddressMode = 0,
        .DutyCycle = 0,
        .GeneralCallMode = 0,
        .NoStretchMode = 0,
        .OwnAddress1 = 0xFE,
        .OwnAddress2 = 0xFE,
    };
}

void k_i2c_default_init(void)
{
    KI2CConf conf = k_i2c_conf_defaults();
    k_i2c_init(DEFAULT_I2C, DEFAULT_I2C, &conf);
}

void k_i2c_default_dev_init(KI2CDevNum i2c, KI2CBusNum i2c_bus)
{
    KI2CConf conf = k_i2c_conf_defaults();
    k_i2c_init(i2c, i2c_bus, &conf);
}

int k_master_transmit_i2c(KI2CDevNum i2c, uint8_t* ptr, int len)
{
    return kprv_i2c_transmit_i2c(i2c, ptr, len);
}

int k_master_receive_i2c(KI2CDevNum i2c, uint8_t *ptr, int len)
{
	return kprv_i2c_receive_i2c(i2c, ptr, len);
}


