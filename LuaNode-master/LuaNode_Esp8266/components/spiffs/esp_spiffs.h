/*
 * ESPRSSIF MIT License
 *
 * Copyright (c) 2015 <ESPRESSIF SYSTEMS (SHANGHAI) PTE LTD>
 *
 * Permission is hereby granted for use on ESPRESSIF SYSTEMS ESP8266 only, in which case,
 * it is free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef __ESP_SPIFFS_H__
#define __ESP_SPIFFS_H__

#include "spiffs.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \defgroup Spiffs_APIs Spiffs APIs
  * @brief Spiffs APIs
  *
  * More details about spiffs on https://github.com/pellepl/spiffs
  *
  */

/** @addtogroup Spiffs_APIs
  * @{
  */

struct esp_spiffs_config {
    uint32 phys_size;        /**< physical size of the SPI Flash */
    uint32 phys_addr;        /**< physical offset in spi flash used for spiffs, must be on block boundary */
    uint32 phys_erase_block; /**< physical size when erasing a block */

    uint32 log_block_size;   /**< logical size of a block, must be on physical block size boundary and must never be less than a physical block */
    uint32 log_page_size;    /**< logical size of a page, at least log_block_size/8  */

    uint32 fd_buf_size;      /**< file descriptor memory area size */
    uint32 cache_buf_size;   /**< cache buffer size */
};

/**
  * @brief  Initialize spiffs
  *
  * @param  struct esp_spiffs_config *config : ESP8266 spiffs configuration
  *
  * @return 0         : succeed
  * @return otherwise : fail
  */
sint32 esp_spiffs_init(struct esp_spiffs_config *config);

/**
  * @brief  Deinitialize spiffs
  *
  * @param  uint8 format : 0, only deinit; otherwise, deinit spiffs and format.
  *
  * @return null
  */
void esp_spiffs_deinit(uint8 format);


size_t myspiffs_init(void);
void myspiffs_deinit(void);

int myspiffs_open(const char *name, int flags);
size_t myspiffs_write( int fd, const void* ptr, size_t len );
size_t myspiffs_read( int fd, void* ptr, size_t len);
int myspiffs_close( int fd );
int myspiffs_lseek( int fd, int off, int whence );
int myspiffs_eof( int fd );
int myspiffs_tell( int fd );
int myspiffs_getc( int fd );
int myspiffs_ungetc( int c, int fd );
int myspiffs_flush( int fd );
int myspiffs_error( int fd );
void myspiffs_clearerr( int fd );
int myspiffs_check( void );
int myspiffs_rename( const char *old, const char *newname );
int myspiffs_format( void );
//void myspiffs_opendir( const char *dir, spiffs_DIR *d );
//spiffs_dirent *myspiffs_readdir( spiffs_DIR *dir, spiffs_dirent *pe );
void myspiffs_remove( char *name );
void myspiffs_fsinfo( uint32 *total, uint32 *used );

size_t myspiffs_size( int fd );

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __ESP_SPIFFS_H__ */
