#include "boot32_c.h"

#define MAX_READ_SECTORS 128
#define EXIT_FAILURE 0
#define BOCHS_DEBUG(c) out_byte(0xE9, c)

static inline uint8_t in_byte(uint16_t port)
{
  uint8_t data = -1;
  asm volatile (
      "inb %1, %0"
      : "=a"(data)
      : "Nd"(port)
      :
      );
  return data;
}

static inline uint16_t in_word(uint16_t port)
{
  uint16_t data = -1;
  asm volatile (
      "inw %1, %0"
      : "=a"(data)
      : "d"(port)
      :
      );
  return data;
}

static inline void out_byte(uint16_t port, uint8_t data)
{
  asm volatile (
      "outb %0, %1"
      :
      : "a"(data), "Nd"(port)
      :
      );
}

bool AtaRead(uint16_t* buffer, uint32_t lba, uint32_t sectors, uint8_t drive)
{
  uint32_t sectors_read;
  if (sectors < 1) return false;

  for (sectors_read = 0; sectors_read < sectors;
       sectors_read += MAX_READ_SECTORS, lba += MAX_READ_SECTORS) {

    uint8_t sectors_to_read = ((sectors - sectors_read) > MAX_READ_SECTORS)
                                ? MAX_READ_SECTORS
                                : sectors - sectors_read;

    // Specify that we want to talk to the slave drive in LBA format
    out_byte(DRIVE_HEAD_REGISTER_PORT, 0xe0 | (drive << 4));

    // This does nothing
    out_byte(ERROR_FEATURE_REGISTER_PORT, 0);

    // Number of sectors to read
    out_byte(SECTOR_COUNT_REGISTER_PORT, sectors_to_read);

    // Specify LBA[7:0]
    out_byte(SECTOR_NUMBER_REGISTER_PORT, (uint8_t)lba);
    // Specify LBA[15:8]
    out_byte(CYLINDER_LOW_REGISTER_PORT, (uint8_t)(lba >> 8));
    // Specify LBA[23:16]
    out_byte(CYLINDER_HIGH_REGISTER_PORT, (uint8_t)(lba >> 16));

    out_byte(STATUS_COMMAND_REGISTER_PORT, READ_SECTORS_COMMAND);

    for (uint32_t j = 0; j < sectors_to_read; j++) {

      /* Busy loop to wait for the busy bit to be set to 0. If the busy bit is
       * set, then the drive is not ready to produce data. */
      while (in_byte(ALTERNATE_STATUS_REGISTER_PORT) & (1 << BUSY_BIT_POSITION)) {
        asm volatile("pause\n");
        for (volatile uint32_t i = 0; i < 1000; i++);
      }

      /* Busy loop has ended, the drive is ready to be read from */
      for (uint32_t i = 0; i < 256; i++) {
        *(buffer++) = in_word(DATA_REGISTER_PORT);
      }
    }
  }

  return true;
}

int main(void)
{
  return 0;
}
