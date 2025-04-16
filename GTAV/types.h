#pragma once

typedef void* Void;
typedef int Any;
typedef unsigned int uint;
typedef int Hash;
typedef int BOOL;
typedef int Entity;
typedef int Player;
typedef int FireId;
typedef int Ped;
typedef int Vehicle;
typedef int Cam;
typedef int CarGenerator;
typedef int Group;
typedef int Train;
typedef int Pickup;
typedef int Object;
typedef int Weapon;
typedef int Interior;
typedef int Blip;
typedef int Texture;
typedef int TextureDict;
typedef int CoverPoint;
typedef int Camera;
typedef int TaskSequence;
typedef int ColourIndex;
typedef int Sphere;
typedef int ScrHandle;

typedef struct
{
	float x;
	float y;
	float z;
} Vector3;

typedef struct
{
	float x;
	float y;
} Vector2;

typedef struct
{
	int r;
	int g;
	int b;
	int a;
} RGBA;

typedef struct
{
	int year = 2024;
	int month = 4;
	int day = 19;
	int hour = 1;
	int minute = 1;
	int second = 1;
	int millisecond = 1;
} Posix;

typedef struct
{
	float* x;
	float* y;
	float* z;
} Vector3star;

struct opd_s { int32_t sub; int32_t toc; };