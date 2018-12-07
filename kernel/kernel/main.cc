#include "terminal.h"

int main(void) {
  Terminal& term = Terminal::GetTerm();
  term.ClearScreen();
  term.Write("Hello world!");
  while(1);
  return 0;
}
