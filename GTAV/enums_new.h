// some buttons not working
HUD::HIDE_HELP_TEXT_THIS_FRAME();
CAM::SET_CINEMATIC_BUTTON_ACTIVE(0);
HUD::HIDE_HUD_COMPONENT_THIS_FRAME(10);
HUD::HIDE_HUD_COMPONENT_THIS_FRAME(6);
HUD::HIDE_HUD_COMPONENT_THIS_FRAME(7);
HUD::HIDE_HUD_COMPONENT_THIS_FRAME(9);
HUD::HIDE_HUD_COMPONENT_THIS_FRAME(8);
PAD::DISABLE_CONTROL_ACTION(0, 19);
PAD::DISABLE_CONTROL_ACTION(0, 20);
PAD::DISABLE_CONTROL_ACTION(0, 21);
PAD::DISABLE_CONTROL_ACTION(0, 27);
PAD::DISABLE_CONTROL_ACTION(0, 54);
PAD::DISABLE_CONTROL_ACTION(0, 123);
PAD::DISABLE_CONTROL_ACTION(0, 124);
PAD::DISABLE_CONTROL_ACTION(0, 125);
PAD::DISABLE_CONTROL_ACTION(0, 126);
PAD::DISABLE_CONTROL_ACTION(0, 138);
PAD::DISABLE_CONTROL_ACTION(0, 139);
PAD::DISABLE_CONTROL_ACTION(0, 140);
PAD::DISABLE_CONTROL_ACTION(0, 177);
PAD::DISABLE_CONTROL_ACTION(0, 178);
PAD::DISABLE_CONTROL_ACTION(0, 179);
PAD::DISABLE_CONTROL_ACTION(0, 207);
PAD::SET_INPUT_EXCLUSIVE(2, 166);
PAD::SET_INPUT_EXCLUSIVE(2, 167);
PAD::SET_INPUT_EXCLUSIVE(2, 177);
PAD::SET_INPUT_EXCLUSIVE(2, 178);
PAD::SET_INPUT_EXCLUSIVE(2, 193);
PAD::SET_INPUT_EXCLUSIVE(2, 194);
PAD::SET_INPUT_EXCLUSIVE(2, 195);
PAD::SET_INPUT_EXCLUSIVE(2, 202);
PAD::SET_INPUT_EXCLUSIVE(2, 203);
PAD::SET_INPUT_EXCLUSIVE(2, 204);
PAD::SET_INPUT_EXCLUSIVE(2, 205);

// works
enum eButtons
{
	BUTTON_TRIANGLE = 0xB4,
	BUTTON_O = 0xC0,
	BUTTON_X = 0xCD,
	BUTTON_SQUARE = 0xBF,
	BUTTON_L1 = 0xC1,
	BUTTON_L2 = 0xC3,
	BUTTON_L3 = 0xC5,
	BUTTON_R1 = 0xC2,
	BUTTON_R2 = 0xC4,
	BUTTON_R3 = 0xC6,
	DPAD_UP = 0xC7,
	DPAD_RIGHT = 0xCA,
	DPAD_LEFT = 0xC9,
	DPAD_DOWN = 0xA1,
	BUTTON_SELECT = 0xCB
	BUTTON_START = 0x0F
};