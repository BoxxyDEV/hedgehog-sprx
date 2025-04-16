
#include "sys/socket.h"
//#include "libpsutil.h"
#include <netdb.h>


RGBA toRGBA(int r, int g, int b, int a)
{
	RGBA rgbatmp;
	rgbatmp.r = r;
	rgbatmp.g = g;
	rgbatmp.b = b;
	rgbatmp.a = a;
	return rgbatmp;
}

Vector2 toVector2(float x, float y)
{
	Vector2 vec2;
	vec2.x = x;
	vec2.y = y;
	return vec2;
}

Vector3 toVector3(float x, float y, float z)
{
	Vector3 vec3;
	vec3.x = x;
	vec3.y = y;
	vec3.z = z;
	return vec3;
}

int howMuchhasEntityArrayFilled(Entity* Entarr)
{
	int filled = 0;
	for (int ent = 0; ent < sizeof(Entarr); ent++)
	{
		if (Entarr[ent] != NULL)
			filled += 1;
	}
	return filled;
}

bool isEntityArrFilled(Entity *entarr)
{
	if (howMuchhasEntityArrayFilled(entarr) == sizeof(entarr))
		return true;
	return false;
}

void appendtoEntityArray(Entity *Entarr, Entity Entity)
{
	int endofarr = howMuchhasEntityArrayFilled(Entarr);
	Entarr[endofarr+1] = Entity;
}




bool isScriptHost(Player pindex)
{
	if (pindex == NETWORK::NETWORK_GET_HOST_OF_SCRIPT("freemode", -1, 0))
		return true;
	return false;
}

bool isSelf(Player pIndex)
{
	if (pIndex == PLAYER::PLAYER_ID())
		return true;
	return false;
}


char* getNameandAttributes(int PlayerIndex)
{
	char* name = PLAYER::GET_PLAYER_NAME(PlayerIndex);
	char result[sizeof(name) + 40];
	snprintf(result, sizeof(result), "%s", name);
	if (SCRIPT::HAS_SCRIPT_LOADED("freemode"))
	{
		if (isHost(name))
			snprintf(result, sizeof(result), "%s ~r~(Host)", result);
		if (isScriptHost(PlayerIndex))
			snprintf(result, sizeof(result), "%s ~o~(SHost)", result);
	}
	if (isSelf(PlayerIndex))
		snprintf(result, sizeof(result), "%s ~p~(You)", result);
	return result;
}



void DialogMessage(char* text)
{
	Dialog::msgdialog_mode = Dialog::MODE_STRING_OK;
	Dialog::Show(text);
}

void DbgPrint(char* msg)
{
	printf(msg);
}

void SaveGameProg() // this function currently does not work
{
	printf("\nMoney: ");
	int bankBal = NETMONEY::NETWORK_GET_VC_BANK_BALANCE();
	printf(ItoS(bankBal));
	printf("\nRP: ");
	
	int rankStat = GAMEPLAY::GET_HASH_KEY("MP0_CHAR_XP_FM");
	int myRP = 0;
	STATS::STAT_GET_INT(rankStat, &myRP, false);
	FileAPI::CreateTextFile("/dev_hdd0/tmp/Hedgehog/Online/Money.txt", ItoS(bankBal), sizeof(ItoS(bankBal)));
	FileAPI::CreateTextFile("/dev_hdd0/tmp/Hedgehog/Online/RP.txt", ItoS(myRP), sizeof(ItoS(myRP)));
}

int addMin(int minute, int add = 1)
{
	int result;
	if ((minute+add) > 60) // if its going to add up over 60
	{
		result = (minute + add) - 60;
	}
	else {
		result = (minute + add); 
	}
	return result;
}

void GTANameChanger(char* name)
{
	*(char*)(0x41245170 + strlen(name)) = 0;
	*(char*)(0x412451E4 + strlen(name)) = 0;
	*(char*)(0x412451B8 + strlen(name)) = 0;
	strncpy((char*)0x41245170, name, strlen(name));
	strncpy((char*)0x412451E4, name, strlen(name));
	strncpy((char*)0x412451B8, name, strlen(name));
}


void settingssetup() 
{
	FileAPI::CreateDir("/dev_hdd0/tmp/Hedgehog");
	FileAPI::CreateDir("/dev_hdd0/tmp/Hedgehog/Online");
	FileAPI::CreateDir("/dev_hdd0/tmp/Hedgehog/settings");
	FileAPI::CreateTextFile("/dev_hdd0/tmp/Hedgehog/firststart.txt", "1", 1);
	FileAPI::CreateTextFile("/dev_hdd0/tmp/Hedgehog/settings/leftsided.txt", "0", 1);
	FileAPI::CreateTextFile("/dev_hdd0/tmp/Hedgehog/settings/CustomGTATextEnabled.txt", "1", 1);
	FileAPI::CreateTextFile("/dev_hdd0/tmp/Hedgehog/settings/MenuNameInTopLeft.txt", "1", 1);
	FileAPI::CreateTextFile("/dev_hdd0/tmp/Hedgehog/settings/Sounds.txt", "1", 1);
	FileAPI::CreateTextFile("/dev_hdd0/tmp/Hedgehog/Online/Money.txt", "500000", 6);
	FileAPI::CreateTextFile("/dev_hdd0/tmp/Hedgehog/Online/RP.txt", "2165850", 7);
	//FileAPI::CreateTextFile("/dev_hdd0/tmp/Hedgehog/Online/createdacc.txt", "1991 06 ", 7);
	FileAPI::CreateTextFile("/dev_hdd0/tmp/Hedgehog/read.txt", "Welcome to Hedgehog SPRX,\nCreated by Boxuga\nI just want to say thank you for downloading my menu.\n\nDownloads\n- Boxuga.com/hedgehogsprx\n\nFollow Boxuga\n- PS3: HedgehogSPRX\n- Xbox 360: notBoxuga\n- Discord: Boxuga\n- X: Boxuga_hedgehog\n-TikTok: Boxuga_hedgehog\n\n 3TA Online\n-Website: 3taonline.com\n\nSpecial Thanks to\n- JIREX\n- Parker\n- Lush Modz ツ\n- Buzz\n- Bogdan\n- Vali\n- gopro2027\n- Drew (aka FaZeModz)\n\nThanks to server boosters of 3TA Online & Boxuga's World\n- Dankie\n- WxSTxRN\n- Mike y", 486);
	autoMoney = 500000;
	autoRP = 2165850; // Rank 120

}

void Startup()
{
	//DialogMessage("hi");
#if Beta
	snprintf(releasebranch, sizeof(releasebranch), "Version: Beta %s", versionnumber);
#else
	snprintf(releasebranch, sizeof(releasebranch), "Version: Stable %s", versionnumber);
#endif
	if (FileAPI::FileExists("/dev_hdd0/tmp/Hedgehog/firststart.txt"))
	{
		char* firststart = FileAPI::ReadFile("/dev_hdd0/tmp/Hedgehog/firststart.txt"); // I just have this as an option just so for example (i add like custom maps like LTS, Paradise, Semjases, etc)
		if (firststart == "1")
		{
			settingssetup();
			DialogMessage("Reseting Hedgehog SPRX Settings");
		}

		if (FileAPI::FileExists("/dev_hdd0/tmp/Hedgehog/username.txt"))
		{
			isUsernameinfile = true;
			UsernamefromFile = FileAPI::ReadFile("/dev_hdd0/tmp/Hedgehog/username.txt");
			snprintf(ModUsername, sizeof(ModUsername), "%s", UsernamefromFile);
			char buf[150];
			snprintf(buf, sizeof(buf), "Welcome %s to Hedgehog SPRX\nCreated By Boxuga\nOpen With  + ", UsernamefromFile);
			DialogMessage(buf);

		}
		else
		{
			DialogMessage("Welcome to Hedgehog SPRX\nCreated By Boxuga\nOpen With  + ");
		}

		if (FileAPI::FileExists("/dev_hdd0/tmp/Hedgehog/settings/leftsided.txt"))
		{
			char* leftsided = FileAPI::ReadFile("/dev_hdd0/tmp/Hedgehog/settings/leftsided.txt");
			if (leftsided[0] == '1')
			{
				menuXCoord = 0.18f;
				textXCoord = 0.06f;
			}
			
		}

		if (FileAPI::FileExists("/dev_hdd0/tmp/Hedgehog/settings/CustomGTATextEnabled.txt"))
		{
			
			char* CustomGTATextEnabled = FileAPI::ReadFile("/dev_hdd0/tmp/Hedgehog/settings/CustomGTATextEnabled.txt");
			if (CustomGTATextEnabled[0] == '0')
			{
				CustomGTAText = false;
			}
			else
			{
				CustomGTAText = true;
			}
			
		}

		if (FileAPI::ReadFile("/dev_hdd0/tmp/Hedgehog/settings/MenuNameInTopLeft.txt"))
		{
			char* MenuNameInTopLeft = FileAPI::ReadFile("/dev_hdd0/tmp/Hedgehog/settings/MenuNameInTopLeft.txt");
			if (MenuNameInTopLeft[0] == '0')
			{
				Menuname = false;
			}
			else
			{
				
				Menuname = true;
			}
		}

		if (FileAPI::FileExists("/dev_hdd0/tmp/Hedgehog/settings/Sounds.txt"))
		{
			char* Soundsfile = FileAPI::ReadFile("/dev_hdd0/tmp/Hedgehog/settings/Sounds.txt");
			if (Soundsfile[0] == '0')
			{
				menuSounds = false;
			}
			else
			{
				menuSounds = true;
			}
		}


		// Basically reads text from the file and converts to an Integer and puts it into its variable
		if (FileAPI::FileExists("/dev_hdd0/tmp/Hedgehog/Online/Money.txt"))
		{
			autoMoney = StoI(FileAPI::ReadFile("/dev_hdd0/tmp/Hedgehog/Online/Money.txt"));
		}

		if (FileAPI::FileExists("/dev_hdd0/tmp/Hedgehog/Online/RP.txt"))
		{
			autoRP = StoI(FileAPI::ReadFile("/dev_hdd0/tmp/Hedgehog/Online/RP.txt"));
		}

		
	}
	else
	{
		settingssetup();
		char buf[150];
		DialogMessage("Welcome to Hedgehog SPRX\nCreated By Boxuga\nOpen With  + ");
	}

	
}

void savesettings()
{
	if (menuXCoord == 0.18f)
	{
		FileAPI::CreateTextFile("/dev_hdd0/tmp/Hedgehog/settings/leftsided.txt", "1", 1);
	}
	else
	{
		
		FileAPI::CreateTextFile("/dev_hdd0/tmp/Hedgehog/settings/leftsided.txt", "0", 1);
	}

	if (Menuname)
	{
		FileAPI::CreateTextFile("/dev_hdd0/tmp/Hedgehog/settings/MenuNameInTopLeft.txt", "1", 1);
	}

	if (!Menuname)
	{
		FileAPI::CreateTextFile("/dev_hdd0/tmp/Hedgehog/settings/MenuNameInTopLeft.txt", "0", 1);
	}
	FileAPI::CreateTextFile("/dev_hdd0/tmp/Hedgehog/username.txt", ModUsername, strlen(ModUsername)); 
}