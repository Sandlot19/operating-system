#ifndef _ASMUTILS_H_
#define _ASMUTILS_H_

#include <cstdint>

class asmutils
{
  public:
    static inline void out_byte(uint16_t port, uint8_t data) {
      asm volatile("outb %0, %1"
          :
          : "a"(data), "Nd"(port)
          :);
    }
};

#endif // _ASMUTILS_H_
