ENTRY(_start)
OUTPUT_FORMAT(elf64-x86-64)
TARGET(x86-64)
SECTIONS
{
  .text 0x100000:
  {
    _mem_start = .;
    *(.text32)
    *(.text64)
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
    bss_top = .;
    *(.bss)
    . = ALIGN(8);
    bss_bottom = .;
  }

  /DISCARD/ :
  {
    *(.note*)
    *(.comment*)
    *(.eh_frame)
  }

  _mem_end = .;
}
