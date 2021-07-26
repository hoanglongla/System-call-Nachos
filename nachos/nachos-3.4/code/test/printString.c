#include "syscall.h"
#include "copyright.h"

void main()
{
	char str[255];
	ReadString(str, 255);
	PrintString(str);
	Halt();
}
