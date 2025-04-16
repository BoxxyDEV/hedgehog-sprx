#include "invoker.h"
#include <inttypes.h>



namespace gopro2027
{


	// all the code here is from gopro_2027
	int G_NATIVES = 0x1DA7BB0;
	int GLOBALS_PTR = 0x1DA7FF0;

	int Read_Global_Address(int a_uiGlobalID)
	{
		int Ptr = *(volatile int*)((GLOBALS_PTR)+(((a_uiGlobalID / 0x40000) & 0x3F) * 4));
		if (Ptr != 0)
			return (Ptr + ((a_uiGlobalID % 0x40000) * 4));
		return 0;
	}

	class Global {
	private:
		unsigned int index;
		unsigned int getAddress() {
			return Read_Global_Address(index);
		}
	public:
		Global(unsigned int globalID)
			: index(globalID/*Read_Global_Address(globalID)*/)
		{
		}
		Global imm(int i) {
			return Global(index + i);
		}
		Global arr(int index, int size) {
			return imm(index * size);
		}
		template <typename T>
		void set(T value) {
			*(T*)getAddress() = value;
		}
		template <typename T>
		T get() {
			return *(T*)getAddress();
		}
		unsigned int* at() {
			return (unsigned int*)getAddress();
		}
	};
	

	int getOPDOfNative(unsigned int hash)
	{
		Native_s* Natives = ((Native_s**)G_NATIVES)[hash & 0xFF];
		while (Natives != 0)
		{
			for (unsigned int i = 0; i < Natives->NativeCount; i++)
			{
				if (Natives->NativeHashes[i] == hash)
				{
					int address = (int)(Natives->NativeFunctions[i]);
					return address;
				}
			}
			Natives = Natives->LastNativesTable;
		}
		return -1;
	}

	void patchNative(unsigned int hash, int hook)
	{
		*(uint64_t*)getOPDOfNative(hash) = *(uint64_t*)(hook);
	}

	void native_ret0_hook(int r3) {
		*(int*)(*(int*)(r3)+0x0) = 0;
	}
	void native_ret1_hook(int r3) {
		*(int*)(*(int*)(r3)+0x0) = 1;
	}

	void FixTexts()
	{
		patchNative(0xFFED3676, (int)native_ret1_hook);
		patchNative(0xA796D7A7, (int)native_ret0_hook);
		patchNative(0x4D8A6521, (int)native_ret0_hook);
	}

	void StatBypass()
	{
		patchNative(0x850690FF, (int)native_ret1_hook);
		patchNative(0x881B1FDB, (int)native_ret1_hook);
	}

	void goprostartup()
	{
		
		FixTexts();
		StatBypass();
		// i am very sorry for stealing this gopro_2027 
	}
}