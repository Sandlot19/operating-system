#ifndef _BOOT32_C_H_
#define _BOOT32_C_H_
#include <stdbool.h>
#include <stdint.h>

// Port numbers for respective registers
// ATA Specification Section 4.0 Pg 13
#define DATA_REGISTER_PORT              0x1F0
#define ERROR_FEATURE_REGISTER_PORT     0x1F1
#define SECTOR_COUNT_REGISTER_PORT      0x1F2
#define SECTOR_NUMBER_REGISTER_PORT     0x1F3
#define CYLINDER_LOW_REGISTER_PORT      0x1F4
#define CYLINDER_HIGH_REGISTER_PORT     0x1F5
#define DRIVE_HEAD_REGISTER_PORT        0x1F6
#define STATUS_COMMAND_REGISTER_PORT    0x1F7
#define ALTERNATE_STATUS_REGISTER_PORT  0x3F6

// See ATA Specification Section 4.1
#define BUSY_BIT_POSITION               7

// See ATA Specification Section 5.4.10
#define READ_SECTORS_COMMAND            0x20

bool AtaRead(uint16_t* buffer, uint32_t lba, uint32_t sectors, uint8_t drive);

#endif // _BOOT32_C_H_
