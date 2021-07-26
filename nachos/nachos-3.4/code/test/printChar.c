#include "syscall.h"

void main()
{
	int c;
	c = ReadChar();
	PrintChar(c);
	Halt();
}
