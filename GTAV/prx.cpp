#include <cellstatus.h>
#include <sys/prx.h>
#include <sys/memory.h>
#include <sys/process.h>
#include <sys/ppu_thread.h>
#include <stdint.h>
#include <string.h>
#include <sys/timer.h>
#include <cell\cell_fs.h>
#include <string>
#include "Files.h"
#include "natives.h"
#include "enums.h"
#include "export.h"
#include <time.h>
#include "ExternalSources.h"

#define Beta true
#define DeveloperMode false
char* versionnumber = "0.2";

#include "Dialog.h"
#include "boxugafunctions.h"
#include "consts32.h"
#include "gopro2027.h"
#include "btncheck.h"
#include <fstream>

//#define version112 true

// add line by line support for reading a file maybe try use for loop look through it with [] and detecting \n character

char* mydomain = "boxuga.com";

#pragma region Hooking
int TOC;
int MAIN_HOOK_ADDRESS;
int og_main_hook_data;
#pragma endregion

SYS_MODULE_INFO("Hedgehog SPRX", 0, 1, 1);
SYS_MODULE_START(gtav_start);
SYS_LIB_DECLARE_WITH_STUB(LIBNAME, SYS_LIB_AUTO_EXPORT, STUBNAME);
SYS_LIB_EXPORT(gtav_stop, LIBNAME);
SYS_MODULE_STOP(gtav_stop);
SYS_MODULE_EXIT(gtav_stop);

#pragma region Variables
int submenu = 0;
int submenuLevel;
int lastSubmenu[20];
int lastOption[20];
int currentOption;
int optionCount;
bool optionPress = false;
bool rightPress = false;
bool leftPress = false;
bool fastRightPress = false;
bool fastLeftPress = false;
bool squarePress = false;
int selectedPlayer;
bool menuSounds = true;
bool keyboardActive = false;
int keyboardAction;
int *keyboardVar = 0;
char *infoText;
char *KeyboardInput;
bool newTimerTick = true;
int maxTimerCount;
bool newTimerTick2 = true;
int maxTimerCount2;
char *keyboardInput;
bool instructions = true;
int instructCount;
int mov;
bool instructionsSetupThisFrame;
bool xInstruction;
bool squareInstruction;
bool lrInstruction;

int bannerTextRed = 255;
int bannerTextGreen = 255; //57, 36, 163
int bannerTextBlue = 255;
int bannerTextOpacity = 255;
int bannerTextFont = 7;
int bannerRectRed = 57;
int bannerRectGreen = 36;
int bannerRectBlue = 163;
int bannerRectOpacity = 255;
int backgroundRed = 16;
int backgroundGreen = 16;
int backgroundBlue = 16;
int backgroundOpacity = 40;
int optionsRed = 255;
int optionsGreen = 255;
int optionsBlue = 255;
int optionsOpacity = 255;
int optionsFont = 0;
int scrollerRed = 255;
int scrollerGreen = 255;
int scrollerBlue = 255;
int scrollerOpacity = 50;
int indicatorRed = 255;
int indicatorGreen = 255;
int indicatorBlue = 255;
int indicatorOpacity = 255;
float menuXCoord = 0.80f;
float menuXScale = 0.25f;
float textXCoord = 0.68f;
float multiplyone = 0.035f;
float multiplytwo = 0.125f;
float drawadd = 0.1415f;
int maxOptions = 18;
Entity spawnedCougars[25];
Entity spawnedBouncyCougars[25];
int ScriptRequest = 1;

int recoverykiils;

// Boxuga's variables
int autoMoney = 0;
int autoRP = 0;
bool SuperJump;
bool NeverWanted;
bool UnlimitedAmmo;
bool GodMode;
bool Invisable;
bool DoNotRagdoll;
bool HardcoreMode;
bool SpawninCar = true;
bool DeleteOldVehicle = false;
bool GlitchySpeedRun;
bool hasLoadedOnline = false;
bool displayProperties = true;
int spawnloop = 0;
bool ExplosiveWeapon;
bool BurstWispon;
bool SuperPunch;
bool cartoongun;
bool SuperRun;
bool HornBoost; 
bool VehJump;
bool vehiclespeed;
bool SpriteOutline = true;
bool PoisonWater;
bool AngryCougars;
bool waterdamage;
int seconds;
bool skipcutscene = false;
bool FirstOpen = true;
bool PauseTime = false;
bool SyncTime = false;
bool Menuname = true;
int randoption = 1;
bool ChangeCharacterApperence;
bool SkipTutorial;
bool vehGodMode;
bool vehInvisiblity;
bool riotmode;
bool MobileRadio;
bool XYZDisplay;
bool FPSCounter;
bool NorthYanktonIPLLoad;
bool YachtIPLLoad;
bool FIBLobbyIPL;
bool MorgueIPL;
bool CreatorMode;
bool vehFixCosmeticCondition;
bool loopenginefix;
bool TennisMode;
bool TeleportGun;

bool moneydrop[18];
bool boostremoteplayercar[18];
bool launchremoteplayercar[18];
bool drawlinetoplayer[18];
int modelloop = 0;
// patching
bool patchcloud;
bool patchcloudsucceed;
bool patchsocialclubpolicies;
bool patchscaccount;
bool networkscpriv4;
bool networkscpriv9;
bool networkscpriv10;
bool Facebookpatch;
bool ROSValidCredsPatch;
bool SignedInPatch;
bool NetworkHaveOnlinePriviledges;
bool cloudavalabilitycheckresults;
bool DLCPResentSPOOF;
bool TutorialSession;
bool TutoialPendingSession;
bool CheckCompatConfig;
bool AussieMode;
bool SCTransitionNews;
bool FirstLoad = true;
int selectedHUDColor;
int CustomHUDR;
int CustomHUDG;
int CustomHUDB;
int CustomHUDA;
bool RSDevMode;
bool CustomGTAText = false;
int animduration = 5000;
// poison water
int timer;
char* keyboardStr = "";

int cougarpos = 0;
int bouncecougarpos = 0;

int fiveMin = NULL;

bool isUsernameinfile;
char* UsernamefromFile;
char ModUsername[50];

Vector3 bulletgun; // this stores where the bullet is

int tpoption = 1;

char releasebranch[50];

//Debug Options
bool DebugText;
float DebugTextX;
float DebugTextY;
float DebugTextScaleX;
float DebugTextScaleY;
int debugtextr, debugtextg, debugtextb, debugtexta;
char* DebugTextContent;
bool debugtextcentre;
float DEBUGBOX_X;
float DEBUGBOX_Y;
float DEBUGBOX_SCALEX;
float DEBUGBOX_SCALEY;
float flagcoordX = 0.08f;
float flagcoordY = 0.175f;
float flagscaleX = 0.03f;
float flagscaleY = 0.04f;
float flagoutlinescaleX = 0.03f;
float flagoutlinescaleY = 0.04f;

bool evProtection[3];

bool FreeShopping = false;
bool ChristmasMode = false;
bool ValentinesEvent = false;
bool CTFContent = false;

// Custom Text
char* GTAOTitle = "3TA Online こんにちは！";
char* Loading3TAO = "Loading 3TA Online";
char* LoadingGTA5 = "Loading Story Mode with Hedgehog SPRX";
char* InviteMSG = "You have been invited to join a 3TA Online session.\nJoin us on Discord: discord.gg/3TAOnline";
char* Leave3TAOnline = "Leave 3TA Online";
char* RockstarError = "Rockstar shutdown GTA Online on 16/12/2021. ~n~if you would like to invite someone you can do it through the mod menu~n~To open press ~INPUT_FRONTEND_RIGHT~ + ~INPUT_FRONTEND_ACCEPT~ to open select Network > Friends and then select your friends name from the menu to invite them to your session.";
char* InviteMessage = "You have been invited to join a 3TA Online session.3TAOnline.com\nboxuga.com/hedgehogsprx";

bool CustomHUDColorsEnabled[165];
RGBA CustomHUDColors[165];

//NoClip
bool NoClip;
Vector3 characterpos;

// collition
bool NoCollition = false;


// Speedometer
int speedosystem = 1;

// loop
bool rploop;
int rploopamount = 1;
bool moneyloop;
int moneyloopamount = 1;
#pragma endregion

#include "MenuUtils.h"
#include "BoxugaUtil.h"
#include "loop.h" // I know i have this after but its so this file can access the declared variables





int Hook()
{
	monitorButtons();
	otherLoop();
	//printbtns();
	optionCount = 0;
	switch (submenu)
	{
#pragma region Main Menu
	case Main_Menu:
		addTitle("Hedgehog");
		int year, month, day, hour, min, sec;
		TIME::GET_LOCAL_TIME(&year, &month, &day, &hour, &min, &sec);
		if (month == 6 && (day == 24 || day == 23))
		{
			addSubtitle("Happy Birthday Sonic The Hedgehog");
		}
		else if (month == 12 && day == 25) 
		{
			addSubtitle("Merry Christmas");
		}
		else if (month == 10 && day == 31)
		{
			addSubtitle("Happy Halloween");
		}
		else if (month == 1 && day == 26)
		{
			addSubtitle("Happy Australia Day");
		}
		else
		{
			addSubtitle("Created By Boxuga");
		}
		addSubmenuOption("Network", Network_menu);
		addSubmenuOption("Self Options", Self_Options);
		addSubmenuOption("Vehicle", Vechicle);
		addSubmenuOption("Weapons", Weapon_Menu);
		addSubmenuOption("Teleport", TeleportMenu);
		addSubmenuOption("Misc.", MiscMenu);
		addSubmenuOption("Settings", Settings, "Customize the menu");
#if DeveloperMode
		addSubmenuOption("Dev Options", DevOptions);
#endif
		break;
#pragma endregion
	case Network_menu:
		addTitle("Network");
		addSubmenuOption("Players", Players_List);
		addSubmenuOption("Friends", Friends_List);
		addSubmenuOption("Recovery", Recovery);
		addSubmenuOption("Name Changer", CustomNameMenu);
		addSubmenuOption("Protections", ProtectionMenu);
		addSubmenuOption("Tunables", TunablesMenu);
		break;
	case TunablesMenu:
		addTitle("Tunables");
		addBoolOption("Free Shopping", &FreeShopping);
		addBoolOption("Christmas Mode", &ChristmasMode);
		addBoolOption("Valentines Event", &ValentinesEvent);
		switch (getOption())
		{
		case 1:
			gopro2027::Global(262144 + 54).set(FreeShopping);
			gopro2027::Global(262144 + 55).set(FreeShopping);
			gopro2027::Global(262144 + 56).set(FreeShopping);
			gopro2027::Global(262144 + 57).set(FreeShopping);
			gopro2027::Global(262144 + 58).set(FreeShopping);
			gopro2027::Global(262144 + 60).set(FreeShopping);
			gopro2027::Global(262144 + 61).set(FreeShopping);
			gopro2027::Global(262144 + 62).set(FreeShopping);
			gopro2027::Global(262144 + 63).set(FreeShopping);
			gopro2027::Global(262144 + 64).set(FreeShopping);
			gopro2027::Global(262144 + 59).set(FreeShopping);
			break;
		case 2:
			gopro2027::Global(262144 + 4579).set(ChristmasMode);
			gopro2027::Global(262144 + 4586).set(ChristmasMode);
			break;
		case 3: 
			gopro2027::Global(262144 + 4685).set(ValentinesEvent);
			break;
		}
		break;
	case ProtectionMenu:
		addTitle("Protections");
		addBoolOption("Non-Host Kick", &evProtection[KickProtection]);
		addBoolOption("Fake Leave", &evProtection[FakeLeaveProtection]);
		addBoolOption("Animation/Teleport", &evProtection[evProtections::AnimationTeleport]);
		switch (getOption())
		{
		case evProtections::KickProtection:
			*(int*)0x1252FC8 = evProtection[KickProtection] ? 0x4E800020 : 0x7C0802A6; // Non-Host Kick
			*(int*)0x12533A0 = evProtection[KickProtection] ? 0x4E800020 : 0x7C0802A6; // Vote Kick
			break;
		case evProtections::FakeLeaveProtection:
			*(int*)0x124465C = evProtection[FakeLeaveProtection] ? 0x4E800020 : 0x7C0802A6;
			break;
		case evProtections::AnimationTeleport:
			*(int*)0x1245720 = evProtection[AnimationTeleport] ? 0x4E800020 : 0x7C0802A6; 
			*(int*)0x124C988 = evProtection[AnimationTeleport] ? 0x4E800020 : 0x7C0802A6; 
			*(int*)0x124CD68 = evProtection[AnimationTeleport] ? 0x4E800020 : 0x7C0802A6; 
			*(int*)0x124CFCC = evProtection[AnimationTeleport] ? 0x4E800020 : 0x7C0802A6;
			break;

		}
		break;
	case CustomNameMenu:
		addTitle("Custom Names");
		addSubtitle("btw no one else sees these");
		addKeyboardOption("Enter Name", NameChanger, "", 30);
		addOption(ModUsername, "Mod Menu username"); 
		addOption("Sonic The Hedgehog");
		addOption("Tails The Fox");
		addOption("Fishsticks");
		addOption("Eric Cartman");
		addOption("Spongebob Squarepants");
		addOption("Park Car");
		addOption("Luffy");
		addOption("Sony");
		addOption("Xbox");
		addOption("Ban Patrol");
		addOption("Nintendo");
		addOption("Mario");
		addOption("Elon Musk");
		addOption("FaZe");
		addOption("FIB");
		addOption("Holden");
		switch (getOption())
		{
		case 2:
			GTANameChanger(ModUsername);
			break;
		case 3:
			GTANameChanger("Sonic The Hedgehog");
			break;
		case 4:
			GTANameChanger("Tails The Fox");
			break;
		case 5:
			GTANameChanger("Fishsticks");
			break;
		case 6:
			GTANameChanger("Eric Cartman");
			break;
		case 7:
			GTANameChanger("Spongebob Squarepants");
			break;
		case 8:
			GTANameChanger("Park Car");
			break;
		case 9:
			GTANameChanger("Luffy");
			break;
		case 10:
			GTANameChanger("Sony");
			break;
		case 11:
			GTANameChanger("Xbox");
			break;
		case 12:
			GTANameChanger("Ban Patrol");
			break;
		case 13:
			GTANameChanger("Nintendo");
			break;
		case 14:
			GTANameChanger("Mario");
			break;
		case 15:
			GTANameChanger("Elon Musk");
			break;
		case 16:
			GTANameChanger("FaZe");
			break;
		case 17:
			GTANameChanger("FIB");
			break;
		case 18:
			GTANameChanger("Holden");
			break;
		}
		break;
#pragma Friends List
	case Friends_List:
		addTitle("Invite Friends");
		addKeyboardOption("Invite by PSN", 3, "", 50);
		int friendcount = NETWORK::NETWORK_GET_FRIEND_COUNT(); 
		int friendsonline = 0;
		for (int i = 0; i < friendcount; i++)
		{
			char buf[70];
			char* psn = NETWORK::NETWORK_GET_FRIEND_NAME(i); // get name based on postion
			snprintf(buf, sizeof(buf), "%s", psn);
			friendsonline++;
			if (NETWORK::NETWORK_IS_FRIEND_IN_SAME_TITLE(psn) && !NETWORK::NETWORK_IS_FRIEND_IN_MULTIPLAYER(psn))
			{
				snprintf(buf, sizeof(buf), "%s ~g~is playing GTA V", buf);
			}
			else if (NETWORK::NETWORK_IS_FRIEND_IN_MULTIPLAYER(psn))
			{
				snprintf(buf, sizeof(buf), "%s ~g~is playing 3TA/RE:V", buf);
			}
			else if (NETWORK::NETWORK_IS_FRIEND_ONLINE(psn) && !NETWORK::NETWORK_IS_FRIEND_IN_SAME_TITLE(psn) && !NETWORK::NETWORK_IS_FRIEND_IN_MULTIPLAYER(psn))
			{
				snprintf(buf, sizeof(buf), "%s ~g~Online", buf);
			}
			addOption(buf);
			if (optionPress)
			{
				if (currentOption == friendsonline)
				{
					ExternalSources::GameInvite(NETWORK::NETWORK_GET_FRIEND_NAME(i - 1));
				}
			}
			
			
		}
		
		break;
#pragma endregion
#pragma region Players List
	case Players_List:
		addTitle("Players List");

		int optionplayercount = 0;
		for (int i = 0; i < 18; i++)
		{
			
			if (strcmp("**Invalid**", PLAYER::GET_PLAYER_NAME(i))) // the reason why i use compare the name with that instead of using the IS_PLAYER_PLAYING is because it will return false when player is dead
			{
				char* playerinfo = getNameandAttributes(i);
				optionplayercount++;
				PlayerOption(playerinfo, i);
				if (optionPress)
				{
					if (currentOption == optionplayercount)
					{
						selectedPlayer = i;
						changeSubmenu(Player_Options);
					}
				}
				
			}
		}
		break;
#pragma endregion
#pragma region Player Options
	case Player_Options:
		addTitle(PLAYER::GET_PLAYER_NAME(selectedPlayer));
		//various player options here
		//use PLAYER::GET_PLAYER_PED(selectedPlayer) to get the ped rather than player.
		addSubmenuOption("Fun Options", NicePlayerOtions);
		addSubmenuOption("Naughty Options", MalicousPlayersOptions);
		addSubmenuOption("Animations", AnimationPlayerOptions);
		addBoolOption("Draw Line to them", &drawlinetoplayer[selectedPlayer]);
		addOption("Teleport to (Them)");
		addOption("Teleport to (Me)");
		addOption("Kick (Host-Only)");
		switch (getOption())
		{
		case 5:	 
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::GET_PLAYER_PED(selectedPlayer), false))
			{
				int vehhandle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED(selectedPlayer));
				PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), vehhandle, freeseat(vehhandle));
			}
			else
			{
				Vector3 Coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true);
				Boxuga::teleportcharacter(Coords);
			}
			break;
		case 6:
			AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::GET_PLAYER_PED(selectedPlayer)); // clear any animations of selected player
			Vector3 playerpos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true); // get the modders pos
			int scene = NETWORK::NETWORK_CREATE_SYNCHRONISED_SCENE_1(playerpos.x, playerpos.y, playerpos.z, 0.0, 0.0, 0.0, 2, 0, 0, 0, 0, 0); // 
			NETWORK::NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE(PLAYER::GET_PLAYER_PED(selectedPlayer), scene, "misschinese2_crystalmazemcs1_cs", "dance_loop_tao", 8.0, 1.0, 3, 0, 30, 0);
			NETWORK::NETWORK_START_SYNCHRONISED_SCENE(scene);
			
			break;
		case 7:
			if (PLAYER::PLAYER_ID() != selectedPlayer)
			{
				if (isHost(PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID())))
				{
					NETWORK::NETWORK_SESSION_KICK_PLAYER(selectedPlayer);
				}
				else
				{
					printscreen("~ws~ ~p~Hedgehog SPRX~w~ ~ws~~n~ You need to be host to kick a player");
				}
			}
			else
			{
				printscreen("~ws~ ~p~Hedgehog SPRX~w~ ~ws~~n~ I do not think you want to kick yourself");
			}
			break;
		}
		break;
#pragma endregion
#pragma region Nice Option Players
	case NicePlayerOtions:
		addTitle("Fun");
		addBoolOption("Money Drop", &moneydrop[selectedPlayer]);
		addOption("Boost Car");
		addOption("Launch Vehicle");
		switch (getOption()) {
		case 2:
			boostremoteplayercar[selectedPlayer] = true;
			break;
		case 3:
			launchremoteplayercar[selectedPlayer] = true;
			break;
		}
		break;

#pragma endregion
#pragma region Naughty OPtions players
	case MalicousPlayersOptions:
		addTitle("Naughty");
		addSubtitle("please do not abuse anyone");
		addOption("Explode");
		switch (getOption())
		{
		case 1: 
			Vector3 Coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true);
			FIRE::ADD_EXPLOSION(Coords.x, Coords.y, Coords.z, 0, 100, true, false, false);
			break;
		}
		break;
	case AnimationPlayerOptions:
		addTitle("Animations");
		addOption("Clear Tasks");
		addOption("Dance");
		addOption("Situps");
		addOption("Electrocute"); 
		addOption("Suicide");
		addOption("Pole Dance");
		addOption("Fire Ragdoll");
		addOption("Pullups");
		addOption("Lay Down");
		addOption("Sunbathe");
		switch (getOption()) {
		case 1: AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::GET_PLAYER_PED(selectedPlayer)); break;
		case 2: Boxuga::PlayAnim(PLAYER::GET_PLAYER_PED(selectedPlayer), "misschinese2_crystalmazemcs1_cs", "dance_loop_tao"); break; 
		case 3: Boxuga::PlayAnim(PLAYER::GET_PLAYER_PED(selectedPlayer), "amb@world_human_sit_ups@male@base", "base"); break;
		case 4: Boxuga::PlayAnim(PLAYER::GET_PLAYER_PED(selectedPlayer), "ragdoll@human", "electrocute"); break;
		case 5: Boxuga::PlayAnim(PLAYER::GET_PLAYER_PED(selectedPlayer), "mp_suicide", "pistol"); break;
		case 6: Boxuga::PlayAnim(PLAYER::GET_PLAYER_PED(selectedPlayer), "mini@strip_club@pole_dance@pole_dance1", "pd_dance_01"); break;
		case 7: Boxuga::PlayAnim(PLAYER::GET_PLAYER_PED(selectedPlayer), "ragdoll@human", "on_fire"); break;
		case 8: Boxuga::PlayAnim(PLAYER::GET_PLAYER_PED(selectedPlayer), "amb@prop_human_muscle_chin_ups@male@base", "base"); break;
		case 9: Boxuga::PlayAnim(PLAYER::GET_PLAYER_PED(selectedPlayer), "amb@world_human_bum_slumped@male@laying_on_left_side@idle_a", "idle_a"); break;
		case 10: Boxuga::PlayAnim(PLAYER::GET_PLAYER_PED(selectedPlayer), "amb@world_human_sunbathe@female@back@idle_a", "idle_c"); break;
		}
		break;
#pragma endregion
#pragma region Self Options
	case Self_Options:
		addTitle("Self Options");
		addSubmenuOption("Animations", Animation_Options);
		addSubmenuOption("Model Changer", Model_menu);
		addBoolOption("God Mode", &GodMode);
		addBoolOption("Invisibility", &Invisable);
		addBoolOption("Super Jump", &SuperJump);
		addBoolOption("Sonic Speed", &SuperRun);
		addBoolOption("Glitchy Speed (RTM)", &GlitchySpeedRun);
		addBoolOption("Never Wanted", &NeverWanted);
		addBoolOption("Never Ragdoll", &DoNotRagdoll);
		addBoolOption("Hardcore Mode", &HardcoreMode);
		addBoolOption("Poison Water", &PoisonWater);
		addBoolOption("Hot Cougars in your area", &AngryCougars);
		addBoolOption("Rockstar developer", &RSDevMode);
		addBoolOption("No Clip (Buggy)", &NoClip);
		addBoolOption("No Collision", &NoCollition);
		addBoolOption("Tennis Mode", &TennisMode);
		switch (getOption()) {
		case 14: 
			characterpos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
			break;
		case 16:
			GAMEPLAY::ENABLE_TENNIS_MODE(PLAYER::PLAYER_PED_ID(), TennisMode, false);
			break;
		}
		break;
	case Animation_Options:
		addTitle("Animations");
		addOption("Stop Animation");
		addOption("Dance");
		addOption("Situps");
		addOption("Electrocute");
		addOption("Suicide");
		addOption("Pole Dance");
		addOption("Fire Ragdoll");
		addOption("Pullups");
		addOption("Lay Down");
		addOption("Sunbathe");
		switch (getOption())
		{
		case 1: AI::CLEAR_PED_TASKS(PLAYER::PLAYER_PED_ID()); break;
		case 2: Boxuga::PlayAnim(PLAYER::PLAYER_PED_ID(), "misschinese2_crystalmazemcs1_cs", "dance_loop_tao"); break;
		case 3: Boxuga::PlayAnim(PLAYER::PLAYER_PED_ID(), "amb@world_human_sit_ups@male@base", "base"); break;
		case 4: Boxuga::PlayAnim(PLAYER::PLAYER_PED_ID(), "ragdoll@human", "electrocute"); break;
		case 5: Boxuga::PlayAnim(PLAYER::PLAYER_PED_ID(), "mp_suicide", "pistol"); break;
		case 6: Boxuga::PlayAnim(PLAYER::PLAYER_PED_ID(), "mini@strip_club@pole_dance@pole_dance1", "pd_dance_01"); break;
		case 7: Boxuga::PlayAnim(PLAYER::PLAYER_PED_ID(), "ragdoll@human", "on_fire"); break;
		case 8: Boxuga::PlayAnim(PLAYER::PLAYER_PED_ID(), "amb@prop_human_muscle_chin_ups@male@base", "base"); break;
		case 9: Boxuga::PlayAnim(PLAYER::PLAYER_PED_ID(), "amb@world_human_bum_slumped@male@laying_on_left_side@idle_a", "idle_a"); break;
		case 10: Boxuga::PlayAnim(PLAYER::PLAYER_PED_ID(), "amb@world_human_sunbathe@female@back@idle_a", "idle_c"); break;
		}
		break;
	case Model_menu:
		addTitle("Models");
		addSubtitle("I wish they had sonic in the game");
		addOption("Alien");
		addOption("Cop");
		addOption("Chimp");
		addOption("Monkey Guy");
		addOption("Space Ranger");
		addOption("Average American");
		addOption("Jesus");
		switch (getOption())
		{
		case 1: Boxuga::clientModel("s_m_m_movalien_01"); break;
		case 2: Boxuga::clientModel("s_m_y_cop_01"); break;
		case 3: Boxuga::clientModel("a_c_chimp"); break;
		case 4: Boxuga::clientModel("u_m_y_pogo_01"); break;
		case 5: Boxuga::clientModel("u_m_y_rsranger_01"); break;
		case 6: Boxuga::clientModel("u_m_m_griff_01"); break;
		case 7: Boxuga::clientModel("u_m_m_jesus_01"); break;
		}
		break;
#pragma endregion
#pragma region Settings
	case Settings:
		addTitle("Settings");
		addSubmenuOption("Banners", Settings_Banners);
		addSubmenuOption("Body", Settings_Body);
		addSubmenuOption("Scroller", Settings_Scroller);
		addSubmenuOption("Indicators", Settings_Indicators);
		addSubmenuOption("Menu Elements", SettingsSizeMenu);
		addSubmenuOption("Info/Credits", Credits);
		addBoolOption("Sounds", &menuSounds);
		addBoolOption("Instructions", &instructions);
		addBoolOption("Draw Menuname on Top Left", &Menuname);
		addCustomBoolOption("Left Sided", menuXCoord, 0.18f);
		addIntOption("Max Options", &maxOptions, 1, 20, false);
		addKeyboardOption("Enter Username", UsernameModMenu, ModUsername, 30, "This is shown when you start the game");
		addOption("Save Settings");
		addOption("Save Game Stats");
		switch (getOption())
		{
		case 10:
			if (menuXCoord == 0.18f)
			{
				menuXCoord = 0.80f;
				textXCoord = 0.68f;
			}
			else
			{
				menuXCoord = 0.18f;
				textXCoord = 0.06f;
			}
			break;
		case 13:
			savesettings();
			break;
		case 14:
			SaveGameProg();
			break;
		}
		break;
	case Settings_Banners:
		addTitle("Banners");
		addIntOption("Text Red", &bannerTextRed, 0, 255, true);
		addIntOption("Text Green", &bannerTextGreen, 0, 255, true);
		addIntOption("Text Blue", &bannerTextBlue, 0, 255, true);
		addIntOption("Text Opacity", &bannerTextOpacity, 0, 255, true);
		addIntOption("Text Font", &bannerTextFont, 0, 7, false);
		addIntOption("Rect Red", &bannerRectRed, 0, 255, true);
		addIntOption("Rect Green", &bannerRectGreen, 0, 255, true);
		addIntOption("Rect Blue", &bannerRectBlue, 0, 255, true);
		addIntOption("Rect Opacity", &bannerRectOpacity, 0, 255, true);
		break;
	case Settings_Body:
		addTitle("Body");
		addIntOption("Text Red", &optionsRed, 0, 255, true);
		addIntOption("Text Green", &optionsGreen, 0, 255, true);
		addIntOption("Text Blue", &optionsBlue, 0, 255, true);
		addIntOption("Text Opacity", &optionsOpacity, 0, 255, true);
		addIntOption("Text Font", &optionsFont, 0, 7, false);
		addIntOption("Rect Red", &backgroundRed, 0, 255, true);
		addIntOption("Rect Green", &backgroundGreen, 0, 255, true);
		addIntOption("Rect Blue", &backgroundBlue, 0, 255, true);
		addIntOption("Rect Opacity", &backgroundOpacity, 0, 255, true);
		break;
	case Settings_Scroller:
		addTitle("Scroller");
		addIntOption("Red", &scrollerRed, 0, 255, true);
		addIntOption("Green", &scrollerGreen, 0, 255, true);
		addIntOption("Blue", &scrollerBlue, 0, 255, true);
		addIntOption("Opacity", &scrollerOpacity, 0, 255, true);
		break;
	case Settings_Indicators:
		addTitle("Indicators");
		addIntOption("Red", &indicatorRed, 0, 255, true);
		addIntOption("Green", &indicatorGreen, 0, 255, true);
		addIntOption("Blue", &indicatorBlue, 0, 255, true);
		addIntOption("Opacity", &indicatorOpacity, 0, 255, true);
		break;
	case SettingsSizeMenu:
		addTitle("Size menu");
		addFloatOption("Menu X", &menuXCoord, 0.0, 10.0, true);
		addFloatOption("Text X", &textXCoord, 0.0, 10.0, true);
		addFloatOption("Menu Scale X", &menuXScale, 0.0, 10.0, true);
		addFloatOption("Multiply One", &multiplyone, 0.0, 10.0, true);
		addFloatOption("Multiply Two", &multiplytwo, 0.0, 10.0, true);
		break;
#pragma endregion
#pragma region credits
	case Credits:
		addTitle("Info/Credits");
		addOption(releasebranch);
		addOption("Developer: Boxuga");
		addOption("Base: 2much4U");
		addOption("gopro_2027");
		addOption("- Text Profanity Fix");
		addOption("- Stats Money + RP");
		addOption("- Hooking");
		addOption("Helping with HEN");
		addOption("- Buzz#2036 - Testing on HEN");
		addOption("Coding Tutorials & Exit on Crash");
		addOption("- Drewbeedoo (aka FaZe Modz)");
		addOption("Invites");
		addOption("- Parker - leaking it");
		addOption("- Joker - Finding how to invite with a native");
		addOption("Protection");
		addOption("- Joker - freeze protection");
		addOption("- Alexander - leaking it");
		addOption("- dontcry - Protection");
		addOption("3TAOnline");
		addOption("- JIREX: Made AIO PKG for Online");
		addOption("- discord.gg/3taonline");
		addOption("- 3taonline.com");
		addOption("Misc");
		addOption("- RLZ (Fixing DInput)");
		break;
#pragma endregion
#pragma region Recovery
	case Recovery:
		addTitle("Recovery");
		addSubmenuOption("Give Rank", Rank_menu);
		addOption("Give $10 million");
		addBoolOption("Money Loop", &moneyloop);
		addIntOption("Money Loop amount", &moneyloopamount, 0, 10000000, true);
		addBoolOption("RP Loop", &rploop, "will quit when you hit rank 1000");
		addIntOption("RP Loop amount", &rploopamount, 0, 2165850, true);
		switch (getOption()) {
		case 2: NETMONEY::NETWORK_EARN_FROM_ROCKSTAR(10000000); break;
		}
		break;
	case Rank_menu:
		addTitle("Rank");
		addSubmenuOption("Preset Ranks", PresetRanks_Menu);
		addOption("+800 xp (lvl 1)");
		addOption("+24000 xp (lvl 10)");
		addOption("+127100 xp (lvl 25)");
		addOption("+448800 xp (lvl 50)");
		addOption("+806500 xp (lvl 69)");
		addOption("+1584350100 xp (Lvl 100)");
		addOption("+4691850 xp (lvl 200)");
		addOption("+8299350 xp (lvl 300)");
		addOption("+12406850 xp (lvl 400)");
		switch (getOption())
		{
		case 2:
			int xp1;
			STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_XP_FM"), &xp1, false);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_XP_FM"), xp1 + 800, false);
			break;
		case 3:
			int xp10;
			STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_XP_FM"), &xp10, false);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_XP_FM"), xp10 + 24000, false); // +rank 10
			break;
		case 4:
			int xp25;
			STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_XP_FM"), &xp25, false);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_XP_FM"), xp25 + 127100, false); // +rank 25
			break;
		case 5:
			int xp50;
			STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_XP_FM"), &xp50, false);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_XP_FM"), xp50 + 448800, false); // +rank 50
			break;
		case 6:
			int xp69;
			STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_XP_FM"), &xp69, false);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_XP_FM"), xp69 + 806500, false); // +rank 69
			break;
		case 7:
			int xp100;
			STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_XP_FM"), &xp100, false);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_XP_FM"), xp100 + 1584350, false); // +rank 100
			break;
		case 8:
			int xp200;
			STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_XP_FM"), &xp200, false);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_XP_FM"), xp200 + 4691850, false); // +rank 200
			break;
		case 9:
			int xp300;
			STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_XP_FM"), &xp300, false);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_XP_FM"), xp300 + 8299350, false); // +rank 300
			break;
		case 10:
			int xp400;
			STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_XP_FM"), &xp400, false);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_XP_FM"), xp400 + 12406850, false); // +rank 400
			break;

		}
		break;
	case PresetRanks_Menu:
		addTitle("Preset Ranks");
		addSubtitle("note: some will need you to find new session");
		addOption("0");
		addOption("4");
		addOption("10");
		addOption("14");
		addOption("25");
		addOption("50");
		addOption("69");
		addOption("100");
		addOption("200"); // rank 200 & OK response from HTTP server
		addOption("300");
		addOption("400");
		addOption("404"); // http error 404
		addOption("420"); // smoke weed everyday
		addOption("1000", "This will cause the game to fake leave");
		switch (getOption()) {
		case 1: STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_XP_FM"), 0, false); break;
		case 2: STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_XP_FM"), 3800, false); break;
		case 3: STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_XP_FM"), 24000, false); break; // rank 10
		case 4: STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_XP_FM"), 44200, false); break;
		case 5: STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_XP_FM"), 127100, false); break; // rank 25
		case 6: STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_XP_FM"), 448800, false); break;
		case 7: STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_XP_FM"), 806500, false); break; // rank 69
		case 8: STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_XP_FM"), 1584350, false); break;
		case 9: STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_XP_FM"), 4691850, false); break; // rank 200
		case 10: STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_XP_FM"), 8299350, false); break;
		case 11: STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_XP_FM"), 12406850, false); break; // rank 400
		case 12: STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_XP_FM"), 12581550, false); break;
		case 13: STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_XP_FM"), 13288350, false); break; // rank 420
		case 14: 
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_XP_FM"), 23775925, false);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_XP_FM"), 47551850, false);
			break;
		}
		break;
#pragma endregion
#pragma region Vehicle
	case Vechicle:
		addTitle("Vehicle");
		addSubmenuOption("Spawner", VehicleSpawnerMenu);
		addOption("Fix Vehicle");
		addOption("Flip Vehicle Upright");
		addBoolOption("God Mode", &vehGodMode);
		addBoolOption("Loop Vehicle Fix", &vehFixCosmeticCondition);
		addBoolOption("Loop Engine Fix", &loopenginefix);
		addBoolOption("Invisible", &vehInvisiblity);
		addBoolOption("Horn Boost", &HornBoost);
		addBoolTextOption("Speedometer", &vehiclespeed, &speedosystem, 1, 2, "Metric", "Imperial");
		addKeyboardOption("Custom Number Plate", VehicleNumberPlate, "Hedgehog", 9);
		switch (getOption()) {
		case 2:
			VEHICLE::SET_VEHICLE_FIXED(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID())); break;
		case 3: 
			VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID())); break;
		}
		break;
	case VehicleSpawnerMenu:
		addTitle("Spawner");
		addSubmenuOption("Spawn Settings", VehicleSpawnerSettingsMenu);
		addSubmenuOption("Super Cars", SuperCars);
		addSubmenuOption("Sports Cars", SportsCars);
		addSubmenuOption("Utility", UtilityCars);
		addSubmenuOption("Service", ServiceVehicles);
		addSubmenuOption("Sedans", Sedans);
		addSubmenuOption("Emergency", EmergencyVehicles);
		addSubmenuOption("Offroad", Offroad);
		addSubmenuOption("Vans", Vanslist);
		addSubmenuOption("Boats", Boats);
		addSubmenuOption("Motocycle", Motocycles);
		addSubmenuOption("Planes", Planes_menu);
		addSubmenuOption("Muscle", MuscleCars);
		addSubmenuOption("SUVs", SUV_menu);
		addSubmenuOption("Helicopters", Helicopters_Menu);
		addSubmenuOption("Military", MilitaryVeh_menu);
		addSubmenuOption("Commercial", CommercialVeh_menu);
		addSubmenuOption("Compacts", CompactsVeh_menu);
		addSubmenuOption("Cycles", CyclesVeh_menu);
		addSubmenuOption("Industrial", Industrialveh_menu);
		addSubmenuOption("Coupes", CoupesVeh_menu);
		addSubmenuOption("Trains", TrainsVeh_menu);
		addKeyboardOption("Spawn Via Model Name", KeyboardInputs::TextVehSpawner, "voltic", 16);
		break;
	case VehicleSpawnerSettingsMenu:
		addTitle("Spawner Settings");
		addBoolOption("Spawn Inside", &SpawninCar);
		addBoolOption("Delete Old Vehicle", &DeleteOldVehicle);
		break;
#pragma region SuperCars
	case SuperCars:
		addTitle("Super");
		addOption("Adder");
		addOption("Bullet");
		addOption("Cheetah");
		addOption("Entityxf");
		addOption("Infernus");
		addOption("Vacca");
		addOption("Voltic");
		addOption("Turismo R");
		switch (getOption()) {
		case 1: spawnloop = VEHICLE_ADDER; break;
		case 2: spawnloop = VEHICLE_BULLET; break;
		case 3: spawnloop = VEHICLE_CHEETAH; break;
		case 4: spawnloop = VEHICLE_ENTITYXF; break;
		case 5: spawnloop = VEHICLE_INFERNUS; break;
		case 6: spawnloop = VEHICLE_VACCA; break;
		case 7: spawnloop = VEHICLE_VOLTIC; break;
		case 8: spawnloop = VEHICLE_TURISMOR; break;
		}
		break;
#pragma endregion
#pragma region Sports
	case SportsCars:
		addTitle("Sports");
		addOption("Banshee");
		addOption("Buffalo");
		addOption("Buffalo2");
		addOption("Carbonizzare");
		addOption("Comet2");
		addOption("Coquette");
		addOption("Elegy2");
		addOption("Feltzer2");
		addOption("Fusilade");
		addOption("Futo");
		addOption("Jb700");
		addOption("Khamelion");
		addOption("Manana");
		addOption("Monroe");
		addOption("9F");
		addOption("Ninef2");
		addOption("Penumbra");
		addOption("Peyote");
		addOption("Rapidgt");
		addOption("Rapidgt2");
		addOption("Schwarzer");
		addOption("Stinger");
		addOption("Stingergt");
		addOption("Sultan");
		addOption("Surano");
		addOption("Tornado");
		addOption("Tornado2");
		addOption("Tornado3");
		addOption("Tornado4");
		addOption("Ztype");
		addOption("Btype");
		addOption("Jester");
		addOption("Alpha");
		switch (getOption()) {
		case 1: spawnloop = VEHICLE_BANSHEE; break;
		case 2: spawnloop = VEHICLE_BUFFALO; break;
		case 3: spawnloop = VEHICLE_BUFFALO2; break;
		case 4: spawnloop = VEHICLE_CARBONIZZARE; break;
		case 5: spawnloop = VEHICLE_COMET2; break;
		case 6: spawnloop = VEHICLE_COQUETTE; break;
		case 7: spawnloop = VEHICLE_ELEGY2; break;
		case 8: spawnloop = VEHICLE_FELTZER2; break;
		case 9: spawnloop = VEHICLE_FUSILADE; break;
		case 10: spawnloop = VEHICLE_FUTO; break;
		case 11: spawnloop = VEHICLE_JB700; break;
		case 12: spawnloop = VEHICLE_KHAMELION; break;
		case 13: spawnloop = VEHICLE_MANANA; break;
		case 14: spawnloop = VEHICLE_MONROE; break;
		case 15: spawnloop = VEHICLE_NINEF; break;
		case 16: spawnloop = VEHICLE_NINEF2; break;
		case 17: spawnloop = VEHICLE_PENUMBRA; break;
		case 18: spawnloop = VEHICLE_PEYOTE; break;
		case 19: spawnloop = VEHICLE_RAPIDGT; break;
		case 20: spawnloop = VEHICLE_RAPIDGT2; break;
		case 21: spawnloop = VEHICLE_SCHWARZER; break;
		case 22: spawnloop = VEHICLE_STINGER; break;
		case 23: spawnloop = VEHICLE_STINGERGT; break;
		case 24: spawnloop = VEHICLE_SULTAN; break;
		case 25: spawnloop = VEHICLE_SURANO; break;
		case 26: spawnloop = VEHICLE_TORNADO; break;
		case 27: spawnloop = VEHICLE_TORNADO2; break;
		case 28: spawnloop = VEHICLE_TORNADO3; break;
		case 29: spawnloop = VEHICLE_TORNADO4; break;
		case 30: spawnloop = VEHICLE_ZTYPE; break;
		case 31: spawnloop = VEHICLE_BTYPE; break;
		case 32: spawnloop = VEHICLE_JESTER; break;
		case 33: spawnloop = VEHICLE_ALPHA; break;
		}
		break;
#pragma endregion
#pragma region Utility
	case UtilityCars:
		addTitle("Utility");
		addOption("Airtug");
		addOption("Armytanker");
		addOption("Armytrailer");
		addOption("Armytrailer2");
		addOption("Baletrailer");
		addOption("Boattrailer");
		addOption("Caddy");
		addOption("Caddy2");
		addOption("Docktrailer");
		addOption("Docktug");
		addOption("Forklift");
		addOption("Freighttrailer");
		addOption("Graintrailer");
		addOption("Mower");
		addOption("Proptrailer");
		addOption("Raketrailer");
		addOption("Ripley");
		addOption("Sadler");
		addOption("Sadler2");
		addOption("Scrap");
		addOption("Tanker");
		addOption("Towtruck");
		addOption("Towtruck2");
		addOption("Tr2");
		addOption("Tr3");
		addOption("Tr4");
		addOption("Tractor");
		addOption("Tractor2");
		addOption("Tractor3");
		addOption("Trailerlogs");
		addOption("Trailers");
		addOption("Trailers2");
		addOption("Trailers3");
		addOption("Trailersmall");
		addOption("Trflat");
		addOption("Tvtrailer");
		addOption("Utillitruck");
		addOption("Utillitruck2");
		addOption("Utillitruck3");
		switch (getOption()) {
		case 1: spawnloop = VEHICLE_AIRTUG; break;
		case 2: spawnloop = VEHICLE_ARMYTANKER; break;
		case 3: spawnloop = VEHICLE_ARMYTRAILER; break;
		case 4: spawnloop = VEHICLE_ARMYTRAILER2; break;
		case 5: spawnloop = VEHICLE_BALETRAILER; break;
		case 6: spawnloop = VEHICLE_BOATTRAILER; break;
		case 7: spawnloop = VEHICLE_CADDY; break;
		case 8: spawnloop = VEHICLE_CADDY2; break;
		case 9: spawnloop = VEHICLE_DOCKTRAILER; break;
		case 10: spawnloop = VEHICLE_DOCKTUG; break;
		case 11: spawnloop = VEHICLE_FORKLIFT; break;
		case 12: spawnloop = VEHICLE_FREIGHTTRAILER; break;
		case 13: spawnloop = VEHICLE_GRAINTRAILER; break;
		case 14: spawnloop = VEHICLE_MOWER; break;
		case 15: spawnloop = VEHICLE_PROPTRAILER; break;
		case 16: spawnloop = VEHICLE_RAKETRAILER; break;
		case 17: spawnloop = VEHICLE_RIPLEY; break;
		case 18: spawnloop = VEHICLE_SADLER; break;
		case 19: spawnloop = VEHICLE_SADLER2; break;
		case 20: spawnloop = VEHICLE_SCRAP; break;
		case 21: spawnloop = VEHICLE_TANKER; break;
		case 22: spawnloop = VEHICLE_TOWTRUCK; break;
		case 23: spawnloop = VEHICLE_TOWTRUCK2; break;
		case 24: spawnloop = VEHICLE_TR2; break;
		case 25: spawnloop = VEHICLE_TR3; break;
		case 26: spawnloop = VEHICLE_TR4; break;
		case 27: spawnloop = VEHICLE_TRACTOR; break;
		case 28: spawnloop = VEHICLE_TRACTOR2; break;
		case 29: spawnloop = VEHICLE_TRACTOR3; break;
		case 30: spawnloop = VEHICLE_TRAILERLOGS; break;
		case 31: spawnloop = VEHICLE_TRAILERS; break;
		case 32: spawnloop = VEHICLE_TRAILERS2; break;
		case 33: spawnloop = VEHICLE_TRAILERS3; break;
		case 34: spawnloop = VEHICLE_TRAILERSMALL; break;
		case 35: spawnloop = VEHICLE_TRFLAT; break;
		case 36: spawnloop = VEHICLE_TVTRAILER; break;
		case 37: spawnloop = VEHICLE_UTILLITRUCK; break;
		case 38: spawnloop = VEHICLE_UTILLITRUCK2; break;
		case 39: spawnloop = VEHICLE_UTILLITRUCK3; break;
		}
		break;
#pragma endregion
#pragma region Vans
	case Vanslist:
		addTitle("Vans");
		addOption("Bison");
		addOption("Bison2");
		addOption("Bison3");
		addOption("Bobcatxl");
		addOption("Boxville");
		addOption("Boxville2");
		addOption("Boxville3");
		addOption("Burrito");
		addOption("Burrito2");
		addOption("Burrito3");
		addOption("Burrito4");
		addOption("Burrito5");
		addOption("Camper");
		addOption("Gburrito");
		addOption("Journey");
		addOption("Minivan");
		addOption("Pony");
		addOption("Pony2");
		addOption("Rumpo");
		addOption("Rumpo2");
		addOption("Speedo");
		addOption("Speedo2");
		addOption("Surfer");
		addOption("Surfer2");
		addOption("Taco");
		addOption("Youga");
		addOption("Paradise");
		switch (getOption()) {
		case 1: spawnloop = VEHICLE_BISON; break;
		case 2: spawnloop = VEHICLE_BISON2; break;
		case 3: spawnloop = VEHICLE_BISON3; break;
		case 4: spawnloop = VEHICLE_BOBCATXL; break;
		case 5: spawnloop = VEHICLE_BOXVILLE; break;
		case 6: spawnloop = VEHICLE_BOXVILLE2; break;
		case 7: spawnloop = VEHICLE_BOXVILLE3; break;
		case 8: spawnloop = VEHICLE_BURRITO; break;
		case 9: spawnloop = VEHICLE_BURRITO2; break;
		case 10: spawnloop = VEHICLE_BURRITO3; break;
		case 11: spawnloop = VEHICLE_BURRITO4; break;
		case 12: spawnloop = VEHICLE_BURRITO5; break;
		case 13: spawnloop = VEHICLE_CAMPER; break;
		case 14: spawnloop = VEHICLE_GBURRITO; break;
		case 15: spawnloop = VEHICLE_JOURNEY; break;
		case 16: spawnloop = VEHICLE_MINIVAN; break;
		case 17: spawnloop = VEHICLE_PONY; break;
		case 18: spawnloop = VEHICLE_PONY2; break;
		case 19: spawnloop = VEHICLE_RUMPO; break;
		case 20: spawnloop = VEHICLE_RUMPO2; break;
		case 21: spawnloop = VEHICLE_SPEEDO; break;
		case 22: spawnloop = VEHICLE_SPEEDO2; break;
		case 23: spawnloop = VEHICLE_SURFER; break;
		case 24: spawnloop = VEHICLE_SURFER2; break;
		case 25: spawnloop = VEHICLE_TACO; break;
		case 26: spawnloop = VEHICLE_YOUGA; break;
		case 27: spawnloop = VEHICLE_PARADISE; break;
		}
		break;
#pragma endregion
#pragma region Service
	case ServiceVehicles:
		addTitle("Service");
		addOption("Airbus");
		addOption("Bus");
		addOption("Coach");
		addOption("Rentalbus");
		addOption("Taxi");
		addOption("Tourbus");
		addOption("Trash");
		switch (getOption()) {
		case 1: spawnloop = VEHICLE_AIRBUS; break;
		case 2: spawnloop = VEHICLE_BUS; break;
		case 3: spawnloop = VEHICLE_COACH; break;
		case 4: spawnloop = VEHICLE_RENTALBUS; break;
		case 5: spawnloop = VEHICLE_TAXI; break;
		case 6: spawnloop = VEHICLE_TOURBUS; break;
		case 7: spawnloop = VEHICLE_TRASH; break;
		}
		break;
#pragma endregion
#pragma region Emergency
	case EmergencyVehicles:
		addTitle("Emergency");
		addOption("Ambulance");
		addOption("FBI");
		addOption("FBI2");
		addOption("Firetruk");
		addOption("Lifeguard");
		addOption("Pbus");
		addOption("Police");
		addOption("Police2");
		addOption("Police3");
		addOption("Police4");
		addOption("Policeb");
		addOption("Policeold1");
		addOption("Policeold2");
		addOption("Policet");
		addOption("Pranger");
		addOption("Riot");
		addOption("Sheriff");
		addOption("Sheriff2");
		switch (getOption()) {
		case 1: spawnloop = VEHICLE_AMBULANCE; break;
		case 2: spawnloop = VEHICLE_FBI; break;
		case 3: spawnloop = VEHICLE_FBI2; break;
		case 4: spawnloop = VEHICLE_FIRETRUK; break;
		case 5: spawnloop = VEHICLE_LGUARD; break;
		case 6: spawnloop = VEHICLE_PBUS; break;
		case 7: spawnloop = VEHICLE_POLICE; break;
		case 8: spawnloop = VEHICLE_POLICE2; break;
		case 9: spawnloop = VEHICLE_POLICE3; break;
		case 10: spawnloop = VEHICLE_POLICE4; break;
		case 11: spawnloop = VEHICLE_POLICEB; break;
		case 12: spawnloop = VEHICLE_POLICEOLD1; break;
		case 13: spawnloop = VEHICLE_POLICEOLD2; break;
		case 14: spawnloop = VEHICLE_POLICET; break;
		case 15: spawnloop = VEHICLE_PRANGER; break;
		case 16: spawnloop = VEHICLE_RIOT; break;
		case 17: spawnloop = VEHICLE_SHERIFF; break;
		case 18: spawnloop = VEHICLE_SHERIFF2; break;
		}
		break;
#pragma endregion
#pragma region Boats 
	case Boats:
		addTitle("Boats");
		addOption("Dinghy");
		addOption("Dinghy2");
		addOption("Jetmax");
		addOption("Marquis");
		addOption("Predator");
		addOption("Seashark");
		addOption("Seashark2");
		addOption("Squalo");
		addOption("Submersible");
		addOption("Suntrap");
		addOption("Tropic");
		addOption("Speeder");
		switch (getOption()) {
		case 1: spawnloop = VEHICLE_DINGHY; break;
		case 2: spawnloop = VEHICLE_DINGHY2; break;
		case 3: spawnloop = VEHICLE_JETMAX; break;
		case 4: spawnloop = VEHICLE_MARQUIS; break;
		case 5: spawnloop = VEHICLE_PREDATOR; break;
		case 6: spawnloop = VEHICLE_SEASHARK; break;
		case 7: spawnloop = VEHICLE_SEASHARK2; break;
		case 8: spawnloop = VEHICLE_SQUALO; break;
		case 9: spawnloop = VEHICLE_SUBMERSIBLE; break;
		case 10: spawnloop = VEHICLE_SUNTRAP; break;
		case 11: spawnloop = VEHICLE_TROPIC; break;
		case 12: spawnloop = VEHICLE_SPEEDER; break;
		}
		break;
#pragma endregion
#pragma region OffRoad
	case Offroad:
		addTitle("Off-Road");
		addOption("Bfinjection");
		addOption("Blazer");
		addOption("Blazer2");
		addOption("Blazer3");
		addOption("Bodhi2");
		addOption("Dloader");
		addOption("Dune");
		addOption("Dune2");
		addOption("Mesa3");
		addOption("Rancherxl");
		addOption("Rancherxl2");
		addOption("Rebel");
		addOption("Rebel2");
		addOption("Sandking");
		addOption("Sandking2");
		addOption("Bifta");
		addOption("Kalahari");
		switch (getOption()) {
		case 1: spawnloop = VEHICLE_BFINJECTION; break;
		case 2: spawnloop = VEHICLE_BLAZER; break;
		case 3: spawnloop = VEHICLE_BLAZER2; break;
		case 4: spawnloop = VEHICLE_BLAZER3; break;
		case 5: spawnloop = VEHICLE_BODHI2; break;
		case 6: spawnloop = VEHICLE_DLOADER; break;
		case 7: spawnloop = VEHICLE_DUNE; break;
		case 8: spawnloop = VEHICLE_DUNE2; break;
		case 9: spawnloop = VEHICLE_MESA3; break;
		case 10: spawnloop = VEHICLE_RANCHERXL; break;
		case 11: spawnloop = VEHICLE_RANCHERXL2; break;
		case 12: spawnloop = VEHICLE_REBEL; break;
		case 13: spawnloop = VEHICLE_REBEL2; break;
		case 14: spawnloop = VEHICLE_SANDKING; break;
		case 15: spawnloop = VEHICLE_SANDKING2; break;
		case 16: spawnloop = VEHICLE_BIFTA; break;
		case 17: spawnloop = VEHICLE_KALAHARI; break;
		}
		break;
#pragma endregion
#pragma region Sedans
	case Sedans:
		addTitle("Sedans");
		addOption("Asea");
		addOption("Asea2");
		addOption("Asterope");
		addOption("Emperor");
		addOption("Emperor2");
		addOption("Emperor3");
		addOption("Fugitive");
		addOption("Ingot");
		addOption("Intruder");
		addOption("Premier");
		addOption("Primo");
		addOption("Regina");
		addOption("Romero");
		addOption("Schafter2");
		addOption("Stanier");
		addOption("Stratum");
		addOption("Stretch");
		addOption("Superd");
		addOption("Surge");
		addOption("Tailgater");
		addOption("Washington");
		switch (getOption()) {
		case 1: spawnloop = VEHICLE_ASEA; break;
		case 2: spawnloop = VEHICLE_ASEA2; break;
		case 3: spawnloop = VEHICLE_ASTEROPE; break;
		case 4: spawnloop = VEHICLE_EMPEROR; break;
		case 5: spawnloop = VEHICLE_EMPEROR2; break;
		case 6: spawnloop = VEHICLE_EMPEROR3; break;
		case 7: spawnloop = VEHICLE_FUGITIVE; break;
		case 8: spawnloop = VEHICLE_INGOT; break;
		case 9: spawnloop = VEHICLE_INTRUDER; break;
		case 10: spawnloop = VEHICLE_PREMIER; break;
		case 11: spawnloop = VEHICLE_PRIMO; break;
		case 12: spawnloop = VEHICLE_REGINA; break;
		case 13: spawnloop = VEHICLE_ROMERO; break;
		case 14: spawnloop = VEHICLE_SCHAFTER2; break;
		case 15: spawnloop = VEHICLE_STANIER; break;
		case 16: spawnloop = VEHICLE_STRATUM; break;
		case 17: spawnloop = VEHICLE_STRETCH; break;
		case 18: spawnloop = VEHICLE_SUPERD; break;
		case 19: spawnloop = VEHICLE_SURGE; break;
		case 20: spawnloop = VEHICLE_TAILGATER; break;
		case 21: spawnloop = VEHICLE_WASHINGTON; break;
		}
		break;
#pragma endregion
#pragma region Motocycles
	case Motocycles:
		addTitle("Motorcycles");
		addOption("Akuma");
		addOption("Bagger");
		addOption("Bati");
		addOption("Bati2");
		addOption("Carbonrs");
		addOption("Daemon");
		addOption("Double");
		addOption("Faggio2");
		addOption("Hexer");
		addOption("Nemesis");
		addOption("Pcj");
		addOption("Ruffian");
		addOption("Sanchez");
		addOption("Sanchez2");
		addOption("Vader");
		switch (getOption()) {
		case 1: spawnloop = VEHICLE_AKUMA; break;
		case 2: spawnloop = VEHICLE_BAGGER; break;
		case 3: spawnloop = VEHICLE_BATI; break;
		case 4: spawnloop = VEHICLE_BATI2; break;
		case 5: spawnloop = VEHICLE_CARBONRS; break;
		case 6: spawnloop = VEHICLE_DAEMON; break;
		case 7: spawnloop = VEHICLE_DOUBLE; break;
		case 8: spawnloop = VEHICLE_FAGGIO2; break;
		case 9: spawnloop = VEHICLE_HEXER; break;
		case 10: spawnloop = VEHICLE_NEMESIS; break;
		case 11: spawnloop = VEHICLE_PCJ; break;
		case 12: spawnloop = VEHICLE_RUFFIAN; break;
		case 13: spawnloop = VEHICLE_SANCHEZ; break;
		case 14: spawnloop = VEHICLE_SANCHEZ2; break;
		case 15: spawnloop = VEHICLE_VADER; break;
		}
		break;
#pragma endregion
#pragma region Planes
	case Planes_menu:
		addTitle("Planes");
		addOption("Blimp");
		addOption("Cargoplane");
		addOption("Cuban800");
		addOption("Duster");
		addOption("Jet");
		addOption("Lazer");
		addOption("Luxor");
		addOption("Mammatus");
		addOption("Shamal");
		addOption("Stunt");
		addOption("Titan");
		addOption("Velum");
		addOption("Vestra");
		switch (getOption()) {
		case 1: spawnloop = VEHICLE_BLIMP; break;
		case 2: spawnloop = VEHICLE_CARGOPLANE; break;
		case 3: spawnloop = VEHICLE_CUBAN800; break;
		case 4: spawnloop = VEHICLE_DUSTER; break;
		case 5: spawnloop = VEHICLE_JET; break;
		case 6: spawnloop = VEHICLE_LAZER; break;
		case 7: spawnloop = VEHICLE_LUXOR; break;
		case 8: spawnloop = VEHICLE_MAMMATUS; break;
		case 9: spawnloop = VEHICLE_SHAMAL; break;
		case 10: spawnloop = VEHICLE_STUNT; break;
		case 11: spawnloop = VEHICLE_TITAN; break;
		case 12: spawnloop = VEHICLE_VELUM; break;
		case 13: spawnloop = VEHICLE_VESTRA; break;
		}
		break;
#pragma endregion
#pragma region Muscle
	case MuscleCars:
		addTitle("Muscle");
		addOption("Buccaneer");
		addOption("Dominator");
		addOption("Gauntlet");
		addOption("Hotknife");
		addOption("Phoenix");
		addOption("Picador");
		addOption("Ratloader");
		addOption("Ruiner");
		addOption("Sabregt");
		addOption("Vigero");
		addOption("Voodoo2");
		addOption("Ratloader2");
		addOption("Slamvan");
		switch (getOption()) {
		case 1: spawnloop = VEHICLE_BUCCANEER; break;
		case 2: spawnloop = VEHICLE_DOMINATOR; break;
		case 3: spawnloop = VEHICLE_GAUNTLET; break;
		case 4: spawnloop = VEHICLE_HOTKNIFE; break;
		case 5: spawnloop = VEHICLE_PHOENIX; break;
		case 6: spawnloop = VEHICLE_PICADOR; break;
		case 7: spawnloop = VEHICLE_RATLOADER; break;
		case 8: spawnloop = VEHICLE_RUINER; break;
		case 9: spawnloop = VEHICLE_SABREGT; break;
		case 10: spawnloop = VEHICLE_VIGERO; break;
		case 11: spawnloop = VEHICLE_VOODOO2; break;
		}
		break;
#pragma endregion
#pragma region SUVs
	case SUV_menu:
		addTitle("SUVs");
		addOption("Baller");
		addOption("Baller2");
		addOption("Bjxl");
		addOption("Cavalcade");
		addOption("Cavalcade2");
		addOption("Dubsta");
		addOption("Dubsta2");
		addOption("Fq2");
		addOption("Granger");
		addOption("Gresley");
		addOption("Habanero");
		addOption("Landstalker");
		addOption("Mesa");
		addOption("Mesa2");
		addOption("Patriot");
		addOption("Radi");
		addOption("Rocoto");
		addOption("Seminole");
		addOption("Serrano");
		switch (getOption()) {
		case 1: spawnloop = VEHICLE_BALLER; break;
		case 2: spawnloop = VEHICLE_BALLER2; break;
		case 3: spawnloop = VEHICLE_BJXL; break;
		case 4: spawnloop = VEHICLE_CAVALCADE; break;
		case 5: spawnloop = VEHICLE_CAVALCADE2; break;
		case 6: spawnloop = VEHICLE_DUBSTA; break;
		case 7: spawnloop = VEHICLE_DUBSTA2; break;
		case 8: spawnloop = VEHICLE_FQ2; break;
		case 9: spawnloop = VEHICLE_GRANGER; break;
		case 10: spawnloop = VEHICLE_GRESLEY; break;
		case 11: spawnloop = VEHICLE_HABANERO; break;
		case 12: spawnloop = VEHICLE_LANDSTALKER; break;
		case 13: spawnloop = VEHICLE_MESA; break;
		case 14: spawnloop = VEHICLE_MESA2; break;
		case 15: spawnloop = VEHICLE_PATRIOT; break;
		case 16: spawnloop = VEHICLE_RADI; break;
		case 17: spawnloop = VEHICLE_ROCOTO; break;
		case 18: spawnloop = VEHICLE_SEMINOLE; break;
		case 19: spawnloop = VEHICLE_SERRANO; break;
		}
		break;
#pragma endregion
#pragma region Militery
	case MilitaryVeh_menu:
		addTitle("Military");
		addOption("Barracks");
		addOption("Barracks2");
		addOption("Crusader");
		addOption("Rhino");
		switch (getOption()) {
		case 1: spawnloop = VEHICLE_BARRACKS; break;
		case 2: spawnloop = VEHICLE_BARRACKS2; break;
		case 3: spawnloop = VEHICLE_CRUSADER; break;
		case 4: spawnloop = VEHICLE_RHINO; break;
		}
		break;
#pragma endregion
#pragma region Helicopters
	case Helicopters_Menu:
		addTitle("Helicopters");
		addOption("Annihilator");
		addOption("Buzzard");
		addOption("Buzzard2");
		addOption("Cargobob");
		addOption("Cargobob2");
		addOption("Cargobob3");
		addOption("Frogger");
		addOption("Frogger2");
		addOption("Maverick");
		addOption("Polmav");
		addOption("Skylift");
		switch (getOption()) {
		case 1: spawnloop = VEHICLE_ANNIHILATOR; break;
		case 2: spawnloop = VEHICLE_BUZZARD; break;
		case 3: spawnloop = VEHICLE_BUZZARD2; break;
		case 4: spawnloop = VEHICLE_CARGOBOB; break;
		case 5: spawnloop = VEHICLE_CARGOBOB2; break;
		case 6: spawnloop = VEHICLE_CARGOBOB3; break;
		case 7: spawnloop = VEHICLE_FROGGER; break;
		case 8: spawnloop = VEHICLE_FROGGER2; break;
		case 9: spawnloop = VEHICLE_MAVERICK; break;
		case 10: spawnloop = VEHICLE_POLMAV; break;
		case 11: spawnloop = VEHICLE_SKYLIFT; break;
		}
		break;
#pragma endregion
#pragma region Commercial
	case CommercialVeh_menu:
		addTitle("Commercial");
		addOption("Benson");
		addOption("Biff");
		addOption("Hauler");
		addOption("Mule");
		addOption("Mule2");
		addOption("Packer");
		addOption("Phantom");
		addOption("Pounder");
		addOption("Stockade");
		addOption("Stockade3");
		switch (getOption()) {
		case 1: spawnloop = VEHICLE_BENSON; break;
		case 2: spawnloop = VEHICLE_BIFF; break;
		case 3: spawnloop = VEHICLE_HAULER; break;
		case 4: spawnloop = VEHICLE_MULE; break;
		case 5: spawnloop = VEHICLE_MULE2; break;
		case 6: spawnloop = VEHICLE_PACKER; break;
		case 7: spawnloop = VEHICLE_PHANTOM; break;
		case 8: spawnloop = VEHICLE_POUNDER; break;
		case 9: spawnloop = VEHICLE_STOCKADE; break;
		case 10: spawnloop = VEHICLE_STOCKADE3; break;
		}
		break;
#pragma endregion
#pragma region Compacts
	case CompactsVeh_menu:
		addOption("Blista");
		addOption("Dilettante");
		addOption("Dilettante2");
		addOption("Issi2");
		addOption("Prairie");
		switch (getOption()) {
		case 1: spawnloop = VEHICLE_BLISTA; break;
		case 2: spawnloop = VEHICLE_DILETTANTE; break;
		case 3: spawnloop = VEHICLE_DILETTANTE2; break;
		case 4: spawnloop = VEHICLE_ISSI2; break;
		case 5: spawnloop = VEHICLE_PRAIRIE; break;
		}
		break;
#pragma endregion
#pragma region Cycles
	case CyclesVeh_menu:
		addTitle("Cycles");
		addOption("BMX");
		addOption("Cruiser");
		addOption("Fixter");
		addOption("Scorcher");
		addOption("Tribike");
		addOption("Tribike2");
		addOption("Tribike3");
		switch (getOption()) {
		case 1: spawnloop = VEHICLE_BMX; break;
		case 2: spawnloop = VEHICLE_CRUISER; break;
		case 3: spawnloop = VEHICLE_FIXTER; break;
		case 4: spawnloop = VEHICLE_SCORCHER; break;
		case 5: spawnloop = VEHICLE_TRIBIKE; break;
		case 6: spawnloop = VEHICLE_TRIBIKE2; break;
		case 7: spawnloop = VEHICLE_TRIBIKE3; break;
		}
		break;
#pragma endregion
#pragma region Industrial
	case Industrialveh_menu:
		addTitle("Industrial");
		addOption("Bulldozer");
		addOption("Cutter");
		addOption("Dump");
		addOption("Flatbed");
		addOption("Handler");
		addOption("Mixer");
		addOption("Mixer2");
		addOption("Rubble");
		addOption("Tiptruck");
		addOption("Tiptruck2");
		switch (getOption()) {
		case 1: spawnloop = VEHICLE_BULLDOZER; break;
		case 2: spawnloop = VEHICLE_CUTTER; break;
		case 3: spawnloop = VEHICLE_DUMP; break;
		case 4: spawnloop = VEHICLE_FLATBED; break;
		case 5: spawnloop = VEHICLE_HANDLER; break;
		case 6: spawnloop = VEHICLE_MIXER; break;
		case 7: spawnloop = VEHICLE_MIXER2; break;
		case 8: spawnloop = VEHICLE_RUBBLE; break;
		case 9: spawnloop = VEHICLE_TIPTRUCK; break;
		case 10: spawnloop = VEHICLE_TIPTRUCK2; break;
		}
		break;
#pragma endregion
#pragma region Coupes
	case CoupesVeh_menu:
		addTitle("Coupes");
		addOption("Cogcabrio");
		addOption("Exemplar");
		addOption("F620");
		addOption("Felon");
		addOption("Felon2");
		addOption("Jackal");
		addOption("Oracle");
		addOption("Oracle2");
		addOption("Sentinel");
		addOption("Sentinel2");
		addOption("Zion");
		addOption("Zion2");
		switch (getOption()) {
		case 1: spawnloop = VEHICLE_COGCABRIO; break;
		case 2: spawnloop = VEHICLE_EXEMPLAR; break;
		case 3: spawnloop = VEHICLE_F620; break;
		case 4: spawnloop = VEHICLE_FELON; break;
		case 5: spawnloop = VEHICLE_FELON2; break;
		case 6: spawnloop = VEHICLE_JACKAL; break;
		case 7: spawnloop = VEHICLE_ORACLE; break;
		case 8: spawnloop = VEHICLE_ORACLE2; break;
		case 9: spawnloop = VEHICLE_SENTINEL; break;
		case 10: spawnloop = VEHICLE_SENTINEL2; break;
		case 11: spawnloop = VEHICLE_ZION; break;
		case 12: spawnloop = VEHICLE_ZION2; break;
		}
		break;
#pragma endregion
#pragma region Trains
	case TrainsVeh_menu:
		addTitle("Trains");
		addOption("Cablecar");
		addOption("Freight");
		addOption("Freightcar");
		addOption("Freightcont1");
		addOption("Freightcont2");
		addOption("Freightgrain");
		addOption("Metrotrain");
		addOption("Tankercar");
		switch (getOption())
		{
		case 1: spawnloop = VEHICLE_CABLECAR; break;
		case 2: spawnloop = VEHICLE_FREIGHT; break;
		case 3: spawnloop = VEHICLE_FREIGHTCAR; break;
		case 4: spawnloop = VEHICLE_FREIGHTCONT1; break;
		case 5: spawnloop = VEHICLE_FREIGHTCONT2; break;
		case 6: spawnloop = VEHICLE_FREIGHTGRAIN; break;
		case 7: spawnloop = VEHICLE_METROTRAIN; break;
		case 8: spawnloop = VEHICLE_TANKERCAR; break;
		}
		break;
#pragma endregion
#pragma endregion
#pragma region Weapons
	case Weapon_Menu:
		addTitle("Weapons");
		addOption("Give All Weapons");
		addOption("Remove Weapons");
		addBoolOption("Unlimited Ammo", &UnlimitedAmmo);
		addBoolOption("Explosive Ammo", &ExplosiveWeapon);
		addBoolOption("Burst Wispon", &BurstWispon);
		addBoolOption("Super Punch", &SuperPunch);
		addBoolOption("Teleport Gun", &TeleportGun);
		switch (getOption()) {
#pragma region Give Weapons
		case 1:
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), WEAPON_PISTOL, 100000, false, false);
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), WEAPON_COMBATPISTOL, 100000, false, false);
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), WEAPON_PISTOL50, 100000, false, false);
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), WEAPON_SNSPISTOL, 10000, false, false);
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), WEAPON_HEAVYPISTOL, 10000, false, false);
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), WEAPON_VINTAGEPISTOL, 10000, false, false);
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), WEAPON_MARKSMANPISTOL, 10000, false, false);
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), WEAPON_APPISTOL, 10000, false, false);
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), WEAPON_STUNGUN, 10000, false, false);
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), WEAPON_MICROSMG, 10000, false, false);
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), WEAPON_SMG, 10000, false, false);
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), WEAPON_ASSAULTSMG, 10000, false, false);
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), WEAPON_COMBATPDW, 10000, false, false);
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), WEAPON_MG, 10000, false, false);
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), WEAPON_COMBATMG, 10000, false, false);
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), WEAPON_GUSENBERG, 10000, false, false);
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), WEAPON_ASSAULTRIFLE, 10000, false, false);
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), WEAPON_CARBINERIFLE, 10000, false, false);
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), WEAPON_ADVANCEDRIFLE, 10000, false, false);
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), WEAPON_SPECIALCARBINE, 10000, false, false);
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), WEAPON_BULLPUPRIFLE, 10000, false, false);
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), WEAPON_SNIPERRIFLE, 10000, false, false);
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), WEAPON_HEAVYSNIPER, 10000, false, false);
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), WEAPON_MARKSMANRIFLE, 10000, false, false);
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), WEAPON_KNIFE, 10000, false, false);
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), WEAPON_NIGHTSTICK, 10000, false, false);
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), WEAPON_HAMMER, 10000, false, false);
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), WEAPON_BAT, 10000, false, false);
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), WEAPON_CROWBAR, 10000, false, false);
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), WEAPON_GOLFCLUB, 10000, false, false);
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), WEAPON_BOTTLE, 10000, false, false);
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), WEAPON_DAGGER, 10000, false, false);
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), WEAPON_KNUCKLE, 10000, false, false);
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), WEAPON_PUMPSHOTGUN, 10000, false, false);
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), WEAPON_SAWNOFFSHOTGUN, 10000, false, false);
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), WEAPON_BULLPUPSHOTGUN, 10000, false, false);
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), WEAPON_ASSAULTSHOTGUN, 10000, false, false);
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), WEAPON_MUSKET, 10000, false, false);
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), WEAPON_HEAVYSHOTGUN, 10000, false, false);
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), WEAPON_GRENADELAUNCHER, 10000, false, false);
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), WEAPON_RPG, 10000, false, false);
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), WEAPON_MINIGUN, 10000, false, false);
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), WEAPON_FIREWORK, 10000, false, false);
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), WEAPON_HOMINGLAUNCHER, 10000, false, false);
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), WEAPON_GRENADE, 10000, false, false);
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), WEAPON_STICKYBOMB, 10000, false, false);
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), WEAPON_PROXMINE, 10000, false, false);
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), WEAPON_SMOKEGRENADE, 10000, false, false);
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), WEAPON_BZGAS, 10000, false, false);
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), WEAPON_MOLOTOV, 10000, false, false);
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), WEAPON_FIREEXTINGUISHER, 10000, false, false);
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), WEAPON_PETROLCAN, 10000, false, false);
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), WEAPON_BALL, 10000, false, false);
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), WEAPON_SNOWBALL, 10000, false, false);
			break;
#pragma endregion
		case 2: WEAPON::REMOVE_ALL_PED_WEAPONS(PLAYER::PLAYER_PED_ID(), false); break;
		}
		break;
#pragma endregion
#pragma region Teleport
	case TeleportMenu:
		addTitle("Teleport");
		addSubtitle("Chaos Control");
		addSubmenuOption("Shops", TeleportShopMenu);
		addSubmenuOption("Common Locations", CommonTeleport);
		addSubmenuOption("IPL Loader", IPLLoadMenu);
		addOption("Teleport Forward");
		addOption("Teleport Up");
		switch (getOption())
		{
		case 4: 
			Vector3 tpcoord = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0, 5.0, 0.0);
			tpcoord.x += 5;
			Boxuga::teleportcharacter(tpcoord);
			break;
		case 5:
			Vector3 ZpCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
			ZpCoords.z += 5;
			Boxuga::teleportcharacter(ZpCoords);
			break;
		}
		break;
	case TeleportShopMenu:
		addTitle("Shops");
		addSubtitle("Buy some stuff with those rings");
		addOption("Vanila Unicorn (Shoe Store :))");
		addOption("Ammunation - Sandy Shores");
		addOption("Ammunation - Hawick");
		addOption("Ammunation - La Mesa");
		addOption("Ammunation - Paleto Bay");
		addOption("Ammunation - Little Seoul");
		addOption("Ammunation - Chaparral");
		addOption("Ammunation - Chumash");
		addOption("Ammunation - Mountains");
		addOption("Discount Store - Strawberry");
		addOption("Discount Store - Senora Desert");
		addOption("Discount Store - Grapeseed");
		addOption("Discount Store - Chapparral");
		addOption("Discount Store - Paleto Bay");
		addOption("Binco - Vespucci Canals");
		addOption("Binco - Textile City");
		addOption("Ponsonbys - Rockford Hills");
		addOption("Ponsonbys - Morningwood");
		addOption("Ponsonbys - Burton");
		addOption("Suburban - Del Perro");
		addOption("Suburban - Harmony");
		addOption("Suburban - Hawick");
		addOption("Suburban - Chumash");
		addOption("LS Customs - Airport");
		addOption("LS Customs - La Mesa");
		addOption("LS Customs - Burton");
		addOption("LS Customs - Senora Desert");
		addOption("Beeker's Garage");
		switch (getOption())
		{
		case 1: Boxuga::teleportcharacter(toVector3(106, -1331, 29)); break;
		case 2: Boxuga::teleportcharacter(toVector3(1707, 3743, 33)); break;
		case 3: Boxuga::teleportcharacter(toVector3(240, -46, 69)); break;
		case 4: Boxuga::teleportcharacter(toVector3(843, -1021, 27)); break;
		case 5: Boxuga::teleportcharacter(toVector3(-321, 6073, 31)); break;
		case 6: Boxuga::teleportcharacter(toVector3(-1317, -389, 36)); break;
		case 7: Boxuga::teleportcharacter(toVector3(-1109, 2685, 18)); break;
		case 8: Boxuga::teleportcharacter(toVector3(-3156, 1083, 20)); break;
		case 9: Boxuga::teleportcharacter(toVector3(2570, 307, 108)); break;
		case 10: Boxuga::teleportcharacter(toVector3(84, -1393, 29)); break;
		case 11: Boxuga::teleportcharacter(toVector3(1193, 2694, 37)); break;
		case 12: Boxuga::teleportcharacter(toVector3(1679, 4820, 41)); break;
		case 13: Boxuga::teleportcharacter(toVector3(-1090, 2700, 19)); break;
		case 14: Boxuga::teleportcharacter(toVector3(-2, 6521, 31)); break;
		case 15: Boxuga::teleportcharacter(toVector3(84, -1393, 29)); break;
		case 16: Boxuga::teleportcharacter(toVector3(413, -812, 29)); break;
		case 17: Boxuga::teleportcharacter(toVector3(-719, -160, 37)); break;
		case 18: Boxuga::teleportcharacter(toVector3(-1458, -230, 49)); break;
		case 19: Boxuga::teleportcharacter(toVector3(-150, -304, 39)); break;
		case 20: Boxuga::teleportcharacter(toVector3(-1210, -784, 17)); break;
		case 21: Boxuga::teleportcharacter(toVector3(620, 2744, 42)); break; // harmony
		case 22: Boxuga::teleportcharacter(toVector3(132, -201, 54)); break;
		case 23: Boxuga::teleportcharacter(toVector3(-3163, 1065, 20)); break;
		case 24: Boxuga::teleportcharacter(toVector3(-1130, -1987, 13)); break; //ls airport
		case 25: Boxuga::teleportcharacter(toVector3(715, -1089, 22)); break;
		case 26: Boxuga::teleportcharacter(toVector3(-366, -132, 38)); break;
		case 27: Boxuga::teleportcharacter(toVector3(1177, 2659, 38)); break;
		case 28: Boxuga::teleportcharacter(toVector3(123, 6610, 31)); break;
		}
		break;
	case CommonTeleport:
		addTitle("Common Places");
		addSubtitle("just teleport");
		addOption("Mount Chilliad");
		addOption("LS Airport");
		addOption("Sandy Shores Airstrip");
		addOption("Maze Bank");
		addOption("LS Pier");
		addOption("Vinehood Sign");
		addOption("Sonic Reference");
		switch (getOption())
		{
		case 1: Boxuga::teleportcharacter(toVector3(494, 5589, 795)); break;
		case 2: Boxuga::teleportcharacter(toVector3(-989, -2905, 14)); break;
		case 3: Boxuga::teleportcharacter(toVector3(1721, 3259, 41)); break;
		case 4: Boxuga::teleportcharacter(toVector3(-72, -820, 327)); break;
		case 5: Boxuga::teleportcharacter(toVector3(-1650, -1092, 13)); break;
		case 6: Boxuga::teleportcharacter(toVector3(704, 1206, 325)); break;
		case 7: Boxuga::teleportcharacter(toVector3(310, -955, 30)); break;
		}
		break;
#pragma endregion
#pragma region Misc
	case MiscMenu:
		addTitle("Misc.");
		addSubmenuOption("Spoofing", Patch_natives_menu);
		addSubmenuOption("Radio", RadioMenu);
		addSubmenuOption("Time", Time_menu);
		addSubmenuOption("Weather", Weather_menu);
		//addSubmenuOption("Draw", DrawingMenu);
		addBoolOption("Display Coords", &XYZDisplay);
		addBoolOption("Riot Mode", &riotmode);
		addBoolOption("Creator Mode/Tutorial", &CreatorMode, "Goto Online from Creator to use Tutorial"); // with this you can also glitch in to tutorial - load into tutorial then 
		addOption("Autosave");
		//addKeyboardOption("Load UGC", UGCload, "", 40);
		switch (getOption())
		{
		case 7: 
			if (riotmode)
				GAMEPLAY::SET_RIOT_MODE_ENABLED(true);
			else
				GAMEPLAY::SET_RIOT_MODE_ENABLED(false);
			break;
		case 8:  
			if (CreatorMode)
			{ // Alot of these are probaly not all required
				gopro2027::patchNative(0xC7FF5AFC, (int)gopro2027::native_ret1_hook); // trying IS_CLOUD
				gopro2027::patchNative(0x9B9AFFF1, (int)gopro2027::native_ret1_hook); // Cloud Succeed
				gopro2027::patchNative(0x358D1D77, (int)gopro2027::native_ret1_hook); // Bypass game downloading Social Club Policies
				gopro2027::patchNative(0x66EC713F, (int)gopro2027::native_ret1_hook); // Makes game think user has Social Club Accou
				gopro2027::patchNative(0xC6EA802E, (int)gopro2027::native_ret1_hook); // Make game think it can Write to Leadboards
				gopro2027::patchNative(0x0CA1167F, (int)gopro2027::native_ret1_hook); // Private DM privladge
				gopro2027::patchNative(0x424C6E27, (int)gopro2027::native_ret1_hook); // Has Social Club perms
				gopro2027::patchNative(0x3FB40673, (int)gopro2027::native_ret1_hook); // Makes the game think that the user has Signed into R* and has a valid account
				gopro2027::patchNative(0x9262744C, (int)gopro2027::native_ret1_hook); // Makes game think all requests have succeded
				//gopro2027::patchNative(0xADD0B40F, (int)gopro2027::native_ret1_hook); // NETWORK_IS_SIGNED_IN
			}
			else
			{
				gopro2027::patchNative(0xC7FF5AFC, (int)gopro2027::native_ret0_hook);
				gopro2027::patchNative(0x9B9AFFF1, (int)gopro2027::native_ret0_hook);
				gopro2027::patchNative(0x358D1D77, (int)gopro2027::native_ret0_hook);
				gopro2027::patchNative(0x66EC713F, (int)gopro2027::native_ret0_hook);
				gopro2027::patchNative(0xC6EA802E, (int)gopro2027::native_ret0_hook);
				gopro2027::patchNative(0x0CA1167F, (int)gopro2027::native_ret0_hook);
				gopro2027::patchNative(0x424C6E27, (int)gopro2027::native_ret0_hook);
				gopro2027::patchNative(0x3FB40673, (int)gopro2027::native_ret0_hook);
				gopro2027::patchNative(0x9262744C, (int)gopro2027::native_ret0_hook);
				//gopro2027::patchNative(0xADD0B40F, (int)gopro2027::native_ret0_hook); 
			}
			break;
		case 9: GAMEPLAY::DO_AUTO_SAVE(); break;
		}
		break;
	case DrawingMenu:
		addTitle("Draw");
		addSubmenuOption("Text", DrawTextMenu);
		addSubmenuOption("Rect", DrawBoxMenu);
		break;
	case DrawTextMenu:
		addTitle("Draw Text");
		addBoolOption("Enable", &DebugText);
		addFloatOption("X Coord", &DebugTextX, 0.0, 10.0, true);
		addFloatOption("Y Coord", &DebugTextY, 0.0, 10.0, true);
		addFloatOption("X Scale", &DebugTextScaleX, 0.0, 10.0, true);
		addFloatOption("Y Scale", &DebugTextScaleY, 0.0, 10.0, true);
		addBoolOption("Centre", &debugtextcentre);
		addKeyboardOption("Text", 4, "Hello World", 64);
		break;
	case DrawBoxMenu:
		addTitle("Rect");
		addOption("Enable");
		break;
	case RadioMenu:
		addTitle("Radio");
		addBoolOption("Mobile Radio", &MobileRadio);
		addOption("Skip Radio");
		switch (getOption())
		{
		case 2: AUDIO::SKIP_RADIO_FORWARD(); break;
		}
		break;
	case IPLLoadMenu:
		addTitle("IPL Loader");
		addBoolOption("North Yankton", &NorthYanktonIPLLoad);
		addBoolOption("Yacht", &YachtIPLLoad);
		addBoolOption("FIB Lobby", &FIBLobbyIPL);
		addBoolOption("Morgue", &MorgueIPL);
		switch (getOption())
		{
		case 1: 
			if (NorthYanktonIPLLoad)
			{
				STREAMING::REQUEST_IPL("prologue01");
				STREAMING::REQUEST_IPL("prologue01c");
				STREAMING::REQUEST_IPL("prologue01d");
				STREAMING::REQUEST_IPL("prologue01e");
				STREAMING::REQUEST_IPL("prologue01f");
				STREAMING::REQUEST_IPL("prologue01g");
				STREAMING::REQUEST_IPL("prologue01h");
				STREAMING::REQUEST_IPL("prologue01i");
				STREAMING::REQUEST_IPL("prologue01j");
				STREAMING::REQUEST_IPL("prologue01k");
				STREAMING::REQUEST_IPL("prologue01z");
				STREAMING::REQUEST_IPL("prologue02");
				STREAMING::REQUEST_IPL("prologue03");
				STREAMING::REQUEST_IPL("prologue03_grv_cov");
				STREAMING::REQUEST_IPL("prologue03_grv_dug");
				STREAMING::REQUEST_IPL("prologue03_grv_fun");
				STREAMING::REQUEST_IPL("prologue03b");
				STREAMING::REQUEST_IPL("prologue_grv_torch");
				STREAMING::REQUEST_IPL("prologue04");
				STREAMING::REQUEST_IPL("prologue04_cover");
				STREAMING::REQUEST_IPL("prologue05");
				STREAMING::REQUEST_IPL("prologue05b");
				STREAMING::REQUEST_IPL("prologue06");
				STREAMING::REQUEST_IPL("prologue06_int");
				STREAMING::REQUEST_IPL("prologue06_pannel");
				STREAMING::REQUEST_IPL("prologue06b");
				STREAMING::REQUEST_IPL("prologue_m2_door");
				STREAMING::REQUEST_IPL("prologuerd");
				STREAMING::REQUEST_IPL("prologuerdb");
				STREAMING::REQUEST_IPL("prologue_DistantLights");
				STREAMING::REQUEST_IPL("prologue_LODLights");
				Boxuga::teleportcharacter(toVector3(5435.95, -5117.60, 79));
			}
			else
			{
				STREAMING::REMOVE_IPL("prologue01");
				STREAMING::REMOVE_IPL("prologue01c");
				STREAMING::REMOVE_IPL("prologue01d");
				STREAMING::REMOVE_IPL("prologue01e");
				STREAMING::REMOVE_IPL("prologue01f");
				STREAMING::REMOVE_IPL("prologue01g");
				STREAMING::REMOVE_IPL("prologue01h");
				STREAMING::REMOVE_IPL("prologue01i");
				STREAMING::REMOVE_IPL("prologue01j");
				STREAMING::REMOVE_IPL("prologue01k");
				STREAMING::REMOVE_IPL("prologue01z");
				STREAMING::REMOVE_IPL("prologue02");
				STREAMING::REMOVE_IPL("prologue03");
				STREAMING::REMOVE_IPL("prologue03_grv_cov");
				STREAMING::REMOVE_IPL("prologue03_grv_dug");
				STREAMING::REMOVE_IPL("prologue03_grv_fun");
				STREAMING::REMOVE_IPL("prologue03b");
				STREAMING::REMOVE_IPL("prologue_grv_torch");
				STREAMING::REMOVE_IPL("prologue04");
				STREAMING::REMOVE_IPL("prologue04_cover");
				STREAMING::REMOVE_IPL("prologue05");
				STREAMING::REMOVE_IPL("prologue05b");
				STREAMING::REMOVE_IPL("prologue06");
				STREAMING::REMOVE_IPL("prologue06_int");
				STREAMING::REMOVE_IPL("prologue06_pannel");
				STREAMING::REMOVE_IPL("prologue06b");
				STREAMING::REMOVE_IPL("prologue_m2_door");
				STREAMING::REMOVE_IPL("prologuerd");
				STREAMING::REMOVE_IPL("prologuerdb");
				STREAMING::REMOVE_IPL("prologue_DistantLights");
				STREAMING::REMOVE_IPL("prologue_LODLights");
			}
			
			break;
		case 2: 
			if (YachtIPLLoad)
			{
				STREAMING::REQUEST_IPL("smboat");
				STREAMING::REQUEST_IPL("apa_smboat_lodlights");
				STREAMING::REQUEST_IPL("ba_sm_boat_window");
				Boxuga::teleportcharacter(toVector3(-2054.68, -1026.5, 15));
			}
			else
			{
				STREAMING::REMOVE_IPL("smboat");
				STREAMING::REMOVE_IPL("apa_smboat_lodlights");
				STREAMING::REMOVE_IPL("ba_sm_boat_window");
			}
			break;
		case 3: 
			if (FIBLobbyIPL)
			{
				Boxuga::teleportcharacter(toVector3(112, -751, 46)); // tp to lobby
				STREAMING::REQUEST_IPL("FIBlobby");
			}
			else
			{
				STREAMING::REMOVE_IPL("FIBlobby");
			}
			break;
		case 4: 
			if (MorgueIPL)
			{
				Boxuga::teleportcharacter(toVector3(291.7, -1349.14, 25));
				STREAMING::REQUEST_IPL("coronertrash");
				STREAMING::REQUEST_IPL("Coroner_Int_On");
			}
			else
			{
				STREAMING::REMOVE_IPL("coronertrash");
				STREAMING::REMOVE_IPL("Coroner_Int_On");
			}
			break;
		}
		break;
	case Weather_menu:
		addTitle("Weather");
		addSubtitle("Note: only you can see this");
		addOption("Sunny");
		addOption("Overcast");
		addOption("Clear");
		addOption("Kiwi Weather (Rain)");
		addOption("Foggy");
		addOption("Thunder");
		addOption("Light Snow");
		addOption("Blizzard");
		addOption("Clearing");
		addOption("Smoggy");
		switch (getOption())
		{
		case 1: Boxuga::SetWeather("EXTRASUNNY"); break;
		case 2: Boxuga::SetWeather("OVERCAST"); break;
		case 3: Boxuga::SetWeather("CLEAR"); break;
		case 4: Boxuga::SetWeather("RAIN"); break;
		case 5: Boxuga::SetWeather("FOGGY"); break;
		case 6: Boxuga::SetWeather("THUNDER"); break;
		case 7: Boxuga::SetWeather("SNOWLIGHT"); break;
		case 8: Boxuga::SetWeather("BLIZZARD"); break;
		case 9: Boxuga::SetWeather("CLEARING"); break;
		case 10: Boxuga::SetWeather("SMOG"); break;
		case 11: Boxuga::SetWeather("CLOUDS"); break;
		}
		break;
	case Patch_natives_menu:
		addTitle("Patch Natives");
		addSubtitle("test these with caution");
		addBoolOption("All DLC Present", &DLCPResentSPOOF);
		addBoolOption("Have Online Priviledges", &NetworkHaveOnlinePriviledges);
		addBoolOption("Facebook", &Facebookpatch); // Shows facebook notifications but doesn't really do anything
		addBoolOption("Tutorial Session", &TutorialSession);
		addBoolOption("Tutorial Session Pending", &TutoialPendingSession);
		addBoolOption("Check Compat Pack Config", &CheckCompatConfig);
		addBoolOption("Aussie Version", &AussieMode);
		addOption("Ban Me (restart to unban)");
		switch (getOption()) {
		case 1: 
			if (DLCPResentSPOOF)
			{
				gopro2027::patchNative(0x1F321943, (int)gopro2027::native_ret1_hook);
			}
			else
			{
				gopro2027::patchNative(0x1F321943, (int)gopro2027::native_ret0_hook);
			}
			break;
		case 2: 
			if (NetworkHaveOnlinePriviledges)
				gopro2027::patchNative(0xEF63BFDF, (int)gopro2027::native_ret1_hook);
			else
				gopro2027::patchNative(0xEF63BFDF, (int)gopro2027::native_ret0_hook);
			break;
		case 3: 
			if (Facebookpatch)
			{
				gopro2027::patchNative(0x429AEAB3, (int)gopro2027::native_ret1_hook);
				gopro2027::patchNative(0x11E8B5CD, (int)gopro2027::native_ret1_hook);
				gopro2027::patchNative(0x37A28C26, (int)gopro2027::native_ret1_hook);
			}
			else
			{
				gopro2027::patchNative(0x429AEAB3, (int)gopro2027::native_ret0_hook);
				gopro2027::patchNative(0x11E8B5CD, (int)gopro2027::native_ret0_hook);
				gopro2027::patchNative(0x37A28C26, (int)gopro2027::native_ret0_hook);
			}
			break;
		case 4: 
			if (TutorialSession)
				gopro2027::patchNative(0x34DD7B28, (int)gopro2027::native_ret1_hook);
			else
				gopro2027::patchNative(0x34DD7B28, (int)gopro2027::native_ret0_hook);
			break;
		case 5: 
			if (TutoialPendingSession)
				gopro2027::patchNative(0xA003C40B, (int)gopro2027::native_ret1_hook);
			else
				gopro2027::patchNative(0xA003C40B, (int)gopro2027::native_ret0_hook);
			break;
		case 6:
			if (CheckCompatConfig)
				gopro2027::patchNative(0xF79A97F5, (int)gopro2027::native_ret1_hook);
			else
				gopro2027::patchNative(0xF79A97F5, (int)gopro2027::native_ret0_hook);
			break;
		case 7:
			if (AussieMode)
			{
				gopro2027::patchNative(0x944BA1DC, (int)gopro2027::native_ret1_hook);
			}
			else
			{
				gopro2027::patchNative(0x944BA1DC, (int)gopro2027::native_ret0_hook);
			}
			break;
		case 8:
				gopro2027::patchNative(0xD3BBE42F, (int)gopro2027::native_ret1_hook);
				gopro2027::patchNative(0xBDBB5948, (int)gopro2027::native_ret1_hook);
				gopro2027::patchNative(0x97287D68, (int)gopro2027::native_ret1_hook);
				break;
		}
		break;
	case Time_menu:
		addTitle("Time");
		addSubtitle("This will not appear to others");
		addBoolOption("Sync Time with System", &SyncTime);
		addOption("Morning");
		addOption("Midday");
		addOption("Arvo (Afternoon)");
		addOption("Night");
		addOption("Midnight");
		addOption("+1 Hour");
		addOption("-1 Hour");
		switch (getOption())
		{
		case 2: NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(7, 0, 0); break;
		case 3: NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(12, 0, 0); break;
		case 4: NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(15, 0, 0); break;
		case 5: NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(20, 0, 0); break;
		case 6: NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(0, 0, 0); break;
		case 7: 
			int hour = TIME::GET_CLOCK_HOURS();
			if ((hour + 1) >= 23)
			{
				hour = 0;
			}
			else
			{
				hour = hour + 1;
			}
			NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(hour, 0, 0);
			break;
		case 8: 
			int hourminus = TIME::GET_CLOCK_HOURS();
			if ((hourminus - 1) <= 0)
			{
				hourminus = 23;
			}
			else
			{
				hourminus = hourminus - 1;
			}
			NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(hourminus, 0, 0);
			break;
		}
		break;
#pragma endregion
#if DeveloperMode
	case DevOptions:
		addTitle("Dev Stuff");
		addFloatOption("Debug Text X", &DebugTextX, 0.0f, 1.0f, true);
		addFloatOption("Debug Text Y", &DebugTextY, 0.0f, 1.0f, true);
		addFloatOption("Debug ScaleX", &DebugTextScaleX, 0.0f, 1.0f, false);
		addFloatOption("Debug ScaleY", &DebugTextScaleY, 0.0f, 1.0f, false);
		addBoolOption("Debug Text", &DebugText);
		addFloatOption("Flag Pos X", &flagcoordX, -1.0f, 1.0f, false);
		addFloatOption("Flag Pos Y", &flagcoordY, -1.0f, 1.0f, false);
		addFloatOption("Flag Scale X", &flagscaleX, 0.0f, 1.0f, false);
		addFloatOption("Flag Scale Y", &flagscaleY, 0.0f, 1.0f, false);
		addFloatOption("Flag O Scale X", &flagoutlinescaleX, 0.0f, 1.0f, false);
		addFloatOption("Flag O Scale Y", &flagoutlinescaleY, 0.0f, 1.0f, false);
		addFloatOption("DebugBox_ScaleX", &DEBUGBOX_SCALEX, -1, 1, true);
		addFloatOption("DebugBox_ScaleY", &DEBUGBOX_SCALEY, -1, 1, true);
		addFloatOption("DebugBoxX", &DEBUGBOX_X, -1, 1, true);
		addFloatOption("DebugBoxY", &DEBUGBOX_Y, -1, 1, true);

		break;
#endif
	}
	resetVars();
	return true;
}


void main_thread(uint64_t main)
{
	printf("[Hedgehog SPRX By Boxuga] Loaded \n");

	Startup(); 
	sleep(30000); //Wait until native table initialization
	
	
	/*
	if (CustomGTAText)
	{
		/* GTA Online 1.12 3ta*/
		//*(int*)0x11100A3 = 0x60000000;

		//*(char*)(0x311DF020 + strlen(GTAOTitle)) = 0;
		//strncpy((char*)0x311DF020, GTAOTitle, strlen(GTAOTitle)); // pause menu
		//*(char*)(0x311DF020 + strlen(GTAOTitle)) = 0;
		//strncpy((char*)0x31340636, GTAOTitle, strlen(GTAOTitle)); // gta online title in playerlist

		//*(char*)(0x311DF1E0 + strlen(Loading3TAO)) = 0;
		//strncpy((char*)0x311DF1E0, Loading3TAO, strlen(Loading3TAO));
		//*(char*)(0x312FBD7F + strlen(Loading3TAO)) = 0;
		//((char*)0x312FBD7F, Loading3TAO, strlen(Loading3TAO));

		//*(char*)(0x3137F28E + strlen(Leave3TAOnline)) = 0;
		//strncpy((char*)0x3137F28E, Leave3TAOnline, strlen(Leave3TAOnline));

		//*(char*)(0x31349E6B + strlen(RockstarError)) = 0;
		//strncpy((char*)0x31349E6B, RockstarError, strlen(RockstarError));

		

		//*(char*)(0x3133B969 + strlen(LoadingGTA5)) = 0;
		//strncpy((char*)0x3133B969, LoadingGTA5, strlen(LoadingGTA5)); // the problem with this is that it breaks the crews label in pause menu


		//*(char*)(0x313393D1 + strlen(InviteMessage)) = 0;
		//strncpy((char*)0x313393D1, InviteMessage, strlen(InviteMessage));
		
	//}
	
	//MAIN_HOOK_ADDRESS = gopro2027::getOPDOfNative(0x6E5BDCE2); // for goprohooking
	//TOC = *(int*)(MAIN_HOOK_ADDRESS + 0x4);

	//og_main_hook_data = *(uint64_t*)MAIN_HOOK_ADDRESS;
	//*(uint64_t*)MAIN_HOOK_ADDRESS = (uint64_t)((int)Hook);
	PatchInJump(0x003C1920, (int)Hook, false); //IS_PLAYER_ONLINE//
	// Randiums Anti-Freeze
	*(int*)0x421008 = 0x60000000;
	*(int*)0x3D3B84 = 0x60000000;
	*(int*)0x3DE52C = 0x60000000;

	// Antifreeze Host
	*(int*)0x1284AF8 = 0x60000000;
	*(int*)0x1284B5C = 0x60000000;
	*(int*)0x1284B6C = 0x60000000;
	*(int*)0x1284B7C = 0x60000000;

	// CrashPatch freeze fix by DontCry
	*(int*)0x0127554C = 0x60000000; 

	// Player Broadcast
	*(int*)0x00995820 = 0x60000000; 
	*(int*)0x00995824 = 0x60000000; 

	// DS4 SUPPORT
	*(int*)0xBC27F8 = 0x60000000; 
	gopro2027::goprostartup();
	AussieMode = GAMEPLAY::IS_AUSSIE_VERSION(); // gets if aussie version
	sys_ppu_thread_exit(0);
}

#include "FaZeModz/FazeModz.h";

sys_ppu_thread_t threadId = SYS_PPU_THREAD_ID_INVALID;
extern "C"
{
	int gtav_start(int argc, const char* argv[])
	{
		sys_ppu_thread_t ModMenuThreadID;
		sys_ppu_thread_t GameFreezeExitID;
		sys_ppu_thread_create(&ModMenuThreadID, main_thread, 0, 10, 0x10, 0, "Hedgehog SPRX");
		sys_ppu_thread_create(&GameFreezeExitID, GameFreezeExit, 0, 10, 0x01, 0, "Hedgehog SPRX - Game Crash Exit Thread"); // Credit to FaZeModz
		return 0;
	}

	int gtav_stop(int argc, const char* argv[])
	{
		*(uint64_t*)MAIN_HOOK_ADDRESS = og_main_hook_data;
		return CELL_OK;
	}
}

