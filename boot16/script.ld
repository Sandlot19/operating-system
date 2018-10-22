ENTRY(bootstart)
OUTPUT_FORMAT(elf64-x86-64)
TARGET(i8086)
SECTIONS
{
  .text 0x7c00 :
  {
    *(.boot)
    *(.text32)
    *(.text*)
  }
  .data :
  {
    *(.data*)
    *(.rodata*)
    *(.rdata*)
  }
  /DISCARD/ :
  {
    *(.note*)
    *(.comment*)
    *(.eh_frame)
  }
}
