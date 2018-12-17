#include "terminal.h"
#include "asmutils.h"

#include <cstdarg>

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
  static Terminal term(kVgaLocation);
  return term;
}

Terminal::Terminal(uint64_t vga_location)
  : vga_buf_(reinterpret_cast<uint16_t*>(vga_location)),
    cursor_x_(0),
    cursor_y_(0) {}

uint16_t Terminal::ConvertToTermChar(uint8_t fg, uint8_t bg, uint8_t character)
{
  //   4     4     8
  // [ bg ][ fg ][ char ]
  return (static_cast<uint16_t>(bg) << 12 |
          static_cast<uint16_t>(fg) << 8 |
          static_cast<uint16_t>(character));
}

uint16_t Terminal::ConvertToTermCursor(uint8_t x, uint8_t y) const
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

void Terminal::print(const char* format, ...)
{
  va_list args;
  va_start(args, format);

  while (*format != '\0') {
    //Write("here\n");
    if (*format == '%') {
      format++;
      switch (*format) {
        case 'd':
        {
          uint64_t i = va_arg(args, uint64_t);
          // TODO: Implement Write() overloads to allow for writing of other
          // types than just strings
          Write(i);
          break;
        }
        case 's':
        {
          const char* s = va_arg(args, const char *);
          Write(s);
          break;
        }
      }
      format++;
    }
    else {
      Write(*format);
      format++;
    }
  }

  va_end(args);
}

uint16_t Terminal::GetTermCursor() const
{
  return ConvertToTermCursor(cursor_x_, cursor_y_);
}


void Terminal::Write(const char* message)
{
  for (int i = 0; message[i] != '\0'; i++) {
    Write(message[i]);
  }
}

void Terminal::Write(char character)
{
  if (character == '\n') {
    MoveCursorTo(0, cursor_y_+1);
  }
  else if (character > 31 && character < 127) {
    vga_buf_[GetTermCursor()] = ConvertToTermChar(kDefaultFg, kDefaultBg, character);
    cursor_x_++;
    if (cursor_x_ >= kDefaultWidth) {
      cursor_x_ = 0;
      cursor_y_++;
    }
    MoveCursorTo(cursor_x_, cursor_y_);
  }
}

void Terminal::Write(uint64_t num)
{
  int num_digits = 0;
  uint64_t tmp = num;

  while (tmp != 0) {
    num_digits++;
    tmp /= 10;
  }

  char number[num_digits+1];
  number[num_digits] = '\0';

  uint32_t i = 0;
  while (num != 0) {
    number[num_digits - i - 1] = '0' + static_cast<char>(num % 10);
    num /= 10;
    i++;
  }

  Write(number);
}

void Terminal::ClearScreen()
{
  volatile uint16_t* vga_buf = reinterpret_cast<uint16_t*>(kVgaLocation);
  for (int i = 0; i < kDefaultWidth * kDefaultHeight; i++) {
    vga_buf[i] = ConvertToTermChar(kDefaultFg, kDefaultBg, ' ');
  }

  MoveCursorTo(0, 0);
}
