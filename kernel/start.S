.intel_syntax noprefix
.code32
.section .text32

.global _start
_start:
  mov   eax, cr4
  or    eax, 1 << 5
  mov   cr4, eax

  mov   edi, 0x1000 | (1 << 4) /* PCD */
  mov   cr3, edi

  mov   edi, 0x1000

  mov   DWORD PTR [edi], 0x2000 /* PDP address */ | (1 << 1) /* R/W */ | (1 << 0) /* P */

  mov   DWORD PTR [edi+4], 0

  mov   ecx, 511

1:
  add   edi, 8 /* 8 bytes per entry */
  mov   DWORD PTR [edi], 0
  mov   DWORD PTR [edi+4], 0
  loop  1b
