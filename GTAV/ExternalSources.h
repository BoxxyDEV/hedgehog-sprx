#include "invoker.h";
#include <string.h>
#include "types.h"


namespace ExternalSources {
	char bytearray[100];
	int TOC;
	void WriteBytes(int p1, char* input, int length)
	{
		for (int i = 0; i < length; i++) // sets up for loop
		{
			*(char*)(p1 + (i)) = input[i];
		}
	}

	char* ReadBytes(int address, int length)
	{
		for (int i = 0; i < length; i++) // sets up for loop
		{
			bytearray[i] = *(char*)(address + (i)); 
		}
		return bytearray;
	}

	void WriteString(int p1, char* string)
	{
		int FreeMem = 0x1D00000; // sets a hexadecimal address as a integer
		int strlength = std::strlen(string); // gets how long the string param is
		char* strpointer = *(char**)FreeMem = string;
		char* StrBytes = ReadBytes(*(int*)FreeMem, strlength);
		WriteBytes(p1, StrBytes, strlength);
		*((char*)p1 + strlength) = '\0';

	}

#define SEND_GAME_INVITE 0x982B00 * 2
	opd_s SendGameInvitePSN_t = { SEND_GAME_INVITE, TOC };
	void(*SendGameInvitePSN)(int unk, int a1, int a2, int a3, int a4, int a5, int a6) = (void(*)(int, int, int, int, int, int, int))&SendGameInvitePSN_t;

	void GameInvite(char* name)
	{
		char buffer[70] = {}; // sets up an array (maybe not im noob to C++)

		WriteBytes((int)0x1004004C, buffer, 0x100); 
		WriteString(0x1004004C + 8, name);
		SendGameInvitePSN(0x40054CE0, 0x1004004C, 1, 0, 0, 0, 0x1C3324C); 

	}
	// credit to Mister//Modzz for the code
	
}