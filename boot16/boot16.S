/* REAL-mode entry for BIOS->Bootloader
 * Jacob Rutheford
 * 25 August 2018
 */

.intel_syntax noprefix

.code16
.section .boot

/* Set the location to load the 32 bit boot loader */
.equ BOOT32_START, 0x8000

.global bootstart
bootstart:
  jmp   0:bootjump

READERROR:        .asciz "Error reading"
A20ERROR:         .asciz "A20 Error"
DONE:             .asciz "Done. Loading kernel"
INFO:             .asciz "Working in 16 bit Real Mode..."
EXTENSIONERROR:   .asciz "Extension error"

bootjump:
  /* cli = Clear interrupt flag */
  cli
  xor   ax, ax
  mov   ds, ax
  mov   es, ax
  mov   gs, ax
  mov   ss, ax
  mov   fs, ax

  mov   sp, 0x5000

  /*
   * Interrupt 0x13 calls the BIOS. Since ah=0 the BIOS will perform a
   * "disk controller reset" which will ensure that the disk controller is
   * actually ready to read.
   */
  int   0x13

  /* A20 bit */
  mov   ax, 0x2401

  int   0x15

  /*
   * If the carry flag is set, then there was an error.
   * jc a20error
   */

  mov   ax, 0x0
  mov   es, ax

  mov   ah, 2
  mov   al, 8 /* number of sectors */
  mov   ch, 0 /* cylinder to read */
  mov   dh, 0 /* head to read */
  mov   cl, 1 /* sector to read */
  lea   bx, [BOOT32_START]
  mov   dl, 0x80
  int   0x13

  lea   si, [INFO] /* print function expects string to be in si */
  call  print
  
  mov   ax, cr0
  or    ax, 1
  mov   cr0, ax

  lgdt  [GDT32]

  mov   ax, 16
  mov   ds, ax

  lea   si, [DONE] /* print function expects string to be in si */
  call  print

  jmp   8:0x8200

print:
  mov   ah, 0x0E /* put the "display char" command in the command register */

.printchar:
  lodsb /* load byte at address SI into AL, and increment SI */
  cmp   al, 0
  je    .done
  int   0x10 /* call the BIOS interrupt */
  jmp   .printchar

.done:
  ret


GDT32.NULL:
  .quad 0

GDT32.CODE:
  .int  (0xffff) /* segment limit */
  .int  (0b11 << 11) /* code segment */ | (1 << 15) /* present */ | (0xf << 16) /* segment limit */ | (1 <<  22) /* set default operand size to 32 bits */ | (1 << 23) /* granularity */

GDT32.DATA:
  .int  (0xffff) /* segment limit */
  .int  (1 << 9) /* writable */ | (0b10 << 11) /* data segment */ | (1 << 15) /* present */ | (0xf << 16) /* segment limit */ | (1 << 22) /* default operand size 32 bits */ | (1 << 23) /* granularity */

GDT32:
  .word .-GDT32.NULL
  .int  GDT32.NULL

  .space  510-(.-bootstart), 0
  .word 0xAA55
