#pragma region Exit on GameCrash
#include "cell/pad/libpad.h"
#include "cell/pad/error.h"
#define CELL_UTIL_PAD_MAX 7
static CellPadInfo2 sPadInfo2;
bool updatePadInfo()
{
	CellPadInfo2 pad_info2;
	int32_t cr = cellPadGetInfo2(&pad_info2);
	if (cr != CELL_PAD_OK) return false;

	sPadInfo2 = pad_info2;

	return true;
}

bool isConnected(uint8_t pad)
{
	if (pad >= CELL_UTIL_PAD_MAX) return false; // if the gamepad is above port 8 then will simply return false
	if (pad >= sPadInfo2.max_connect) return false;

	return (sPadInfo2.port_status[pad] & CELL_PAD_STATUS_CONNECTED);
}

bool padUtilConnected(uint8_t pad)
{
	if (!updatePadInfo()) { // if no controllers are connected
		return false;
	}
	return isConnected(pad);
}

void GameFreezeExit(uint64_t frz)
{
	// Credit to FaZeModz https://github.com/TheRealFaZeModz/TinyMenuGTA/blob/28b1df654168ba3c59a082a2d61e0a6e1483cf25/Tiny%20Ass%20Menu%20Source%205.0.0/Tiny%20Ass%20Menu%20Source/GTAV_Native_Invoker/prx.cpp#L4257
	sleep(30000);
	while (true) {
		sleep(100);
		static int pad = -1;
		if (pad == -1) {
			for (int i = 0; i < 7; i++) {
				if (padUtilConnected(i)) // if no controllers are connected
					pad = i;
			}
		}

		CellPadData tempPadData;
		CellPadData padData;
		int32_t ret = cellPadGetData(pad == -1 ? 0 : pad, &tempPadData);

		if (ret == CELL_PAD_OK && tempPadData.len != 0) {
			padData = tempPadData;
		}
		int data = padData.button[CELL_PAD_BTN_OFFSET_DIGITAL1];
		if ((data & CELL_PAD_CTRL_SELECT) && (data & CELL_PAD_CTRL_START)) // if Select and Start are being pressed
		{
			sys_process_exit(0);
		}

	}

}
#pragma endregion