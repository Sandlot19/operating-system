#include "terminal.h"
#include "asmutils.h"

namespace
{
  constexpr uint8_t kDefaultFg = 0xa;
  constexpr uint8_t kDefaultBg = 0x0;
  constexpr uint8_t kDefaultWidth = 0x80;
  constexpr uint8_t kDefaultHeight = 0x20;
  constexpr uint64_t kVgaLocation = 0xB8000;
}

Terminal& Terminal::GetTerm()
{
  static Terminal term;
  return term;
}

Terminal::Terminal() {}

uint16_t Terminal::ConvertToTermChar(uint8_t fg, uint8_t bg, uint8_t character)
{
  //  4     4     8
  //[ bg ][ fg ][ char ] 
  return (static_cast<uint16_t>(bg) << 12 |
          static_cast<uint16_t>(fg) << 8 |
          static_cast<uint16_t>(character));
}

uint16_t Terminal::ConvertToTermCursor(uint8_t x, uint8_t y)
{
  return (y * kDefaultWidth + x);
}

void Terminal::MoveCursorTo(uint8_t x, uint8_t y)
{
  uint16_t cursor_pos = ConvertToTermCursor(x, y);
  asmutils::out_byte(0x3d4, 0x0f);
  asmutils::out_byte(0x3d5, static_cast<uint8_t>(cursor_pos & 0xff));
  asmutils::out_byte(0x3d4, 0x0e);
  asmutils::out_byte(0x3d5, static_cast<uint8_t>((cursor_pos >> 8) & 0xff));

  cursor_x_ = x;
  cursor_y_ = y;
}


void Terminal::Write(const char* message)
{
  int i = 0;
  volatile uint16_t* vga_buf = reinterpret_cast<uint16_t*>(kVgaLocation);
  while(message[i] != '\0') {
    vga_buf[i] = ConvertToTermChar(kDefaultFg, kDefaultBg, message[i]);
    cursor_x_++;
    if (cursor_x_ >= kDefaultWidth) {
      cursor_x_ = 0;
      cursor_y_++;
    }
    i++;
  }
}

void Terminal::ClearScreen()
{
  volatile uint16_t* vga_buf = reinterpret_cast<uint16_t*>(kVgaLocation);
  for (int i = 0; i < kDefaultWidth * kDefaultHeight; i++) {
    vga_buf[i] = ConvertToTermChar(kDefaultFg, kDefaultBg, ' ');
  }

  MoveCursorTo(0, 0);
}
