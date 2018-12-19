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

  // Set up the PDP (address 0x2000)
  // 0x2000 follows right behind PML4
  // PML4 is at 0x1000 + (512 entries * 8 bytes per) = 0x2000
  mov   edi, 0x2000
  mov   DWORD PTR [edi], (1 << 7) /* Gb page */ | (1 << 1) /* R/W */ | (1 << 0) /* P */
  mov   DWORD PTR [edi+4], 0

  // zero out the rest of the entries
  mov   ecx, 511

1:
  add   edi, 8
  mov   DWORD PTR [edi], 0
  mov   DWORD PTR [edi+4], 0
  loop  1b

  lgdt  [GDT64]

  mov   ecx, 0xc0000080
  rdmsr
  or    eax, (1 << 0) /* SCE */ | (1 << 8) /* LME */ | (1 << 11) /* NXE */
  wrmsr

  // should be in long mode here, so we need to enable the MMU

  // Enable MMU
  mov   eax, cr0
  or    eax, 1 << 31
  mov   cr0, eax

  // Long mode active should be set now that MMU is active
  // Jump to 64 bit area

  // Data descriptor is the second entry and each entry is 8 bytes. The first
  // entry is just like the 32-bit GDT (NULL). So the data segment starts at
  // entry #8 and the code segment is the next one (8+8=16)
  mov   ax, 8
  mov   ds, ax
  jmp   16:_start64

.code64
.section .text64
_start64:
  mov   esp, 0x5000

  // jump to C++ code
  call  main

  // if main ever returns, we fucked up
  hlt

GDT64.begin:
  // NULL selector
  .quad 0

GDT64.kerneldata:
  .int  0
  .int  (1 << 15) /* Present */ | (0b10 << 11) /* Data Segment */

GDT64.kernelcode:
  .int  0
  .int  (1 << 15) /* Present */ | (0b11 << 11) /* Code Segment */ | (1 << 21) /* Long mode code */

GDT64.end:

GDT64:
  // Two byte length of the GDT comes first, similarly to 32-bit GDT
  .short  GDT64.end - GDT64.begin

  // 8 byte pointer to the GDT comes next, unlike 32-bit GDT
  .quad   GDT64.begin
