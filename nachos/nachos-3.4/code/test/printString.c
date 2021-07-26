#include "syscall.h"
#include "copyright.h"

int main()
{
	char str[200];
	ReadString(str, 200);
	PrintString(str);
	PrintString("\n");
	Halt();
	return 0;
}
