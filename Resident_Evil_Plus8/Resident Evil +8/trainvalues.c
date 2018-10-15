#include <types.h>


#define USA_CODES	0
#define PAL_CODES	1
#define JAP_CODES	2


// WHICH GAME REGIONS TO SUPPORT? (Defaults to USA if none selected)
u8 trainer_regions[3] = {
	1, //USA
	1, //PAL
	0, //JAP
};


// TRAINER MENU SETUP
#define MENU_FONT_WIDTH			16
#define MENU_FONT_HEIGHT		16
#define MENU_V_DIFFRENCE		18 /* Font height + Diffrence ! */
#define MENU_MOVING_SPEED		1
#define MENU_X_POSITION			80
#define MENU_Y_POSITION			190

#define MENU_OPTION_X_POSITION	520

// Number of items to display in menu
#define MENU_NUM_DISPLAY		12


char *menuoptions[]  = { "OFF", "ON" };

typedef struct _MENU {
	char *str;
	int option;
	u32 *usa_codes;
	u32 *pal_codes;
	u32 *jap_codes;
} MENU;



// Edit below to change menu

//master_code must be defined, but not used in the menu!
u32 master_code[][2*2] = {
	// USA Codes
	{
		0xC411E410, 0x00000800,
		0x00000000, 0x00000000 //end of code list
	},

	// PAL Codes
	{
		0xC4158F50, 0x00000800,
		0x00000000, 0x00000000 //end of code list
	}

	//JAP Codes
};

u32 codes_health[][2*2] = {
	// USA Codes
	{
		0x021F11BE, 0x00000578,
		0x00000000, 0x00000000 //end of code list
	},

	// PAL Codes
	{
		0x0222A29E, 0x00000578,
		0x00000000, 0x00000000 //end of code list
	}

	//JAP Codes
};

u32 codes_editor[][36*2] = {
	// USA Codes
	{
		0x04002C00, 0x808D8718,
		0x04002C04, 0xA01B0000,
		0x04002C08, 0x28000002,
		0x04002C0C, 0x41820060,
		0x04002C10, 0xA004FC10,
		0x04002C14, 0x5400E73F,
		0x04002C18, 0x41820054,
		0x04002C1C, 0x3CC08000,
		0x04002C20, 0x60C62C70,
		0x04002C24, 0x7CC600AE,
		0x04002C28, 0x38E00220,
		0x04002C2C, 0x7CE70430,
		0x04002C30, 0x70E70002,
		0x04002C34, 0x7CA32214,
		0x04002C38, 0x7CA53A14,
		0x04002C3C, 0x88053B63,
		0x04002C40, 0x7C003214,
		0x04002C44, 0x5400063E,
		0x04002C48, 0x40820020,
		0x04002C4C, 0x28000082,
		0x04002C50, 0x40810018,
		0x04002C54, 0x28060001,
		0x04002C58, 0x4182000C,
		0x04002C5C, 0x38000082,
		0x04002C60, 0x48000008,
		0x04002C64, 0x38000000,
		0x04002C68, 0x98053B63,
		0x04002C6C, 0x4E800020,
		0x04002C70, 0x00FF0100,
		0x04002C74, 0xFF000000,
		0x04002C78, 0x01000000,
		0x04002C7C, 0x00000000,
		0x04073190, 0x4BF8FA71,
		0x00000000, 0x00000000, //padding! Length must be the same for all regions
		0x00000000, 0x00000000,
		0x00000000, 0x00000000 //end of code list
	},

	// PAL Codes
	{
		0x04002C00, 0xA0BF0000,
		0x04002C04, 0x28050002,
		0x04002C08, 0x41820068,
		0x04002C0C, 0x3CA08022,
		0x04002C10, 0x60A56478,
		0x04002C14, 0xA0A50000,
		0x04002C18, 0x54A5E73F,
		0x04002C1C, 0x41820054,
		0x04002C20, 0x3CC08000,
		0x04002C24, 0x60C62C78,
		0x04002C28, 0x7CC628AE,
		0x04002C2C, 0x3B400220,
		0x04002C30, 0x7F5A2C30,
		0x04002C34, 0x735A0002,
		0x04002C38, 0x7CA02214,
		0x04002C3C, 0x7CA5D214,
		0x04002C40, 0x8B450001,
		0x04002C44, 0x7F5A3214,
		0x04002C48, 0x575A063E,
		0x04002C4C, 0x40820020,
		0x04002C50, 0x281A0082,
		0x04002C54, 0x40810018,
		0x04002C58, 0x28060001,
		0x04002C5C, 0x4182000C,
		0x04002C60, 0x3B400082,
		0x04002C64, 0x48000008,
		0x04002C68, 0x3B400000,
		0x04002C6C, 0x9B450001,
		0x04002C70, 0x7C04022E,
		0x04002C74, 0x4E800020,
		0x04002C78, 0x00FF0100,
		0x04002C7C, 0xFF000000,
		0x04002C80, 0x01000000,
		0x04002C84, 0x00000000,
		0x0408C488, 0x4BF76779,
		0x00000000, 0x00000000 //end of code list
	}

	//JAP Codes
};

u32 codes_crate[][5*2] = {
	// USA Codes
	{
		0x00000000, 0x841F1200,
		0x00FF0001, 0x01820001,
		0x00000000, 0x00000000, //padding! Length must be the same for all regions
		0x00000000, 0x00000000,
		0x00000000, 0x00000000 //end of code list
	},

	// PAL Codes
	{
		0x00000000, 0x8222A2E2,
		0x00000001, 0x01840002,
		0x00000000, 0x8222A2E4,
		0x00000063, 0x00840002,
		0x00000000, 0x00000000 //end of code list
	}

	//JAP Codes
};

u32 codes_allfiles[][2*2] = {
	// USA Codes
	{
		0x041F3B40, 0xFFFFFFFF,
		0x00000000, 0x00000000 //end of code list
	},

	// PAL Codes
	{
		0x0422CC20, 0xFFFFFFFF,
		0x00000000, 0x00000000 //end of code list
	}

	//JAP Codes
};

u32 codes_unlockdoors[][2*2] = {
	// USA Codes
	{
		0x001F3BA4, 0x00000CFF,
		0x00000000, 0x00000000 //end of code list
	},

	// PAL Codes
	{
		0x0022CC84, 0x00000CFF,
		0x00000000, 0x00000000 //end of code list
	}

	//JAP Codes
};

u32 codes_bombtimer[][2*2] = {
	// USA Codes
	{
		0x041FC2C8, 0x000015D0,
		0x00000000, 0x00000000 //end of code list
	},

	// PAL Codes
	{
		0x042353A8, 0x000015D0,
		0x00000000, 0x00000000 //end of code list
	}

	//JAP Codes
};

u32 codes_finishtime[][2*2] = {
	// USA Codes
	{
		0x041FC300, 0x00000000,
		0x00000000, 0x00000000 //end of code list
	},

	// PAL Codes
	{
		0x042353E0, 0x00000000,
		0x00000000, 0x00000000 //end of code list
	}

	//JAP Codes
};

u32 codes_kills[][2*2] = {
	// USA Codes
	{
		0x04040974, 0x38000000,
		0x00000000, 0x00000000 //end of code list
	},

	// PAL Codes
	{
		0x0404CD94, 0x7C030050,
		0x00000000, 0x00000000 //end of code list
	}

	//JAP Codes
};


MENU mainmenu[] = {
	{
		"Infinite Health", 0,
		codes_health[USA_CODES],		codes_health[PAL_CODES],		(u32*)0
	},
	{
		"Inventory Editor (C-Stick)", 0,
		codes_editor[USA_CODES],		codes_editor[PAL_CODES],		(u32*)0
	},
	{
		"All Items In Crate", 0,
		codes_crate[USA_CODES],			codes_crate[PAL_CODES],			(u32*)0
	},
	{
		"Have All Files", 0,
		codes_allfiles[USA_CODES],		codes_allfiles[PAL_CODES],		(u32*)0
	},
	{
		"Unlock All Doors", 0,
		codes_unlockdoors[USA_CODES],	codes_unlockdoors[PAL_CODES],	(u32*)0
	},
	{
		"Freeze Bomb Timer", 0,
		codes_bombtimer[USA_CODES],		codes_bombtimer[PAL_CODES],		(u32*)0
	},
	{
		"Low Finishing Time", 0,
		codes_finishtime[USA_CODES],	codes_finishtime[PAL_CODES],	(u32*)0
	},
	{
		"1-Hit Kills", 0,
		codes_kills[USA_CODES],			codes_kills[PAL_CODES],			(u32*)0
	},

	//end menu
	{
		(char*)0, 0,
		(u32*)0, (u32*)0, (u32*)0
	}
};
