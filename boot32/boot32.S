/* boot32.S
 * 32-bit bootloader 
 * 32 bit Protected mode bootloader to give control to the kernel
 * Jacob Rutherford
 */
.intel_syntax noprefix

.code32
.section .text32
.global boot32_start

boot32_start:
  /* Set up the stack pointer to 0x5000 */
  mov     esp, 0x5000
  call    main

  test    eax, eax
  jz      1f

  jmp     eax

1:
  hlt
  jmp     1b
