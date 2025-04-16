#include "natives.h"
#include "consts32.h"
#include <string>

namespace Boxuga
{
	Object CreateObj(char* name, Vector3 coords)
	{
		//
		int myObjHash = GAMEPLAY::GET_HASH_KEY(name);
		if (STREAMING::IS_MODEL_IN_CDIMAGE(myObjHash) && STREAMING::IS_MODEL_VALID(myObjHash))
		{
			//
			if (!STREAMING::HAS_MODEL_LOADED(myObjHash))
			{
				STREAMING::REQUEST_MODEL(myObjHash);
			}
			
			if (STREAMING::HAS_MODEL_LOADED(myObjHash))
			{
				Object myObj = OBJECT::CREATE_OBJECT(myObjHash, coords.x, coords.y, coords.z, true, true, false);
				return myObj;
			}

			
		}
		return NULL;
	}

	void TeleporttoPlayer(int player)
	{
		Vector3 Coords = ENTITY::GET_ENTITY_COORDS(player, 1);
		ENTITY::SET_ENTITY_COORDS(player, Coords.x, Coords.y, Coords.z, false, false, false, true);
	}

	int VehicleSpawner(int Vhash, bool SpawninCar)
	{
		Vector3 playercoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
		if (STREAMING::IS_MODEL_IN_CDIMAGE(Vhash) && STREAMING::IS_MODEL_A_VEHICLE(Vhash))
		{
			STREAMING::REQUEST_MODEL(Vhash);
			if (STREAMING::HAS_MODEL_LOADED(Vhash))
			{
				int commodore = VEHICLE::CREATE_VEHICLE(Vhash, playercoords.x, playercoords.y, playercoords.z, 90.0, true, false);
				if (SpawninCar)
				{
					PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), commodore, -1);
				}
				return commodore;
			}
		}
		return NULL;
	}

	void ChangeModel(char* model)
	{
		int Modelhash = GAMEPLAY::GET_HASH_KEY(model);
		if (STREAMING::IS_MODEL_IN_CDIMAGE(Modelhash) && STREAMING::IS_MODEL_VALID(Modelhash))
		{
			STREAMING::REQUEST_MODEL(Modelhash);
			if (STREAMING::HAS_MODEL_LOADED(Modelhash))
			{
				PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), Modelhash);
			}
		}
	}


	void DrawSprite(char * Streamedtexture, char * textureName, float x, float y, float width, float height, float rotation, int r, int g, int b, int a)
	{
		GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(Streamedtexture, false);
		GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(Streamedtexture);
		GRAPHICS::DRAW_SPRITE(Streamedtexture, textureName, x, y, width, height, rotation, r, g, b, a);
	}

	void teleportcharacter(Vector3 coord)
	{
		if (PED::IS_PED_SITTING_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID()))
		{
			ENTITY::SET_ENTITY_COORDS(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), coord.x, coord.y, coord.z, false, false, false, true);
		}
		else
		{
			ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), coord.x, coord.y, coord.z, false, false, false, true);
		}
	}


	void PlayAnim(Ped player, char* animdir, char* anim)
	{
		STREAMING::REQUEST_ANIM_DICT(animdir); // loads the animation dictionary into memory
		if (STREAMING::HAS_ANIM_DICT_LOADED(animdir)) // checks if it's loaded
		{
			Vector3 playercoords = ENTITY::GET_ENTITY_COORDS(player, true); // gets player pos
			int id = NETWORK::NETWORK_CREATE_SYNCHRONISED_SCENE(playercoords.x, playercoords.y, playercoords.z, 0, 0, 0, 2, false, true, 1.0f, 0.0f, 1.0f);
			NETWORK::NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE(player, id, animdir, anim, 8.0f, -8.0f, 120, 0, 100.0f, false); 
			NETWORK::NETWORK_START_SYNCHRONISED_SCENE(id);
		}
	}

	void clientModel(char* modelname)
	{
		int model = GAMEPLAY::GET_HASH_KEY(modelname); // gets id from model string
		if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_VALID(model)) // checks if its valid and in the CDIMAGE
		{
			STREAMING::REQUEST_MODEL(model); // Loads model into memory
			if (STREAMING::HAS_MODEL_LOADED(model)) // checks if model exists in memory
			{
				PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), model); // Changes the model to the new one
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
			}
		}
	}

	Ped SummonPed(char* modelname, float x, float y, float z, bool Hostile, bool Despawn)
	{
		int hash = GAMEPLAY::GET_HASH_KEY(modelname);
		if (STREAMING::IS_MODEL_IN_CDIMAGE(hash) && STREAMING::IS_MODEL_VALID(hash))
		{
			STREAMING::REQUEST_MODEL(hash);
			if (STREAMING::HAS_MODEL_LOADED(hash))
			{
				Ped pedmodel = PED::CREATE_PED(21, hash, x, y, z, 0, true, true);
				if (Hostile)
				{
					AI::TASK_COMBAT_PED(pedmodel, PLAYER::PLAYER_PED_ID(), 0, 16);
					PED::REGISTER_TARGET(pedmodel, PLAYER::PLAYER_PED_ID());
					PED::SET_PED_CAN_SWITCH_WEAPON(pedmodel, true);
					PED::SET_PED_COMBAT_RANGE(pedmodel, 2);
					WEAPON::GIVE_WEAPON_TO_PED(pedmodel, WEAPON_KNUCKLE, 10, false, true);
					PED::SET_PED_AS_ENEMY(pedmodel, true); 
				}
				if (Despawn)
				{
					STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
				}
				return pedmodel;
			}
		}
		return 0;
	}

	void SetWeather(char* Weather)
	{
		GAMEPLAY::SET_OVERRIDE_WEATHER(Weather);
	}

	char* getHUDName(int selHUDColor)
	{
		if (selHUDColor == 0)
		{
			return "HUD_COLOUR_PURE_WHITE";
		}
		if (selHUDColor == 1)
		{
			return "HUD_COLOUR_WHITE";
		}
		if (selHUDColor == 2)
		{
			return "HUD_COLOUR_BLACK";
		}
		if (selHUDColor == 3)
		{
			return "HUD_COLOUR_GREY";
		}
		if (selHUDColor == 4)
		{
			return "HUD_COLOUR_GREYLIGHT";
		}
		if (selHUDColor == 5)
		{
			return "HUD_COLOUR_GREYDARK";
		}
		if (selHUDColor == 6)
		{
			return "HUD_COLOUR_RED";
		}
		if (selHUDColor == 7)
		{
			return "HUD_COLOUR_REDLIGHT";
		}
		if (selHUDColor == 8)
		{
			return "HUD_COLOUR_REDDARK";
		}
		if (selHUDColor == 9)
		{
			return "HUD_COLOUR_BLUE";
		}
		if (selHUDColor == 10)
		{
			return "HUD_COLOUR_BLUELIGHT";
		}
		if (selHUDColor == 11)
		{
			return "HUD_COLOUR_BLUEDARK";
		}
		if (selHUDColor == 12)
		{
			return "HUD_COLOUR_YELLOW";
		}
		if (selHUDColor == 13)
		{
			return "HUD_COLOUR_YELLOWLIGHT";
		}
		if (selHUDColor == 14)
		{
			return "HUD_COLOUR_YELLOWDARK";
		}
		if (selHUDColor == 15)
		{
			return "HUD_COLOUR_ORANGE";
		}
		if (selHUDColor == 16)
		{
			return "HUD_COLOUR_ORANGELIGHT";
		}
		if (selHUDColor == 17)
		{
			return "HUD_COLOUR_ORANGEDARK";
		}
		if (selHUDColor == 18)
		{
			return "HUD_COLOUR_GREEN";
		}
		if (selHUDColor == 19)
		{
			return "HUD_COLOUR_GREENLIGHT";
		}
		if (selHUDColor == 20)
		{
			return "HUD_COLOUR_GREENDARK";
		}
		if (selHUDColor == 21)
		{
			return "HUD_COLOUR_PURPLE";
		}
		if (selHUDColor == 22)
		{
			return "HUD_COLOUR_PURPLELIGHT";
		}
		if (selHUDColor == 23)
		{
			return "HUD_COLOUR_PURPLEDARK";
		}
		if (selHUDColor == 24)
		{
			return "HUD_COLOUR_PINK";
		}
		if (selHUDColor == 25)
		{
			return "HUD_COLOUR_RADAR_HEALTH";
		}
		if (selHUDColor == 26)
		{
			return "HUD_COLOUR_RADAR_ARMOUR";
		}
		if (selHUDColor == 27)
		{
			return "HUD_COLOUR_RADAR_DAMAGE";
		}
		if (selHUDColor == 28)
		{
			return "HUD_COLOUR_NET_PLAYER1";
		}
		if (selHUDColor == 29)
		{
			return "HUD_COLOUR_NET_PLAYER2";
		}
		if (selHUDColor == 30)
		{
			return "HUD_COLOUR_NET_PLAYER3";
		}
		if (selHUDColor == 31)
		{
			return "HUD_COLOUR_NET_PLAYER4";
		}
		if (selHUDColor == 32)
		{
			return "HUD_COLOUR_NET_PLAYER5";
		}
		if (selHUDColor == 33)
		{
			return "HUD_COLOUR_NET_PLAYER6";
		}
		if (selHUDColor == 34)
		{
			return "HUD_COLOUR_NET_PLAYER7";
		}
		if (selHUDColor == 35)
		{
			return "HUD_COLOUR_NET_PLAYER8";
		}
		if (selHUDColor == 36)
		{
			return "HUD_COLOUR_NET_PLAYER9";
		}
		if (selHUDColor == 37)
		{
			return "HUD_COLOUR_NET_PLAYER10";
		}
		if (selHUDColor == 38)
		{
			return "HUD_COLOUR_NET_PLAYER11";
		}
		if (selHUDColor == 39)
		{
			return "HUD_COLOUR_NET_PLAYER12";
		}
		if (selHUDColor == 40)
		{
			return "HUD_COLOUR_NET_PLAYER13";
		}
		if (selHUDColor == 41)
		{
			return "HUD_COLOUR_NET_PLAYER14";
		}
		if (selHUDColor == 42)
		{
			return "HUD_COLOUR_NET_PLAYER15";
		}
		if (selHUDColor == 43)
		{
			return "HUD_COLOUR_NET_PLAYER16";
		}
		if (selHUDColor == 44)
		{
			return "HUD_COLOUR_NET_PLAYER17";
		}
		if (selHUDColor == 45)
		{
			return "HUD_COLOUR_NET_PLAYER18";
		}
		if (selHUDColor == 46)
		{
			return "HUD_COLOUR_NET_PLAYER19";
		}
		if (selHUDColor == 47)
		{
			return "HUD_COLOUR_NET_PLAYER20";
		}
		if (selHUDColor == 48)
		{
			return "HUD_COLOUR_NET_PLAYER21";
		}
		if (selHUDColor == 49)
		{
			return "HUD_COLOUR_NET_PLAYER22";
		}
		if (selHUDColor == 50)
		{
			return "HUD_COLOUR_NET_PLAYER23";
		}
		if (selHUDColor == 51)
		{
			return "HUD_COLOUR_NET_PLAYER24";
		}
		if (selHUDColor == 52)
		{
			return "HUD_COLOUR_NET_PLAYER25";
		}
		if (selHUDColor == 53)
		{
			return "HUD_COLOUR_NET_PLAYER26";
		}
		if (selHUDColor == 54)
		{
			return "HUD_COLOUR_NET_PLAYER27";
		}
		if (selHUDColor == 55)
		{
			return "HUD_COLOUR_NET_PLAYER28";
		}
		if (selHUDColor == 56)
		{
			return "HUD_COLOUR_NET_PLAYER29";
		}
		if (selHUDColor == 57)
		{
			return "HUD_COLOUR_NET_PLAYER30";
		}
		if (selHUDColor == 58)
		{
			return "HUD_COLOUR_NET_PLAYER31";
		}
		if (selHUDColor == 59)
		{
			return "HUD_COLOUR_NET_PLAYER32";
		}
		if (selHUDColor == 60)
		{
			return "HUD_COLOUR_SIMPLEBLIP_DEFAULT";
		}
		if (selHUDColor == 61)
		{
			return "HUD_COLOUR_MENU_BLUE";
		}
		if (selHUDColor == 62)
		{
			return "HUD_COLOUR_MENU_GREY_LIGHT";
		}
		if (selHUDColor == 63)
		{
			return "HUD_COLOUR_MENU_BLUE_EXTRA_DARK";
		}
		if (selHUDColor == 64)
		{
			return "HUD_COLOUR_MENU_YELLOW";
		}
		if (selHUDColor == 65)
		{
			return "HUD_COLOUR_MENU_YELLOW_DARK";
		}
		if (selHUDColor == 66)
		{
			return "HUD_COLOUR_MENU_GREEN";
		}
		if (selHUDColor == 67)
		{
			return "HUD_COLOUR_MENU_GREY";
		}
		if (selHUDColor == 68)
		{
			return "HUD_COLOUR_MENU_GREY_DARK";
		}
		if (selHUDColor == 69)
		{
			return "HUD_COLOUR_MENU_HIGHLIGHT";
		}
		if (selHUDColor == 70)
		{
			return "HUD_COLOUR_MENU_STANDARD";
		}
		if (selHUDColor == 71)
		{
			return "HUD_COLOUR_MENU_DIMMED";
		}
		if (selHUDColor == 72)
		{
			return "HUD_COLOUR_MENU_EXTRA_DIMMED";
		}
		if (selHUDColor == 73)
		{
			return "HUD_COLOUR_BRIEF_TITLE";
		}
		if (selHUDColor == 74)
		{
			return "HUD_COLOUR_MID_GREY_MP";
		}
		if (selHUDColor == 75)
		{
			return "HUD_COLOUR_NET_PLAYER1_DARK";
		}
		if (selHUDColor == 76)
		{
			return "HUD_COLOUR_NET_PLAYER2_DARK";
		}
		if (selHUDColor == 77)
		{
			return "HUD_COLOUR_NET_PLAYER3_DARK";
		}
		if (selHUDColor == 78)
		{
			return "HUD_COLOUR_NET_PLAYER4_DARK";
		}
		if (selHUDColor == 79)
		{
			return "HUD_COLOUR_NET_PLAYER5_DARK";
		}
		if (selHUDColor == 80)
		{
			return "HUD_COLOUR_NET_PLAYER6_DARK";
		}
		if (selHUDColor == 81)
		{
			return "HUD_COLOUR_NET_PLAYER7_DARK";
		}
		if (selHUDColor == 82)
		{
			return "HUD_COLOUR_NET_PLAYER8_DARK";
		}
		if (selHUDColor == 83)
		{
			return "HUD_COLOUR_NET_PLAYER9_DARK";
		}
		if (selHUDColor == 84)
		{
			return "HUD_COLOUR_NET_PLAYER10_DARK";
		}
		if (selHUDColor == 85)
		{
			return "HUD_COLOUR_NET_PLAYER11_DARK";
		}
		if (selHUDColor == 86)
		{
			return "HUD_COLOUR_NET_PLAYER12_DARK";
		}
		if (selHUDColor == 87)
		{
			return "HUD_COLOUR_NET_PLAYER13_DARK";
		}
		if (selHUDColor == 88)
		{
			return "HUD_COLOUR_NET_PLAYER14_DARK";
		}
		if (selHUDColor == 89)
		{
			return "HUD_COLOUR_NET_PLAYER15_DARK";
		}
		if (selHUDColor == 90)
		{
			return "HUD_COLOUR_NET_PLAYER16_DARK";
		}
		if (selHUDColor == 91)
		{
			return "HUD_COLOUR_NET_PLAYER17_DARK";
		}
		if (selHUDColor == 92)
		{
			return "HUD_COLOUR_NET_PLAYER18_DARK";
		}
		if (selHUDColor == 93)
		{
			return "HUD_COLOUR_NET_PLAYER19_DARK";
		}
		if (selHUDColor == 94)
		{
			return "HUD_COLOUR_NET_PLAYER20_DARK";
		}
		if (selHUDColor == 95)
		{
			return "HUD_COLOUR_NET_PLAYER21_DARK";
		}
		if (selHUDColor == 96)
		{
			return "HUD_COLOUR_NET_PLAYER22_DARK";
		}
		if (selHUDColor == 97)
		{
			return "HUD_COLOUR_NET_PLAYER23_DARK";
		}
		if (selHUDColor == 98)
		{
			return "HUD_COLOUR_NET_PLAYER24_DARK";
		}
		if (selHUDColor == 99)
		{
			return "HUD_COLOUR_NET_PLAYER25_DARK";
		}
		if (selHUDColor == 100)
		{
			return "HUD_COLOUR_NET_PLAYER26_DARK";
		}
		if (selHUDColor == 101)
		{
			return "HUD_COLOUR_NET_PLAYER27_DARK";
		}
		if (selHUDColor == 102)
		{
			return "HUD_COLOUR_NET_PLAYER28_DARK";
		}
		if (selHUDColor == 103)
		{
			return "HUD_COLOUR_NET_PLAYER29_DARK";
		}
		if (selHUDColor == 104)
		{
			return "HUD_COLOUR_NET_PLAYER30_DARK";
		}
		if (selHUDColor == 105)
		{
			return "HUD_COLOUR_NET_PLAYER31_DARK";
		}
		if (selHUDColor == 106)
		{
			return "HUD_COLOUR_NET_PLAYER32_DARK";
		}
		if (selHUDColor == 107)
		{
			return "HUD_COLOUR_BRONZE";
		}
		if (selHUDColor == 108)
		{
			return "HUD_COLOUR_SILVER";
		}
		if (selHUDColor == 109)
		{
			return "HUD_COLOUR_GOLD";
		}
		if (selHUDColor == 110)
		{
			return "HUD_COLOUR_PLATINUM";
		}
		if (selHUDColor == 111)
		{
			return "HUD_COLOUR_GANG1";
		}
		if (selHUDColor == 112)
		{
			return "HUD_COLOUR_GANG2";
		}
		if (selHUDColor == 113)
		{
			return "HUD_COLOUR_GANG3";
		}
		if (selHUDColor == 114)
		{
			return "HUD_COLOUR_GANG4";
		}
		if (selHUDColor == 115)
		{
			return "HUD_COLOUR_SAME_CREW";
		}
		if (selHUDColor == 116)
		{
			return "HUD_COLOUR_FREEMODE";
		}
		if (selHUDColor == 117)
		{
			return "HUD_COLOUR_PAUSE_BG";
		}
		if (selHUDColor == 118)
		{
			return "HUD_COLOUR_FRIENDLY";
		}
		if (selHUDColor == 119)
		{
			return "HUD_COLOUR_ENEMY";
		}
		if (selHUDColor == 120)
		{
			return "HUD_COLOUR_LOCATION";
		}
		if (selHUDColor == 121)
		{
			return "HUD_COLOUR_PICKUP";
		}
		if (selHUDColor == 122)
		{
			return "HUD_COLOUR_PAUSE_SINGLEPLAYER";
		}
		if (selHUDColor == 123)
		{
			return "HUD_COLOUR_FREEMODE_DARK";
		}
		if (selHUDColor == 124)
		{
			return "HUD_COLOUR_INACTIVE_MISSION";
		}
		if (selHUDColor == 125)
		{
			return "HUD_COLOUR_DAMAGE";
		}
		if (selHUDColor == 126)
		{
			return "HUD_COLOUR_PINKLIGHT";
		}
		if (selHUDColor == 127)
		{
			return "HUD_COLOUR_PM_MITEM_HIGHLIGHT";
		}
		if (selHUDColor == 128)
		{
			return "HUD_COLOUR_SCRIPT_VARIABLE";
		}
		if (selHUDColor == 129)
		{
			return "HUD_COLOUR_YOGA";
		}
		if (selHUDColor == 130)
		{
			return "HUD_COLOUR_TENNIS";
		}
		if (selHUDColor == 131)
		{
			return "HUD_COLOUR_GOLF";
		}
		if (selHUDColor == 132)
		{
			return "HUD_COLOUR_SHOOTING_RANGE";
		}
		if (selHUDColor == 133)
		{
			return "HUD_COLOUR_FLIGHT_SCHOOL";
		}
		if (selHUDColor == 134)
		{
			return "HUD_COLOUR_NORTH_BLUE";
		}
		if (selHUDColor == 135)
		{
			return "HUD_COLOUR_SOCIAL_CLUB";
		}
		if (selHUDColor == 136)
		{
			return "HUD_COLOUR_PLATFORM_BLUE";
		}
		if (selHUDColor == 137)
		{
			return "HUD_COLOUR_PLATFORM_GREEN";
		}
		if (selHUDColor == 138)
		{
			return "HUD_COLOUR_PLATFORM_GREY";
		}
		if (selHUDColor == 139)
		{
			return "HUD_COLOUR_FACEBOOK_BLUE";
		}
		if (selHUDColor == 140)
		{
			return "HUD_COLOUR_INGAME_BG";
		}
		if (selHUDColor == 141)
		{
			return "HUD_COLOUR_DARTS";
		}
		if (selHUDColor == 142)
		{
			return "HUD_COLOUR_WAYPOINT";
		}
		if (selHUDColor == 143)
		{
			return "HUD_COLOUR_MICHAEL";
		}
		if (selHUDColor == 144)
		{
			return "HUD_COLOUR_FRANKLIN";
		}
		if (selHUDColor == 145)
		{
			return "HUD_COLOUR_TREVOR";
		}
		if (selHUDColor == 146)
		{
			return "HUD_COLOUR_GOLF_P1";
		}
		if (selHUDColor == 147)
		{
			return "HUD_COLOUR_GOLF_P2";
		}
		if (selHUDColor == 148)
		{
			return "HUD_COLOUR_GOLF_P3";
		}
		if (selHUDColor == 149)
		{
			return "HUD_COLOUR_GOLF_P4";
		}
		if (selHUDColor == 150)
		{
			return "HUD_COLOUR_WAYPOINTLIGHT";
		}
		if (selHUDColor == 151)
		{
			return "HUD_COLOUR_WAYPOINTDARK";
		}
		if (selHUDColor == 152)
		{
			return "HUD_COLOUR_PANEL_LIGHT";
		}
		if (selHUDColor == 153)
		{
			return "HUD_COLOUR_MICHAEL_DARK";
		}
		if (selHUDColor == 154)
		{
			return "HUD_COLOUR_FRANKLIN_DARK";
		}
		if (selHUDColor == 155)
		{
			return "HUD_COLOUR_TREVOR_DARK";
		}
		if (selHUDColor == 156)
		{
			return "HUD_COLOUR_OBJECTIVE_ROUTE";
		}
		if (selHUDColor == 157)
		{
			return "HUD_COLOUR_PAUSEMAP_TINT";
		}
		if (selHUDColor == 158)
		{
			return "HUD_COLOUR_PAUSE_DESELECT";
		}
		if (selHUDColor == 159)
		{
			return "HUD_COLOUR_PM_WEAPONS_PURCHASABLE";
		}
		if (selHUDColor == 160)
		{
			return "HUD_COLOUR_PM_WEAPONS_LOCKED";
		}
		if (selHUDColor == 161)
		{
			return "HUD_COLOUR_END_SCREEN_BG";
		}
		if (selHUDColor == 162)
		{
			return "HUD_COLOUR_CHOP";
		}
		if (selHUDColor == 163)
		{
			return "HUD_COLOUR_PAUSEMAP_TINT_HALF";
		}
		if (selHUDColor == 164)
		{
			return "HUD_COLOUR_NORTH_BLUE_OFFICIAL";
		}
		if (selHUDColor == 165)
		{
			return "HUD_COLOUR_SCRIPT_VARIABLE_2";
		}
	}


}