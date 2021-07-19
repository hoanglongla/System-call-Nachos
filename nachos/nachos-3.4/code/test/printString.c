#include "syscall.h"

int main()
{
	char str[200];
	PrintString("\nInput string: ");
	ReadString(str, 200);
	PrintString("\nThe string you just input: ");
	PrintString(str);
	Halt();
	return 0;
}
