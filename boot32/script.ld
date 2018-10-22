ENTRY(boot32_start)
OUTPUT_FORMAT(elf32-i386)
TARGET(i386)
SECTIONS
{
  .text 0x8200 :
  {
    *(.text32)
    *(.text*)
  }
  .data :
  {
    *(.data*)
    *(.rodata*)
    *(.rdata*)
  }
  .bss : ALIGN(4K)
  {
    *(.bss)
  }
  /DISCARD/ :
  {
    *(.note*)
    *(.comment*)
    *(.eh_frame)
  }
}
