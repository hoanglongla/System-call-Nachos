// exception.cc 
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.  
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "syscall.h"

//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2. 
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//	"which" is the kind of exception.  The list of possible exceptions 
//	are in machine.h.
//----------------------------------------------------------------------

void IncreasePC()
{
	int counter = machine->ReadRegister(PCReg);
	machine->WriteRegister(PrevPCReg, counter);
	counter = machine->ReadRegister(NextPCReg);
	machine->WriteRegister(PCReg, counter);
	machine->WriteRegister(NextPCReg, counter +4);
}

char* User2Sys(int virtualAddr, int limit)
{
	int oneChar;
	char* kernelBuffer = NULL;
	kernelBuffer = new char[limit+1];
	if (kernelBuffer == NULL) return kernelBuffer;
	memset(kernelBuffer,0,limit+1);
	for (int i = 0; i < limit; i++)
	{
		machine->ReadMem(virtualAddr + i, 1, &oneChar);
		kernelBuffer[i] = (char) oneChar;
		if (oneChar == 0) break;
	}
	return kernelBuffer;
}

int Sys2User(int virtualAddr, int len, char*buffer)
{
	if (len <0) return -1;
	if (len ==0) return len;
	int i = 0;
	int oneChar = 0;
	do
	{
		oneChar = (int)buffer[i];
		machine->WriteMem(virtualAddr + i, 1, oneChar);
		i++;
	} while (i< len && oneChar !=0);
	return i;
}

void ExceptionHandler(ExceptionType which)
{
    int type = machine->ReadRegister(2);

    switch (which) {
	case NoException:
	return;

        case PageFaultException:
		{
		printf("\n\n No valid translation found");
		interrupt->Halt();
		break;
		}

        case ReadOnlyException:
		{
		printf("\n\n Write attempted to page marked read-only");
		interrupt->Halt();
		break;
		}

        case BusErrorException:
		{
		printf("\n\n Translation resulted in an invalid physical address");
		interrupt->Halt();
		break;
		}

        case AddressErrorException:
		{
		printf("\n\n Unaligned reference or one that was beyond the end of the address space");
		interrupt->Halt();
		break;
		}

        case OverflowException:
		{
		printf("\n\n Integer overflow in add or sub");
		interrupt->Halt();
		break;
		}

	case IllegalInstrException:
		{
		printf("\n\n Unimplemented or reserved instr");
		interrupt->Halt();
		break;	
		}

	case SyscallException:
	switch (type) {
		case SC_Halt:
		{	
			printf("\nShutdown, initiated by user program. \n");
			interrupt->Halt();
			return;
		}

		case SC_ReadString:
		{	
			int virtualAddr, length;
			char* buffer;
			virtualAddr = machine->ReadRegister(4);
			length = machine->ReadRegister(5);
			buffer = User2Sys(virtualAddr, length);
			gSynchConsole->Read(buffer, length);
			Sys2User(virtualAddr, length, buffer);
			delete buffer;
			IncreasePC();
			return;
		}

		case SC_PrintString:
		{	
			int virtualAddr;
			char* buffer;
			virtualAddr = machine->ReadRegister(4);
			buffer = User2Sys(virtualAddr, 255);
			int length = 0;
			while (buffer[length] != 0) length++;
			gSynchConsole->Write(buffer, length + 1);
			delete buffer;
			IncreasePC();
			return;
			}
		}
		default: 
			break;
	}
	IncreasePC();	
}
		
