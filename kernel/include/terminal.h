// terminal.h
//
// Class definition for Terminal with singleton method

#ifndef _TERMINAL_H_
#define _TERMINAL_H_

#include <cstdint>

class Terminal
{
  public:
    void print(const char* format, ...);
    void ClearScreen();
    static Terminal& GetTerm();

  private:
    Terminal(uint64_t vga_location);
    Terminal(const Terminal&) = delete;
    void Write(const char* message);
    void Write(uint64_t num);
    void Write(char character);
    uint16_t ConvertToTermChar(uint8_t fg, uint8_t bg, uint8_t character);
    uint16_t ConvertToTermCursor(uint8_t x, uint8_t y) const;
    uint16_t GetTermCursor() const;
    void MoveCursorTo(uint8_t x, uint8_t y);

    volatile uint16_t* const vga_buf_;
    uint8_t cursor_x_;
    uint8_t cursor_y_;
};



#endif  // _TERMINAL_H_
