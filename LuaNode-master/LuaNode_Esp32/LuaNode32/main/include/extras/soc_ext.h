// Copyright 2010-2016 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef _ESP32_SOC_EXT_H_
#define _ESP32_SOC_EXT_H_

#define FUNC_GPIO0						0
#define FUNC_GPIO1						3
#define FUNC_GPIO2						2
#define FUNC_GPIO3						3
#define FUNC_GPIO4						0
#define FUNC_GPIO5						0
#define FUNC_GPIO9						3
#define FUNC_GPIO10						3
#define FUNC_GPIO12						3
#define FUNC_GPIO13						3
#define FUNC_GPIO14						3
#define FUNC_GPIO15						3
#define PERIPHS_IO_MUX                  0x60009000

#define PERIPHS_RTC_BASEADDR            0x60008000
#define REG_RTC_BASE					PERIPHS_RTC_BASEADDR
#define RTC_GPIO_IN_DATA				(REG_RTC_BASE + 0x08C)
#define PAD_XPD_DCDC_CONF				(REG_RTC_BASE + 0x0A0)
#define RTC_GPIO_OUT					(REG_RTC_BASE + 0x068)
#define RTC_GPIO_CONF					(REG_RTC_BASE + 0x090)

#define GPIO_STATUS_W1TC_ADDRESS      0x24
#define GPIO_STATUS_ADDRESS                  0x1c

#define ETS_UART0_INUM                          5

#endif /* _ESP32_SOC_H_ */
