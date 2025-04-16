#pragma region Internals

int sceKernelWrite(void* destination, const void* source, size_t size)
{
	system_call_4(905, (uint64_t)sys_process_getpid(), (uint64_t)destination, size, (uint64_t)source);
	return_to_user_prog(int);
}

int32_t sceKernelHenWrite(void* destination, const void* source, size_t size)
{
	system_call_6(8, 0x7777, 0x32, (uint64_t)sys_process_getpid(), (uint64_t)destination, (uint64_t)source, (uint64_t)size);
	return_to_user_prog(int);
}

void PatchInJump(uint64_t Address, int Destination, bool Linked)
{
	int FuncBytes[4];													// Use this data to copy over the address.
	Destination = *(int*)Destination;									// Get the actual destination address (pointer to void).
	FuncBytes[0] = 0x3D600000 + ((Destination >> 16) & 0xFFFF);			// lis %r11, dest>>16
	if (Destination & 0x8000)											// if bit 16 is 1...
		FuncBytes[0] += 1;
	FuncBytes[1] = 0x396B0000 + (Destination & 0xFFFF);					// addi %r11, %r11, dest&OxFFFF
	FuncBytes[2] = 0x7D6903A6;											// mtctr %r11
	FuncBytes[3] = 0x4E800420;											// bctr
	if (Linked)
		FuncBytes[3] += 1;												// bctrl
	//sceKernelHenWrite((void*)Address, FuncBytes, 4 * 4);
	memcpy((void*)Address, FuncBytes, 4 * 4);
}

void sleep(usecond_t time)  //1 second = 1000
{
	sys_timer_usleep(time * 1000);
}
void set_text_component(char *text)
{
	GRAPHICS::_0x3AC9CB55("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING(text);
	GRAPHICS::_0x386CE0B8();
}
void instructionsSetup()
{
	mov = GRAPHICS::REQUEST_SCALEFORM_MOVIE("instructional_buttons");
	GRAPHICS::_0x7B48E696(mov, 255, 255, 255, 0);
	GRAPHICS::_0x215ABBE8(mov, "CLEAR_ALL");
	GRAPHICS::_0x02DBF2D7();
	GRAPHICS::_0x215ABBE8(mov, "SET_CLEAR_SPACE");
	GRAPHICS::_0x716777CB(200);
	GRAPHICS::_0x02DBF2D7();
	instructCount = 0;
}
void addInstruction(int button, char *text)
{
	if (!instructionsSetupThisFrame)
	{
		instructionsSetup();
		instructionsSetupThisFrame = true;
	}
	GRAPHICS::_0x215ABBE8(mov, "SET_DATA_SLOT");
	GRAPHICS::_0x716777CB(instructCount);
	GRAPHICS::_0x716777CB(button);
	set_text_component(text);
	GRAPHICS::_0x02DBF2D7();
	instructCount++;
}
void instructionsClose()
{
	GRAPHICS::_0x215ABBE8(mov, "DRAW_INSTRUCTIONAL_BUTTONS");
	GRAPHICS::_0x02DBF2D7();
	GRAPHICS::_0x215ABBE8(mov, "SET_BACKGROUND_COLOUR");
	GRAPHICS::_0x716777CB(0);
	GRAPHICS::_0x716777CB(0);
	GRAPHICS::_0x716777CB(0);
	GRAPHICS::_0x716777CB(80);
	GRAPHICS::_0x02DBF2D7();
}
void drawText(char * text, int font, float x, float y, float scalex, float scaley, int r, int b, int g, int a, bool center)
{
	UI::SET_TEXT_FONT(font);
	UI::SET_TEXT_SCALE(scalex, scaley);
	UI::SET_TEXT_COLOUR(r, g, b, a);
	UI::SET_TEXT_WRAP(0.0f, 1.0f);
	UI::SET_TEXT_CENTRE(center);
	UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
	UI::SET_TEXT_OUTLINE();
	UI::_SET_TEXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING(text);
	UI::_DRAW_TEXT(x, y);
}

void drawIntText(char * text, int num, int font, float x, float y, float scalex, float scaley, int r, int b, int g, int a, bool center)
{
	UI::SET_TEXT_FONT(font);
	UI::SET_TEXT_SCALE(scalex, scaley);
	UI::SET_TEXT_COLOUR(r, g, b, a);
	UI::SET_TEXT_WRAP(0.0f, 1.0f);
	UI::SET_TEXT_CENTRE(center);
	UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
	UI::SET_TEXT_OUTLINE();
	UI::_SET_TEXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING(text);
	UI::ADD_TEXT_COMPONENT_INTEGER(num);
	UI::_DRAW_TEXT(x, y);
}

void printscreen(char* msg)
{
	UI::_0xF42C43C7("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING(msg);
	UI::_0x38F82261(3000, 1);
}
void drawNotification(char* Title, char* msg)
{
	if (menuXCoord == 0.8f)
	{
		UI::_0x574EE85C("STRING");
		UI::_ADD_TEXT_COMPONENT_STRING(msg);
		UI::_SET_NOTIFICATION_MESSAGE("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", true, 4, Title, "");
		UI::_DRAW_NOTIFICATION(false, true);
	}
	else
	{
		printscreen(msg);
	}
}

void playSound(char* sound)
{
	if (menuSounds)
		AUDIO::PLAY_SOUND_FRONTEND(-1, sound, "HUD_FRONTEND_DEFAULT_SOUNDSET");
}
bool isNumericChar(char x)
{
	return (x >= '0' && x <= '9') ? true : false;
}
int StoI(char *str)
{
	if (*str == NULL)
		return 0;

	int res = 0,
		sign = 1,
		i = 0;

	if (str[0] == '-')
	{
		sign = -1;
		i++;
	}
	for (; str[i] != '\0'; ++i)
	{
		if (isNumericChar(str[i]) == false)
			return 0;
		res = res * 10 + str[i] - '0';
	}
	return sign * res;
}
char *ItoS(int num)
{
	char buf[30];
	snprintf(buf, sizeof(buf), "%i", num);
	return buf;
}
int FtoI(float input)
{
	char returnvalue[64];
	int wholenumber = (int)input;
	input -= wholenumber;
	input *= 100;
	sprintf(returnvalue, "%d.%d", wholenumber, (int)input);
	return wholenumber;
}

char* FtoS(float input)
{
	char returnvalue[64];
	int wholenumber = (int)input;
	input -= wholenumber;
	input *= 100;
	sprintf(returnvalue, "%d.%d", wholenumber, (int)input);
	return returnvalue;
}
void startKeyboard(int action, char *defaultText, int maxLength)
{
	GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(0, "FMMC_KEY_TIP8", "", defaultText, "", "", "", maxLength);
	keyboardAction = action;
	keyboardActive = true;
}
void changeSubmenu(int newSubmenu)
{
	lastSubmenu[submenuLevel] = submenu;
	lastOption[submenuLevel] = currentOption;
	currentOption = 1;
	submenu = newSubmenu;
	submenuLevel++;
}
void SetupTimer(int tickTime)
{
	if (newTimerTick) {
		maxTimerCount = GAMEPLAY::GET_GAME_TIMER() + tickTime;
		newTimerTick = false;
	}
}
bool IsTimerReady()
{
	return GAMEPLAY::GET_GAME_TIMER() > maxTimerCount;
}
void ResetTimer()
{
	newTimerTick = true;
}
void SetupTimer2(int tickTime)
{
	if (newTimerTick2) {
		maxTimerCount2 = GAMEPLAY::GET_GAME_TIMER() + tickTime;
		newTimerTick2 = false;
	}
}
bool IsTimerReady2()
{
	return GAMEPLAY::GET_GAME_TIMER() > maxTimerCount2;
}
void ResetTimer2()
{
	newTimerTick2 = true;
}
void addTitle(char *title)
{
	drawText(title, bannerTextFont, menuXCoord, 0.090f, 0.70f, 0.70f, bannerTextRed, bannerTextGreen, bannerTextBlue, bannerTextOpacity, true);
	GRAPHICS::DRAW_RECT(menuXCoord, 0.1175f, menuXScale, 0.083f, bannerRectRed, bannerRectGreen, bannerRectBlue, bannerRectOpacity); // edited title and background to be 0.22f x
}
void addSubtitle(char* subtitle)
{
	drawText(subtitle, bannerTextFont, menuXCoord, 0.136f, 0.25f, 0.25f, bannerTextRed, bannerTextGreen, bannerTextBlue, bannerTextOpacity, true);
}
#pragma region Option Helpers
void addOption(char *option, char *info = NULL)
{
	optionCount++;
	if (currentOption == optionCount)
		infoText = info;
	if (currentOption <= maxOptions && optionCount <= maxOptions)
		drawText(option, optionsFont, textXCoord, (optionCount * multiplyone + multiplytwo), 0.4f, 0.4f, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
	else if ((optionCount > (currentOption - maxOptions)) && optionCount <= currentOption)
		drawText(option, optionsFont, textXCoord, ((optionCount - (currentOption - maxOptions)) * multiplyone + multiplytwo), 0.4f, 0.4f, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
}
void addSubmenuOption(char *option, int newSubmenu, char *info = NULL)
{
	addOption(option, info);
	if (currentOption == optionCount)
	{
		xInstruction = true;
		if (optionPress)
			changeSubmenu(newSubmenu);
	}
}
void addBoolOption(char *option, bool *b00l, char *info = NULL)
{
	char buf[30];

	
	if (*b00l)
	{
		if (currentOption <= maxOptions && optionCount <= maxOptions)
			drawText("~g~On", optionsFont, (menuXCoord + flagcoordX), (optionCount * 0.035f + 0.160f), 0.4f, 0.4f, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
		else if ((optionCount > (currentOption - maxOptions)) && optionCount <= currentOption)
			drawText("~g~On", optionsFont, (menuXCoord + flagcoordX), ((optionCount - (currentOption - maxOptions)) * 0.035f + 0.160f), 0.4f, 0.4f, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
		snprintf(buf, sizeof(buf), "%s", option);
		addOption(buf, info);
	}
	else
	{
		if (currentOption <= maxOptions && optionCount <= maxOptions)
			drawText("~r~Off", optionsFont, (menuXCoord + flagcoordX), (optionCount * 0.035f + 0.160f), 0.4f, 0.4f, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
		else if ((optionCount > (currentOption - maxOptions)) && optionCount <= currentOption)
			drawText("~r~Off", optionsFont, (menuXCoord + flagcoordX), ((optionCount - (currentOption - maxOptions)) * 0.035f + 0.160f), 0.4f, 0.4f, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
		snprintf(buf, sizeof(buf), "%s", option);
		addOption(buf, info);
	}
	if (currentOption == optionCount)
		if (optionPress)
			*b00l = !*b00l;
	
}
template<typename TYPE>
void addCustomBoolOption(char *option, TYPE value, TYPE match, char *info = NULL)
{
	char buf[30];
	if (value == match)
	{
		if (currentOption <= maxOptions && optionCount <= maxOptions)
			drawText("~g~On", optionsFont, (menuXCoord + flagcoordX), (optionCount * 0.035f + 0.160f), 0.4f, 0.4f, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
		else if ((optionCount > (currentOption - maxOptions)) && optionCount <= currentOption)
			drawText("~g~On", optionsFont, (menuXCoord + flagcoordX), ((optionCount - (currentOption - maxOptions)) * 0.035f + 0.160f), 0.4f, 0.4f, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
		snprintf(buf, sizeof(buf), "%s", option);
		addOption(buf, info);
	}
	else
	{
		if (currentOption <= maxOptions && optionCount <= maxOptions)
			drawText("~r~Off", optionsFont, (menuXCoord + flagcoordX), (optionCount * 0.035f + 0.160f), 0.4f, 0.4f, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
		else if ((optionCount > (currentOption - maxOptions)) && optionCount <= currentOption)
			drawText("~r~Off", optionsFont, (menuXCoord + flagcoordX), ((optionCount - (currentOption - maxOptions)) * 0.035f + 0.160f), 0.4f, 0.4f, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
		snprintf(buf, sizeof(buf), "%s", option);
		addOption(buf, info);
	}
}


void addIntOption(char *option, int *var, int min, int max, bool keyboard, char *info = NULL)
{
	char buf[33];
	snprintf(buf, sizeof(buf), "%s: < %i >", option, *var);
	addOption(buf, info);
	if (currentOption == optionCount)
	{
		lrInstruction = true;
		if (rightPress)
		{
			playSound("NAV_UP_DOWN");
			if (*var >= max)
				*var = min;
			else
				*var = *var + 1;
		}
		else if (leftPress)
		{
			playSound("NAV_UP_DOWN");
			if (*var <= min)
				*var = max;
			else
				*var = *var - 1;
		}
		if (keyboard)
		{
			squareInstruction = true;
			if (squarePress)
			{
				startKeyboard(0, "", (strlen(ItoS(max)) + 1));
				keyboardVar = var;
			}
		}
	}
}

void addBoolTextOption(char *option, bool *b00l, int *var, int min, int max, char* textoptionone, char* textoptiontwo, char* textoptionthree = NULL, char *info = NULL)
{
	char buf[60];
	if (*var == 1)
	{
		snprintf(buf, sizeof(buf), "%s < %s >", option, textoptionone);
	}
	if (*var == 2)
	{
		snprintf(buf, sizeof(buf), "%s < %s >", option, textoptiontwo);
	}
	if (*var == 3)
	{
		snprintf(buf, sizeof(buf), "%s  < %s >", option, textoptionthree);
	}
	//snprintf(buf, sizeof(buf), "%s: < %i >", option, *var);
	addBoolOption(buf, b00l, info);
	if (currentOption == optionCount)
	{
		lrInstruction = true;
		if (rightPress)
		{
			playSound("NAV_UP_DOWN");
			if (*var >= max)
				*var = min;
			else
				*var = *var + 1;
		}
		else if (leftPress)
		{
			playSound("NAV_UP_DOWN");
			if (*var <= min)
				*var = max;
			else
				*var = *var - 1;
		}
	}
}
void addFloatOption(char *option, float *var, float min, float max, bool holdPress, char *info = NULL)
{
	char buf[30];
	snprintf(buf, sizeof(buf), "%s: < %s >", option, FtoS(*var));
	addOption(buf, info);
	if (currentOption == optionCount)
	{
		lrInstruction = true;
		if (holdPress)
		{
			if (fastRightPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var >= max)
					*var = min;
				else
					*var = *var + 0.01f;
			}
			else if (fastLeftPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var <= min)
					*var = max;
				else
					*var = *var - 0.01f;
			}
		}
		else
		{
			if (rightPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var >= max)
					*var = min;
				else
					*var = *var + 0.01f;
			}
			else if (leftPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var <= min)
					*var = max;
				else
					*var = *var - 0.01f;
			}
		}
	}
}
void addKeyboardOption(char *option, int action, char *defaultText, int maxLength, char *info = NULL)
{
	addOption(option, info);
	if (currentOption == optionCount)
	{
		xInstruction = true;
		if (optionPress)
			startKeyboard(action, defaultText, maxLength);
	}
}



#pragma endregion
int getOption()
{
	xInstruction = true;
	if (optionPress)
		return currentOption;
	else return 0;
}
void monitorButtons()
{
	SetupTimer(20);
	if (submenu == Closed)
	{
		if (IsTimerReady())
		{
			if ((CONTROLS::IS_CONTROL_PRESSED(0, DpAD_RIGHT)) && (CONTROLS::IS_CONTROL_PRESSED(0, 205))) //(CONTROLS::IS_CONTROL_PRESSED(0, 193) && CONTROLS::IS_CONTROL_PRESSED(0, 205)) // L1 + Cross
			{
				submenu = Main_Menu;
				submenuLevel = 0;
				currentOption = 1;
				if (FirstOpen)
				{
					drawNotification("Hedgehog SPRX", "Welcome, Please do not abuse other players and have fun. \nCreated by Boxuga");
					FirstOpen = false;
				}
				playSound("YES");
			}
			ResetTimer();
		}
	}
	else {
		if (IsTimerReady())
		{
			if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, 43)) //43 for circle
			{
				if (submenu == Main_Menu)
				{
					submenu = Closed;
				}
				else {
					submenu = lastSubmenu[submenuLevel - 1];
					currentOption = lastOption[submenuLevel - 1];
					submenuLevel--;
				}
				playSound("Back");
			}
			else if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, 205)) // 205 for X
			{
				optionPress = true;
				playSound("SELECT");
			}
			else if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, DpAD_UP)) // Up 151
			{
				currentOption--;
				if (currentOption < 1)
				{
					currentOption = optionCount;
				}
				playSound("NAV_UP_DOWN");
			}
			else if (CONTROLS::IS_CONTROL_JUST_PRESSED(2, 248)) // 46 
			{
				currentOption++;
				if (currentOption > optionCount)
				{
					currentOption = 1;
				}
				playSound("NAV_UP_DOWN");
			}
			else if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, DpAD_RIGHT)) // 202 right dpad
			{
				rightPress = true;
			}
			else if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, DpAD_LEFT))// 15 for left
			{
				leftPress = true;
			}
			else if (CONTROLS::IS_CONTROL_PRESSED(0, DpAD_RIGHT))
			{
				fastRightPress = true;
			}
			else if (CONTROLS::IS_CONTROL_PRESSED(0, DpAD_LEFT))
			{
				fastLeftPress = true;
			}
			else if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, 167)) //square 167
			{
				squarePress = true;
			}
			ResetTimer();
		}
	}
}
void normalMenuActions()
{
	UI::HIDE_HELP_TEXT_THIS_FRAME();
	CAM::SET_CINEMATIC_BUTTON_ACTIVE(0);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(10);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(6);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(7);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(9);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(8);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 19);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 20);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 21);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 27);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 54);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 123);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 124);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 125);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 126);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 138);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 139);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 140);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 177);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 178);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 179);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 207);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 120);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 166);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 167);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 177);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 178);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 193);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 194);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 202);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 203);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 205);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 248);
	if (optionCount > maxOptions)
	{
		GRAPHICS::DRAW_RECT(menuXCoord, (((maxOptions * 0.035f) / 2) + drawadd), menuXScale, (maxOptions * 0.037f), backgroundRed, backgroundGreen, backgroundBlue, backgroundOpacity); //Background
		if (currentOption > maxOptions)
		{
			GRAPHICS::DRAW_RECT(menuXCoord, ((maxOptions * 0.035f) + drawadd), menuXScale, 0.035f, scrollerRed, scrollerGreen, scrollerBlue, scrollerOpacity); //Scroller
			GRAPHICS::DRAW_RECT(menuXCoord, 0.156f, 0.19f, 0.005f, indicatorRed, indicatorGreen, indicatorBlue, indicatorOpacity); //Up Indicator
		}
		else
		{
			GRAPHICS::DRAW_RECT(menuXCoord, ((currentOption * 0.035f) + drawadd), menuXScale, 0.035f, scrollerRed, scrollerGreen, scrollerBlue, scrollerOpacity); //Scroller
		}
		if (currentOption != optionCount)
		{
			GRAPHICS::DRAW_RECT(menuXCoord, ((maxOptions * 0.035f) + 0.161f), menuXScale, 0.005f, indicatorRed, indicatorGreen, indicatorBlue, indicatorOpacity); //Down Indicator
		}
	}
	else
	{
		GRAPHICS::DRAW_RECT(menuXCoord, (((optionCount * 0.035f) / 2) + 0.159f), menuXScale, (optionCount * 0.035f), backgroundRed, backgroundGreen, backgroundBlue, backgroundOpacity); //Background
		GRAPHICS::DRAW_RECT(menuXCoord, ((currentOption * 0.035f) + 0.1415f), menuXScale, 0.035f, scrollerRed, scrollerGreen, scrollerBlue, scrollerOpacity); //Scroller
	}
	if (!GAMEPLAY::IS_STRING_NULL_OR_EMPTY(infoText))
	{
		if (optionCount > maxOptions)
		{
			drawText(infoText, optionsFont, menuXCoord, ((maxOptions + 1) * 0.035f + 0.125f), 0.4f, 0.4f, bannerTextRed, bannerTextGreen, bannerTextBlue, bannerTextOpacity, true);
			GRAPHICS::DRAW_RECT(menuXCoord, (((maxOptions + 1) * 0.035f) + 0.1415f), menuXScale, 0.035f, bannerRectRed, bannerRectGreen, bannerRectBlue, bannerRectOpacity); //Info Box
		}
		else
		{
			drawText(infoText, optionsFont, menuXCoord, ((optionCount + 1) * 0.035f + 0.125f), 0.4f, 0.4f, bannerTextRed, bannerTextGreen, bannerTextBlue, bannerTextOpacity, true);
			GRAPHICS::DRAW_RECT(menuXCoord, (((optionCount + 1) * 0.035f) + 0.1415f), menuXScale, 0.035f, bannerRectRed, bannerRectGreen, bannerRectBlue, bannerRectOpacity); //Info Box
		}
	}
	SetupTimer2(20);
	if (instructions)
	{
		if (IsTimerReady2())
		{
			if (xInstruction)
				addInstruction(BUTTON_A, "Select");
			if (squareInstruction)
				addInstruction(BUTTON_X, "Keyboard");
			if (lrInstruction)
				addInstruction(BUTTON_DPAD_LEFT_RIGHT, "Scroll");
			addInstruction(BUTTON_DPAD_UP_DOWN, "Scroll");
			addInstruction(BUTTON_B, "Back");
			instructionsClose();
			ResetTimer2();
		}
	}


}
void resetVars()
{
	if (submenu != Closed)
		normalMenuActions();
	optionPress = false;
	rightPress = false;
	leftPress = false;
	fastRightPress = false;
	fastLeftPress = false;
	squarePress = false;
	infoText = NULL;
	instructionsSetupThisFrame = false;
	squareInstruction = false;
	xInstruction = false;
	lrInstruction = false;
}

void addTextOption(char *option, int *var, int min, int max, char* textoptionone, char* textoptiontwo, char* textoptionthree = NULL, char *info = NULL)
{
	char buf[60];
	if (*var == 1)
	{
		snprintf(buf, sizeof(buf), "%s < %s >", option, textoptionone);
	}
	if (*var == 2)
	{
		snprintf(buf, sizeof(buf), "%s < %s >", option, textoptiontwo);
	}
	if (*var == 3)
	{
		snprintf(buf, sizeof(buf), "%s  < %s >", option, textoptionthree);
	}
	snprintf(buf, sizeof(buf), "%s: < %i >", option, *var);
	addOption(option, info);
	if (currentOption == optionCount)
	{
		lrInstruction = true;
		if (rightPress)
		{
			playSound("NAV_UP_DOWN");
			if (*var >= max)
				*var = min;
			else
				*var = *var + 1;
		}
		else if (leftPress)
		{
			playSound("NAV_UP_DOWN");
			if (*var <= min)
				*var = max;
			else
				*var = *var - 1;
		}
	}
}

int freeseat(int handle)
{
	// I kinda stole here not gonna lie but i changed for loop because i think its easier then a while loop https://nextgenupdate.com/forums/gta-5-mods/815964-sprx-c-gtav-code-thread.html 
	for (int seatindex = -1; seatindex < VEHICLE::GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(handle); seatindex++)
	{
		if (VEHICLE::IS_VEHICLE_SEAT_FREE(handle, seatindex)) // if a person not in that seat then return the first seat otherwise if car full the return -2
		{
			return seatindex;
		}
	}
	return -2;
}

char* getHost() {
	return (char*)(0x1C3324C + 0x10);
}

bool isHost(char* name) {
	if (strcmp(getHost(), name))
	{
		return true;
	}

	return false;
}


bool isMenuOwner(char* name)
{
	if (strcmp(name, "HedgehogSPRX"))
		return true;

	if (strcmp(name, "Boxuga"))
		return true;

	return false;
}

char* getContentCreator(char* name)
{
	if (strcmp(name, "Parker3TAO"))
		return "3TA Online";

	if (strcmp(name, "JIREXv1"))
		return "3TA Online";

	if (strcmp(name, "FunkyBuzzer"))
		return "3TA Online";

	if (strcmp(name, "poytasuola"))
		return "3TA Online";

	if (isMenuOwner(name))
		return "3TA Online";

	if (strcmp(name, "LT5xxz"))
		return "LTS";

	if (strcmp(name, "XeKyuubii"))
		return "XBL-Kyuubii";

	if (strcmp(name, "Sonito2004"))
		return "Sonito on YouTube";

	if (strcmp(name, "WP_MoDz_2017"))
		return "CoGicBoii Tornado";

	if (strcmp(name, "LushModz5000"))
		return "Lush Modz";

	if (strcmp(name, "X-DontTryMeYo-X")) // lol what is this username
		return "Peace Modz";


	return "nothing";
}

void sidePlayerOption(int id)
{
	char username[50];
	char playercoordx[10];
	char playercoordy[10];
	char playercoordz[10];
	char ownerstr[50];
	char isHoststr[20];
	char apartof[100];
	Vector3 pcoords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(id), true);
	//char* isGod = "God Mode: Off";
	snprintf(username, sizeof(username), "Name: %s", PLAYER::GET_PLAYER_NAME(id));
	snprintf(playercoordx, sizeof(playercoordx), "X: %s", ItoS(FtoI(pcoords.x)));
	snprintf(playercoordy, sizeof(playercoordy), "Y: %s", ItoS(FtoI(pcoords.y)));
	snprintf(playercoordz, sizeof(playercoordz), "Z: %s", ItoS(FtoI(pcoords.z)));
	if (isHost(PLAYER::GET_PLAYER_NAME(id)))
		snprintf(isHoststr, sizeof(isHoststr), "Host: ~g~Yes");
	else
		snprintf(isHoststr, sizeof(isHoststr), "Host: ~g~No");

	if (isMenuOwner(PLAYER::GET_PLAYER_NAME(id)))
		snprintf(ownerstr, sizeof(ownerstr), "Menu Owner (Boxuga): Yes");
	else
		snprintf(ownerstr, sizeof(ownerstr), "Menu Owner (Boxuga): No");
	
	snprintf(apartof, sizeof(apartof), "Apart of %s", getContentCreator(PLAYER::GET_PLAYER_NAME(id)));
	if (PLAYER::GET_PLAYER_INVINCIBLE(id))
	{
		//isGod = "God Mode: On"; // can i use GET_PLAYER_INVINCIBLE(selectedPlayer)
	}
	if (menuXCoord == 0.18f)
	{
		GRAPHICS::DRAW_RECT((menuXCoord + 0.20), 0.27, 0.13, 0.36, backgroundRed, backgroundGreen, backgroundBlue, backgroundOpacity); // left
		drawText(username, optionsFont, (menuXCoord + 0.14), 0.09, 0.30, 0.30, bannerTextRed, bannerTextBlue, bannerTextGreen, bannerRectOpacity, false);
		drawText(playercoordx, optionsFont, (menuXCoord + 0.14), 0.11, 0.30, 0.30, bannerTextRed, bannerTextBlue, bannerTextGreen, bannerRectOpacity, false);
		drawText(playercoordy, optionsFont, (menuXCoord + 0.14), 0.13, 0.30, 0.30, bannerTextRed, bannerTextBlue, bannerTextGreen, bannerRectOpacity, false);
		drawText(playercoordz, optionsFont, (menuXCoord + 0.14), 0.15, 0.30, 0.30, bannerTextRed, bannerTextBlue, bannerTextGreen, bannerRectOpacity, false);
		drawText(isHoststr, optionsFont, (menuXCoord + 0.14), 0.17, 0.30, 0.30, bannerTextRed, bannerTextBlue, bannerTextGreen, bannerRectOpacity, false);
		drawText(ownerstr, optionsFont, (menuXCoord + 0.14), 0.19, 0.30, 0.30, bannerTextRed, bannerTextBlue, bannerTextGreen, bannerRectOpacity, false);
		drawText(apartof, optionsFont, (menuXCoord + 0.14), 0.21, 0.30, 0.30, bannerTextRed, bannerTextBlue, bannerTextGreen, bannerRectOpacity, false);
		//drawText(isGod, optionsFont, (menuXCoord + 0.14), 0.17, 0.30, 0.30, bannerTextRed, bannerTextBlue, bannerTextGreen, bannerRectOpacity, false);
	}
	else
	{
		GRAPHICS::DRAW_RECT((menuXCoord - 0.20), 0.27, 0.13, 0.36, backgroundRed, backgroundGreen, backgroundBlue, backgroundOpacity);
		drawText(username, optionsFont, (menuXCoord - 0.26), 0.09, 0.30, 0.30, bannerTextRed, bannerTextBlue, bannerTextGreen, bannerRectOpacity, false);
		drawText(playercoordx, optionsFont, (menuXCoord - 0.26), 0.11, 0.30, 0.30, bannerTextRed, bannerTextBlue, bannerTextGreen, bannerRectOpacity, false);
		drawText(playercoordy, optionsFont, (menuXCoord - 0.26), 0.13, 0.30, 0.30, bannerTextRed, bannerTextBlue, bannerTextGreen, bannerRectOpacity, false);
		drawText(playercoordz, optionsFont, (menuXCoord - 0.26), 0.15, 0.30, 0.30, bannerTextRed, bannerTextBlue, bannerTextGreen, bannerRectOpacity, false);
		drawText(isHoststr, optionsFont, (menuXCoord - 0.26), 0.17, 0.30, 0.30, bannerTextRed, bannerTextBlue, bannerTextGreen, bannerRectOpacity, false);
		drawText(ownerstr, optionsFont, (menuXCoord - 0.26), 0.19, 0.30, 0.30, bannerTextRed, bannerTextBlue, bannerTextGreen, bannerRectOpacity, false);
		drawText(apartof, optionsFont, (menuXCoord - 0.26), 0.21, 0.30, 0.30, bannerTextRed, bannerTextBlue, bannerTextGreen, bannerRectOpacity, false);
		//drawText(isGod, optionsFont, (menuXCoord - 0.26), 0.17, 0.30, 0.30, bannerTextRed, bannerTextBlue, bannerTextGreen, bannerRectOpacity, false);
	}
}

void PlayerOption(char* name, int id)
{
	addOption(name);
	if (currentOption == optionCount)
	{
		sidePlayerOption(id);
	}
}

void addsigninOption()
{
	addOption("Sign in");
	if (currentOption == optionCount && optionCount)
	{
		PLAYER::DISPLAY_SYSTEM_SIGNIN_UI(true);
	}
}
#pragma endregion