//#define INTERNAL_FLASH_SECTOR_SIZE	SPI_FLASH_SEC_SIZE
#define INTERNAL_FLASH_SECTOR_SIZE	4096
#define INTERNAL_FLASH_WRITE_UNIT_SIZE  4
#define INTERNAL_FLASH_READ_UNIT_SIZE	  4

// Determine whether an address is in the flash-cache range
static inline bool is_cache_flash_addr (uint32_t addr)
{
  return addr >= 0x3F400000 && addr < 0x3FC00000;
}

// Internal flash partitions
#define PLATFORM_PARTITION_TYPE_APP     0x00
#define PLATFORM_PARTITION_TYPE_DATA    0x01
#define PLATFORM_PARTITION_TYPE_NODEMCU 0xC2

#define PLATFORM_PARTITION_SUBTYPE_APP_FACTORY 0x00
#define PLATFORM_PARTITION_SUBTYPE_APP_OTA(n)  (0x10+n)
#define PLATFORM_PARTITION_SUBTYPE_APP_TEST    0x20

#define PLATFORM_PARTITION_SUBTYPE_DATA_OTA    0x00
#define PLATFORM_PARTITION_SUBTYPE_DATA_RF     0x01
#define PLATFORM_PARTITION_SUBTYPE_DATA_WIFI   0x02

#define PLATFORM_PARTITION_SUBTYPE_NODEMCU_SPIFFS 0x00

typedef struct {
  uint8_t  label[16];
  uint32_t offs;
  uint32_t size;
  uint8_t  type;
  uint8_t  subtype;
} platform_partition_t;

/**
 * Obtain partition information for the internal flash.
 * @param idx Which partition index to load info for.
 * @param info Buffer to store the info in.
 * @returns True if the partition info was loaded, false if not (e.g. no such
 *   partition idx).
 */
bool platform_partition_info (uint8_t idx, platform_partition_t *info);

/**
 * Appends a partition entry to the partition table, if possible.
 * Intended for auto-creation of a SPIFFS partition.
 * @param info The partition definition to append.
 * @returns True if the partition could be added, false if not.
 */
bool platform_partition_add (const platform_partition_t *info);
