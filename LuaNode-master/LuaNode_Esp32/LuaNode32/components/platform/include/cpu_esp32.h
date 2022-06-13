#ifndef _CPU_ESP32_H_
#define _CPU_ESP32_H_

#include "sdkconfig.h"

#define NUM_UART 3

#define INTERNAL_FLASH_SECTOR_SIZE      SPI_FLASH_SEC_SIZE
#define INTERNAL_FLASH_WRITE_UNIT_SIZE  4
#define INTERNAL_FLASH_READ_UNIT_SIZE	  4

#define FLASH_SEC_NUM   (flash_safe_get_sec_num())


#endif
