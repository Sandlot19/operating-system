#ifndef _BOOT32_H_
#define _BOOT32_H_
#include <stdbool.h>
#include <stdint.h>

// Port numbers for respective registers
// ATA Specification Section 4.0 Pg 13
#define ERROR_FEATURE_REGISTER_PORT 0x1F1
#define SECTOR_COUNT_REGISTER_PORT 0x1F2
#define SECTOR_NUMBER_REGISTER_PORT 0x1F3
#define CYLINDER_LOW_REGISTER_PORT 0x1F4
#define CYLINDER_HIGH_REGISTER_PORT 0x1F5
#define DRIVE_HEAD_REGISTER_PORT 0x1F6
#define STATUS_COMMAND_REGISTER_PORT 0x1F7

bool AtaRead(uint16_t* buffer, uint32_t lba, uint32_t sectors, uint8_t drive);

#endif // _BOOT32_h_
