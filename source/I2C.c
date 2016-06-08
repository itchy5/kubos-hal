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
#include <string.h>

static KI2C k_i2cs[K_NUM_I2CS];

KI2C* kprv_i2c_get(KI2CNum i2c)
{
    return &k_i2cs[i2c];
}

void k_i2c_init(KI2CNum i2c, KI2CConf *conf)
{
    KI2C *k_i2c = &k_i2cs[i2c];
    memcpy(&k_i2c->conf, conf, sizeof(KI2CConf));

    k_i2c->dev = i2c;
    k_i2c->rx_queue = xQueueCreate(k_i2c->conf.rx_queue_len, sizeof(uint8_t));
    k_i2c->tx_queue = xQueueCreate(k_i2c->conf.tx_queue_len, sizeof(uint8_t));

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
        .rx_queue_len = I2C_QUEUE_LEN,
        .tx_queue_len = I2C_QUEUE_LEN
    };
}

void k_i2c_default_init(void)
{
    KI2CConf conf = k_i2c_conf_defaults();
    k_i2c_init(DEFAULT_I2C, &conf);
}

int k_master_transmit_interrupt_i2c(KI2CNum i2c, uint16_t DevAddress, uint8_t* ptr, int len)
{
    return kprv_i2c_transmit_i2c(i2c, DevAddress, ptr, len);
}

int k_master_receive_interrupt_i2c(KI2CNum i2c, uint16_t DevAddress)
{
	return kprv_i2c_receive_i2c(i2c, DevAddress);
}

int k_i2c_get_state()
{
	return kprv_i2c_get_state();
}

int k_i2c_get_error()
{
	return kprv_i2c_get_error();
}
