// terminal.h
//
// Class definition for Terminal with singleton method

#ifndef _TERMINAL_H_
#define _TERMINAL_H_

#include <cstdint>

class Terminal
{
  public:
    void Write(const char* message);
    void ClearScreen();
    static Terminal& GetTerm();

  private:
    Terminal();
    Terminal(const Terminal&) = delete;
    uint16_t ConvertToTermChar(uint8_t fg, uint8_t bg, uint8_t character);
    uint16_t ConvertToTermCursor(uint8_t x, uint8_t y);
    void MoveCursorTo(uint8_t x, uint8_t y);

    uint8_t cursor_x_;
    uint8_t cursor_y_;
};



#endif  // _TERMINAL_H_
