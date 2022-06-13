/*
 * Copyright 2016 Dius Computing Pty Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the
 *   distribution.
 * - Neither the name of the copyright holders nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * @author Johny Mattsson <jmattsson@dius.com.au>
 */

#include "platform.h"
#include "platform_partition.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
//#include "../../bootloader/src/main/bootloader_config.h"
#include "esp_spi_flash.h"
#include "esp_flash_data_types.h"

#define partition_info_t	esp_partition_info_t
#define PARTITION_MAGIC		ESP_PARTITION_MAGIC
#define PARTITION_ADD		ESP_PARTITION_TABLE_ADDR

static inline bool possible_idx (uint8_t idx)
{
  return ((idx +1) * sizeof (partition_info_t)) < SPI_FLASH_SEC_SIZE;
}


bool platform_partition_info (uint8_t idx, platform_partition_t *info)
{
  if (!possible_idx (idx))
    return false;

  partition_info_t pi;
  esp_err_t err = spi_flash_read (
    PARTITION_ADD + idx * sizeof(pi), (uint32_t *)&pi, sizeof (pi));
  if (err != ESP_OK) {
    return false;
  }

  if (pi.magic != PARTITION_MAGIC) {
    return false;
  }

  memcpy (info->label, pi.label, sizeof (info->label));
  info->offs = pi.pos.offset;
  info->size = pi.pos.size;
  info->type = pi.type;
  info->subtype = pi.subtype;
  return true;
}


bool platform_partition_add (const platform_partition_t *info)
{
  partition_info_t *part_table = (partition_info_t *)malloc(SPI_FLASH_SEC_SIZE);
  if (!part_table)
    return false;
  esp_err_t err =
    spi_flash_read (PARTITION_ADD, (uint32_t *)part_table, SPI_FLASH_SEC_SIZE);
  if (err != ESP_OK)
    goto out;

  uint8_t idx = 0;
  for (; possible_idx (idx); ++idx)
    if (part_table[idx].magic != PARTITION_MAGIC)
      break;

  if (possible_idx (idx))
  {
    partition_info_t *slot = &part_table[idx];
    slot->magic = PARTITION_MAGIC;
    slot->type = info->type;
    slot->subtype = info->subtype;
    slot->pos.offset = info->offs;
    slot->pos.size = info->size;
    memcpy (slot->label, info->label, sizeof (slot->label));
    //memset (slot->reserved, 0xff, sizeof (slot->reserved));
	slot->flags = 0xffffffff;
    err = spi_flash_erase_sector (PARTITION_ADD / SPI_FLASH_SEC_SIZE);
    if (err == ESP_OK)
      err = spi_flash_write (
        PARTITION_ADD, (uint32_t *)part_table, SPI_FLASH_SEC_SIZE);
  }

out:
  free (part_table);
  return err == ESP_OK;
}
