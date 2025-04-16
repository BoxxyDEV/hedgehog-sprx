#pragma region Other Loop
void otherLoop()
{
	int year, month, day, hour, min, sec;
	TIME::GET_LOCAL_TIME(&year, &month, &day, &hour, &min, &sec);

	if (keyboardActive)
	{
		if (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 1)
		{
			keyboardInput = GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT();
			keyboardActive = false;
			switch (keyboardAction)
			{
			case AddInt: //addIntOption
				*keyboardVar = StoI(keyboardInput);
				break;
			case VehicleNumberPlate: // vehicle number plate
				VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), keyboardInput);
				break;
			case NameChanger: // name changer
				GTANameChanger(keyboardInput);
				break;
			case InviteByPSN:
				ExternalSources::GameInvite(keyboardInput);
				break;
			case DBGText:
				DebugTextContent = keyboardInput;
				break;
			case TextVehSpawner:
				spawnloop = GAMEPLAY::GET_HASH_KEY(keyboardInput);
				break;
			case UsernameModMenu:
				snprintf(ModUsername, sizeof(ModUsername), "%s", keyboardInput);
				char notifyuser[100];
				snprintf(notifyuser, sizeof(notifyuser), "%s has been set as the username. ~n~Press Save Settings to save it to the hard drive", ModUsername);
				drawNotification("Hedgehog SPRX", notifyuser);
				break;
			case UGCload:
				bool ugcloadsuccessful = DATAFILE::DATAFILE_LOAD_OFFLINE_UGC(keyboardInput);
				if (ugcloadsuccessful)
					printscreen("UGC File has been loaded");
				else
					printscreen("UGC File has failed to load");
				break;
			}

		}
		else if (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 2 || GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 3)
		{
			keyboardActive = false;
		}
	}

	// I'm just going to do it shorthand from now on if this compiles 27/3/2024
	if (SuperJump)
		GAMEPLAY::SET_SUPER_JUMP_THIS_FRAME(PLAYER::PLAYER_ID());

	if (NeverWanted)
		PLAYER::CLEAR_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID());

	WEAPON::SET_PED_INFINITE_AMMO_CLIP(PLAYER::PLAYER_PED_ID(), UnlimitedAmmo);
	ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), !Invisable);
	PED::SET_PED_CAN_RAGDOLL(PLAYER::PLAYER_PED_ID(), !DoNotRagdoll);


	if (HardcoreMode && PLAYER::IS_PLAYER_DEAD(PLAYER::PLAYER_ID()))
	{
		NETWORK::SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME();
	}

	if (spawnloop != 0)
	{
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
		if (int veh = Boxuga::VehicleSpawner(spawnloop, SpawninCar) != 0)
		{
			UI::BUSYSPINNER_OFF();
			spawnloop = 0;
		}
	}

	if (ExplosiveWeapon)
	{
		GAMEPLAY::SET_EXPLOSIVE_AMMO_THIS_FRAME(PLAYER::PLAYER_ID());
	}

	if (BurstWispon)
	{
		GAMEPLAY::SET_FIRE_AMMO_THIS_FRAME(PLAYER::PLAYER_ID());
	}

	if (SuperPunch)
	{
		GAMEPLAY::SET_EXPLOSIVE_MELEE_THIS_FRAME(PLAYER::PLAYER_ID());
	}

	if (CONTROLS::IS_CONTROL_PRESSED(0, BuTTON_X) && SuperRun)
	{
		ENTITY::APPLY_FORCE_TO_ENTITY(PLAYER::PLAYER_PED_ID(), 0, 0, 35, 0, 0, 0, 0, true, true, true, true, false, true);
	}

	if (PLAYER::IS_PLAYER_PRESSING_HORN(PLAYER::PLAYER_ID()) && HornBoost)
	{
		ENTITY::APPLY_FORCE_TO_ENTITY(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 0, 0, 5000, 0, 0, 0, 0, true, true, true, true, false, true);
	}

	if (DebugText)
	{
		drawText(DebugTextContent, 1, DebugTextX, DebugTextY, DebugTextScaleX, DebugTextScaleY, debugtextr, debugtextb, debugtextg, debugtexta, debugtextcentre);
	}

	if (vehiclespeed)
	{
		char vehspeed[10];
		if (speedosystem == 1)
		{
			snprintf(vehspeed, sizeof(vehspeed), "%i KM/h", FtoI(ENTITY::GET_ENTITY_SPEED(PLAYER::PLAYER_PED_ID())*3.6));
		}
		else if (speedosystem == 2)
		{ // PED::GET_VEHICLE_PED_IS_USING()
			snprintf(vehspeed, sizeof(vehspeed), "%i Mi/h", FtoI(ENTITY::GET_ENTITY_SPEED(PLAYER::PLAYER_PED_ID())*2.236936));
		}
		drawText(vehspeed, 4, 0.27f, 0.76f, 0.4f, 0.4, 255, 255, 255, 255, true);
	}

	if (PoisonWater && ENTITY::IS_ENTITY_IN_WATER(PLAYER::PLAYER_PED_ID()))
	{
		


		if (timer != sec)
		{
			ENTITY::SET_ENTITY_HEALTH(PLAYER::PLAYER_PED_ID(), ENTITY::GET_ENTITY_HEALTH(PLAYER::PLAYER_PED_ID()) - 5);
			timer = sec;
		}

	}

	if (AngryCougars && !PLAYER::IS_PLAYER_DEAD(PLAYER::PLAYER_ID()))
	{

		int randnum;
		if (PLAYER::GET_PLAYER_WANTED_LEVEL != 0) // don't know why i did it like this but if have a wanted level seems like it has less of a chance
		{
			randnum = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 2000); // random int value between 0 and 200
		}
		else
		{
			randnum = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 1040);
		}

		int randpos = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 100); // generates a random x & y pos to add to the playerpos
		int randposy = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 20);

		if (randnum > 50 && randnum < 60) // if randnum between 50 and 60
		{

			Vector3 playerpos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false); // gets the position of the player
			Ped cougar = Boxuga::SummonPed("a_c_mtlion", (playerpos.x + randpos), (playerpos.y + randposy), playerpos.z + 5, true, true);
			if (isEntityArrFilled(spawnedCougars))
			{
				if (ENTITY::DOES_ENTITY_EXIST(spawnedCougars[cougarpos]))
				{
					ENTITY::DELETE_ENTITY(&spawnedCougars[cougarpos]);
				}
					spawnedCougars[cougarpos] = cougar;
					cougarpos += 1;
			}
			else
				appendtoEntityArray(spawnedCougars, cougar);
			
			Object ball = Boxuga::CreateObj("prop_bskball_01", ENTITY::GET_ENTITY_COORDS(cougar));
			ENTITY::ATTACH_ENTITY_TO_ENTITY(ball, cougar, PED::GET_PED_BONE_INDEX(cougar, 0x796e), 0, 0, 10, 0, 0, 0, false, false, false, false, 2, true);
			
		}
		
	}

	for (int bouncycougar = 0; bouncycougar < 25; bouncycougar++)
	{
		if (ENTITY::DOES_ENTITY_EXIST(spawnedCougars[bouncycougar]))
		{
			Vehicle vehisin;
			Vector3 myCoord = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
			Vector3 cougarCoord = ENTITY::GET_ENTITY_COORDS(spawnedCougars[bouncycougar], false);
			float distenceBetween = SYSTEM::VDIST(myCoord.x, myCoord.y, myCoord.z, cougarCoord.x, cougarCoord.y, cougarCoord.z);
			if (distenceBetween < 5)
			{
				if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false))
				{
					Vehicle myCar = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
					ENTITY::APPLY_FORCE_TO_ENTITY(myCar, false, 0, 1200, 500, 0, 0, 0, true, true, true, true, false, true);
				}
				else 
					ENTITY::APPLY_FORCE_TO_ENTITY(PLAYER::PLAYER_PED_ID(), false, 0, 1200, 500, 0, 0, 0, true, true, true, true, false, true);
			}
			
		}
	}
		



	if (SyncTime)
	{
		int y, m, d, h, min, s;
		TIME::GET_LOCAL_TIME(&y, &m, &d, &h, &min, &s); // gets system time
		NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(h, min, s); // sets it
	}

	if (GlitchySpeedRun)
	{
		*(float*)0x4124527C = 16;
	}

	if (!GlitchySpeedRun)
	{
		*(float*)0x4124527C = 1;
	}

	if (FirstOpen)
	{
		drawText("Open with Right DPAD + X", 7, 0.145, 0.08, 0.30, 0.30, 126, 255, 56, 120, true);
	}

	if (submenu == Closed && Menuname)
	{
		drawText("Hedgehog SPRX", 7, 0.145, 0.05, 0.55, 0.55, 126, 255, 56, 120, true);
	}

	ENTITY::SET_ENTITY_INVINCIBLE(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), vehGodMode);
	ENTITY::SET_ENTITY_VISIBLE(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), !vehInvisiblity);
	AUDIO::SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(MobileRadio);

	if (XYZDisplay)
	{
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
		char coordsx[10], coordsy[10], coordsz[10];
		snprintf(coordsx, sizeof(coordsx), "X: %s", FtoS(FtoI(coords.x)));
		snprintf(coordsy, sizeof(coordsy), "Y: %s", FtoS(FtoI(coords.y)));
		snprintf(coordsz, sizeof(coordsz), "Z: %s", FtoS(FtoI(coords.z)));
		drawText(coordsx, 4, 0.27f, 0.80f, 0.4f, 0.4, 255, 255, 255, 255, true);
		drawText(coordsy, 4, 0.27f, 0.82f, 0.4f, 0.4, 255, 255, 255, 255, true);
		drawText(coordsz, 4, 0.27f, 0.84f, 0.4f, 0.4, 255, 255, 255, 255, true);
	}

	if (RSDevMode)
		NETWORK::NETWORK_PLAYER_IS_ROCKSTAR_DEV(PLAYER::PLAYER_ID());

	if (UI::IS_WARNING_MESSAGE_ACTIVE())
		submenu = Closed;

	

	if (NoClip)
	{
		if (CONTROLS::IS_CONTROL_PRESSED(0, 205))
		{
			characterpos.z = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0, 0.0, 1.5).z;
		}
		if (CONTROLS::IS_CONTROL_PRESSED(0, 43))
		{
			characterpos.z = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0, 0.0, -1.5).z;
		}
		if (CONTROLS::IS_CONTROL_PRESSED(0, 108))
		{
			characterpos.x = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 1.5, 0.0, 0.0).x;
		}
		if (CONTROLS::IS_CONTROL_PRESSED(0, 34)) // left stick left
		{
			characterpos.x = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), -1.5, 0.0, 0.0).x;
		}
		if (CONTROLS::IS_CONTROL_PRESSED(0, 39))
		{
			characterpos.y = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0, 1.5, 0.0).y;
		}
		if (CONTROLS::IS_CONTROL_PRESSED(0, 32))
		{
			characterpos.y = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0, -1.5, 0.0).y;
		}
		if (CONTROLS::IS_CONTROL_PRESSED(0, 14))
		{
			if (ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()) >= 360)
			{
				ENTITY::SET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID(), 0);
			}
			else
			{
				ENTITY::SET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID(), 0);
			}
		}
		Boxuga::teleportcharacter(characterpos);
	}


	if (rploop)
	{
		int xp;
		STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_XP_FM"), &xp, false);
		if (xp < 47551850)
		{
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_XP_FM"), xp + rploopamount, false);
		}
		else
		{
			drawNotification("Hedgehog SPRX", "You have hit the Rank limit of 1000");
			rploop = false;
		}

	}

	if (moneyloop)
		NETMONEY::NETWORK_EARN_FROM_ROCKSTAR(moneyloopamount);


	if (vehFixCosmeticCondition)
		VEHICLE::SET_VEHICLE_FIXED(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()));

	if (loopenginefix)
		VEHICLE::SET_VEHICLE_ENGINE_HEALTH(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 1000);

	if (GodMode)
		PLAYER::SET_PLAYER_INVINCIBLE(PLAYER::PLAYER_ID(), true);
	else 
		PLAYER::SET_PLAYER_INVINCIBLE(PLAYER::PLAYER_ID(), false);

	if (NoCollition)
		ENTITY::SET_ENTITY_COLLISION(PLAYER::PLAYER_PED_ID(), false, true);
	else
		ENTITY::SET_ENTITY_COLLISION(PLAYER::PLAYER_PED_ID(), true, true);
	

	for (int i = 0; i < 18; i++) // player loop
	{
		if (moneydrop[i])
		{
			Vector3 pedpos = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(i), true);
			STREAMING::REQUEST_MODEL(289396019); // money bag hash
			if (STREAMING::HAS_MODEL_LOADED(289396019)) // Makes sure the model has actually loaded into memory
			{
				OBJECT::CREATE_AMBIENT_PICKUP(3463437675, pedpos.x, pedpos.y, pedpos.z + 1, 0, 40000, 289396019, true, true); // Creates the drop
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(289396019); // tells the game it can delete the bag to free memory
			}
		}

		if (boostremoteplayercar[i])
		{
			int vehicle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED(i));
			if (NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(vehicle))
			{
				ENTITY::APPLY_FORCE_TO_ENTITY(vehicle, 0, 0, 5000, 0, 0, 0, 0, true, true, true, true, false, true);
				boostremoteplayercar[i] = false;
			}
		}

		if (launchremoteplayercar[i])
		{
			int vehicle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED(i));
			if (NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(vehicle))
			{
				ENTITY::APPLY_FORCE_TO_ENTITY(vehicle, 0, 0, 0, 5000, 0, 0, 0, true, true, true, true, false, true);
				launchremoteplayercar[i] = false;
			}
		}

		if (drawlinetoplayer[i])
		{
			Vector3 mypos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
			Vector3 theirpos = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(i), true);
			GRAPHICS::DRAW_LINE(mypos.x, mypos.y, mypos.z, theirpos.x, theirpos.y, theirpos.z, bannerRectRed, bannerRectGreen, bannerRectBlue, 255);
		}
	}

	

	if (SCRIPT::HAS_SCRIPT_LOADED("freemode"))
	{
		/*
		if (fiveMin == min)
		{
			int bankbal = NETWORKCASH::NETWORK_GET_VC_BANK_BALANCE();

			printf("\n[Hedgehog SPRX by Boxuga] Saved RP/Bank Money\n");
			fiveMin = addMin(min, 10);
		}
		else
		{
			if (fiveMin == NULL)
			{
				fiveMin = addMin(min, 10);
			}
		}*/
		//drawText("Hello", 1, 0.5, 0.9, 0.5, 0.5, 255, 255, 255, 255, true);

		if (!hasLoadedOnline)
		{
			
			if (autoMoney != 0)
			{
				if (autoMoney > 10000000)
				{
					NETMONEY::NETWORK_EARN_FROM_ROCKSTAR(10000000); // From memory i think it only worked with amounts 10mil and lower
					autoMoney = autoMoney - 10000000;
				}
				else 
				{
					NETMONEY::NETWORK_EARN_FROM_ROCKSTAR(autoMoney);
					autoMoney = 0;
				}
				
			}
			if (autoRP != 0)
			{
				int currentrp;
				int rankstat = GAMEPLAY::GET_HASH_KEY("MP0_CHAR_XP_FM");
				STATS::STAT_GET_INT(rankstat, &currentrp, false);
				if (autoRP > 2165850)
				{
					STATS::STAT_SET_INT(rankstat, currentrp + 2165850, false);
					autoRP = autoRP - 2165850;
				}
				else 
				{
					STATS::STAT_SET_INT(rankstat, currentrp + autoRP, false);
					autoRP = 0;
				}
			}
			if (autoMoney == 0 && autoRP == 0)
			{
				
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_DEATHS_PLAYER"), 1, true); // Hopefully this will work but idk because im dumb asf
				Posix date;
				date.year = 1991;
				date.month = 6;
				date.day = 23;
				Hash createdchar = GAMEPLAY::GET_HASH_KEY("MP0_CHAR_DATE_CREATED");
				STATS::STAT_SET_DATE(createdchar, &date, 7, true);
				hasLoadedOnline = true;
			}
			
		}
	}
	Vector3 gunbulletloc;
	if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::PLAYER_PED_ID(), &gunbulletloc))
	{
		if (TeleportGun)
			Boxuga::teleportcharacter(gunbulletloc);
	}
	
	
}
#pragma endregion