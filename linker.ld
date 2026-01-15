OUTPUT_ARCH( "aarch64" )
ENTRY( _start )

SECTIONS
{
  . = 0xffff000040000000;

  . = ALIGN(0x1000);
  PROVIDE(_kernel_begin_ = .);

  .text : AT(0x40000000) {
    . = ALIGN(0x1000);
    PROVIDE(_text_begin_ = .);
    *(.text .text.*)
    . = ALIGN(0x1000);
    PROVIDE(_text_end_ = .);
  }

  .rodata : {
    . = ALIGN(16);
    PROVIDE(_rodata_begin_ = .);
    *(.srodata .srodata.*)
    . = ALIGN(16);
    *(.rodata .rodata.*)
    . = ALIGN(16);
    PROVIDE(_rodata_end_ = .);
  }

  .data : {
    . = ALIGN(16);
    PROVIDE(_data_begin_ = .);
    . = ALIGN(0x1000);
    PROVIDE(_stack_begin_ = .);
    . += 0x4 * 0x1000;
    PROVIDE(_identity_level_0_page_table_ = .);
    . += 0x1000;
    PROVIDE(_identity_level_1_page_table_ = .);
    . += 0x1000;
    PROVIDE(_identity_level_2_page_table_ = .);
    . += 0x1000;
    PROVIDE(_linear_level_0_page_table_ = .);
    . += 0x1000;
    PROVIDE(_linear_level_1_page_table_ = .);
    . += 0x1000;
    PROVIDE(_linear_level_2_page_table_ = .);
    . += 0x1000;
    *(.sdata .sdata.*)
    . = ALIGN(16);
    *(.data .data.*)
    . = ALIGN(16);
    PROVIDE(_data_end_ = .);
  }

  .bss : {
    . = ALIGN(16);
    PROVIDE(_bss_begin_ = .);
    *(.sbss .sbss.*)
    . = ALIGN(16);
    *(.bss .bss.*)
    . = ALIGN(16);
    PROVIDE(_bss_end_ = .);
  }

  . = ALIGN(0x1000);
  PROVIDE(_kernel_end_ = .);
}

_bss_size_ = (_bss_end_ - _bss_begin_) >> 3;
