#include <terminal.h>

int main(void) {
  Terminal& term = Terminal::GetTerm();
  term.ClearScreen();
  term.print("Hello world! This is the %d day of %s!", 17, "December");
  while(1);
  return 0;
}
