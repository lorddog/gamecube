#include <types.h>

#include <memory.h>
#include <video.h>
#include <blit.h>
#include <bitmap.h>
#include <string.h>
#include <joypad.h>
#include <font.h>
#include <fst.h>
#include <apploader.h>

#include "tr_bg.raw.c"
#include "tr_logo.raw.c"
#include "tr_font.raw.c"
#include "tr_menufont.raw.c"
#include "tr_arrows.raw.c"

#include "code_engine.h"


// TRAINER SETUP
// Logo
#define LOGO_Y_START_POS	60
#define LOGO_MOVING_SPEED   4

// Scroller Font
#define BG_FONT_WIDTH		32
#define BG_FONT_HEIGHT		32

// Scroller
#define SCROLLER_BMP		24 /* Number of bitmaps used in scroller */
#define SCROLLER_SPACE		25 /* Spacing between bitmaps in scroller */
#define SCROLL_SPEED		3  /* animation speed */
#define SCROLLER_Y_POSITION 420 /* scroller position */

char *scroller="           StarCube is proud to present a Resident Evil (NTSC & PAL) +8 Trainer for your Nintendo Gamecube.                Greets: holycube, eurasia,  pdx, fairlight, kalisto, triforce, rare and all our friends.                Coding: Parasyte & LordDog                Gfx: LordDog                Loop time!";

// Trainer Menu
#include "trainvalues.c"
// END OF SETUP !


// Reset by pressing start // my Cube is far away ;)
#define REG_HOTRESET        (0xCC003024)
#define REG_HOTRESET_PTR    ((volatile u32*)REG_HOTRESET)
#define M_HOTRESET          *REG_HOTRESET_PTR = 0x00000000


int sin160[] = {
  0,  1,  3,  4,  5,  6,  7,  9, 10, 11, 12, 13, 15, 16, 17, 18, 19, 20, 21, 22,
 23, 23, 24, 25, 26, 27, 27, 28, 29, 29, 30, 30, 30, 31, 31, 31, 32, 32, 32, 32,
 32, 32, 32, 32, 32, 31, 31, 31, 30, 30, 30, 29, 29, 28, 27, 27, 26, 25, 24, 23,
 23, 22, 21, 20, 19, 18, 17, 16, 15, 13, 12, 11, 10,  9,  7,  6,  5,  4,  3,  1,
  0, -1, -3, -4, -5, -6, -7, -9,-10,-11,-12,-13,-15,-16,-17,-18,-19,-20,-21,-22,
-23,-23,-24,-25,-26,-27,-27,-28,-29,-29,-30,-30,-30,-31,-31,-31,-32,-32,-32,-32,
-32,-32,-32,-32,-32,-31,-31,-31,-30,-30,-30,-29,-29,-28,-27,-27,-26,-25,-24,-23,
-23,-22,-21,-20,-19,-18,-17,-16,-15,-13,-12,-11,-10, -9, -7, -6, -5, -4, -3, -1
};


// Not Perfect Yet ! (Not smooth enough!)
int sin88[] = {
  0,  1,  3,  4,  5,  6,  7,  9, 10, 11, 12, 12, 13, 12, 12, 11, 10,  9,
  8,  7,  6,  5,  4,  3,  2,  1,  0, -1, -2, -3, -4, -4, -5, -5, -5, -4, -4, -3,
  -1
};


void init() {
    DVDStopDrive();
    FontInit(tr_menufont_Bitmap, MENU_FONT_WIDTH, MENU_FONT_HEIGHT, TR_MENUFONT_WIDTH, FONTYUV);
    HeapInit();
    VideoInit();
}

int menu_getlast(MENU *menu) {
    int i = 0;

    while (1) {
        if (!(menu[i].str)) break;
        i++;
    }

    return (i - 1);
}

void LoadDisc() {
    //vars
    u32(*entry)(void), (*init_engine)(void);
    u32 *codeptr;
    int i, j, region = USA_CODES;

    //init DVD
    DVDResetDrive();
    DVDGetDiscID();
    //	if (*(u8*)(0x80000008)) DVDAudioStatus(1, (*(u8*)(0x80000009) ? 0 : 0x0A));
    //	else DVDAudioStatus(0,0);

    FSTInit(0); //init FST

    //init video mode
    if ((DVDRegionJ()) || (DVDRegionU())) VIDEO_MODE = 0;
    else VIDEO_MODE = 1;

    entry = RunApploader(0); //run apploader

    /* Begin trainer setup */

    //copy trainer to memory
    MemoryCopy8((u8*)(0x80001840), (u8*)(code_engine), _code_engine);

    //get dvd region
    if ((DVDRegionU()) && (trainer_regions[USA_CODES])) region = USA_CODES;
    else if ((DVDRegionP()) && (trainer_regions[PAL_CODES])) region = PAL_CODES;
    else if ((DVDRegionJ()) && (trainer_regions[JAP_CODES])) region = JAP_CODES;

    //copy codes to memory, master code first
    i = 0;
    codeptr = (u32*)(0x80001860); //master code starts here
    while ((master_code[region][i]) || (master_code[region][i + 1])) {
        *(codeptr++) = master_code[region][i];
        *(codeptr++) = master_code[region][i + 1];
        i += 2;
    }

    //then selected codes from menu
    codeptr = (u32*)(0x80001928); //regular codes start here
    for (i = 0; i <= menu_getlast(mainmenu); i++) {
        if (mainmenu[i].option) {
            j = 0;
            switch (region) {
            case USA_CODES:
                while ((mainmenu[i].usa_codes[j]) || (mainmenu[i].usa_codes[j + 1])) {
                    *(codeptr++) = mainmenu[i].usa_codes[j];
                    *(codeptr++) = mainmenu[i].usa_codes[j + 1];
                    j += 2;
                }
                break;

            case PAL_CODES:
                while ((mainmenu[i].pal_codes[j]) || (mainmenu[i].pal_codes[j + 1])) {
                    *(codeptr++) = mainmenu[i].pal_codes[j];
                    *(codeptr++) = mainmenu[i].pal_codes[j + 1];
                    j += 2;
                }
                break;

            case JAP_CODES:
                while ((mainmenu[i].jap_codes[j]) || (mainmenu[i].jap_codes[j + 1])) {
                    *(codeptr++) = mainmenu[i].jap_codes[j];
                    *(codeptr++) = mainmenu[i].jap_codes[j + 1];
                    j += 2;
                }
                break;
            }
        }
    }

    FlushDC(0x80001840, _code_engine); //flush data cache
    InvalidateIC(0x80001840, _code_engine); //invalidate instruction cache

    //initialize code engine
    init_engine = (taplFunc4)(0x80001858);
    init_engine();

    /* End trainer setup */

    VideoInit();      //set video mode, fixes several imports
    VideoSetBlack(1); //blank video

    entry(); //start game
}

int main() {
    int num_menus = menu_getlast(mainmenu), menu_scroll = 0;
    int menu_speed = MENU_MOVING_SPEED, menu_pos = 0;
    int z = 1, mz = 0, i, j = SCROLLER_BMP, k, x = (SCROLL_SPEED * 2);
    int arrows_flash = 0;
    int stringlen = StringLength(scroller);
    u16 btn;

    BITMAP text[SCROLLER_BMP]; //text bitmaps. bitmaps are independently movable, and allow transparent blits.
    BITMAP logo;
    BITMAP arrows[2] = { //arrow bitmaps, for scrolling menus
        {
            /* x */		MENU_X_POSITION,
            /* y */		(MENU_Y_POSITION - ((TR_ARROWS_HEIGHT / 2) + (MENU_V_DIFFRENCE - MENU_FONT_HEIGHT))), //display above menu text
            /* w */		TR_ARROWS_WIDTH,
            /* h */		(TR_ARROWS_HEIGHT / 2),
            /* bits */	(u32*)tr_arrows_Bitmap
        },
        {
            /* x */		MENU_X_POSITION,
            /* y */		(MENU_Y_POSITION + (MENU_V_DIFFRENCE * MENU_NUM_DISPLAY)), //display below menu text
            /* w */		TR_ARROWS_WIDTH,
            /* h */		(TR_ARROWS_HEIGHT / 2),
            /* bits */	(u32*)(tr_arrows_Bitmap + ((TR_ARROWS_WIDTH * (TR_ARROWS_HEIGHT / 2)) / 2))
        }
    };


    init();

    //setup logo bitmap
    logo.x = (VideoWidth / 2) - (TR_LOGO_WIDTH / 2);
    logo.y = LOGO_Y_START_POS;
    logo.w = TR_LOGO_WIDTH;
    logo.h = TR_LOGO_HEIGHT;
    logo.bits = (u32*)tr_logo_Bitmap;

    //setup text bitmaps
    for (i = 0; i < SCROLLER_BMP; i++) {
        text[i].x = x;
        text[i].y = SCROLLER_Y_POSITION;
        text[i].w = BG_FONT_WIDTH;
        text[i].h = BG_FONT_HEIGHT;
        text[i].bits = (u32*)(tr_font_Bitmap + ((scroller[i] - 0x20)*(BG_FONT_WIDTH*BG_FONT_HEIGHT) / 2));
        x += SCROLLER_SPACE;
    }

    while (1) {
        // Logo Animation
        logo.y = (sin160[z] + LOGO_Y_START_POS);
        z += LOGO_MOVING_SPEED;
        if (z >= 160) z = 1;

        //VideoClear(COLOR_BLACK); // Not needed! The background will clear the screen for us
        BlitScreen(0, 0, tr_bg_Bitmap, TR_BG_WIDTH, TR_BG_HEIGHT); // Copy background to backbuffer
        BitmapBlitTransScreen(&logo, tr_logo_Bitmap[0]); // Blit the bitmap to backbuffer using upper left pixel(s) as transparency

        // Display Scroller
        for (i = 0; i < SCROLLER_BMP; i++) {
            text[i].x -= SCROLL_SPEED;
            if (text[i].x < (SCROLL_SPEED * 2)) { //if bitmap scrolls too far, move it to the end of the message, and give it the next character
                text[i].x += (SCROLLER_SPACE*SCROLLER_BMP);
                text[i].bits = (u32*)(tr_font_Bitmap + ((scroller[j] - 0x20)*(BG_FONT_WIDTH*BG_FONT_HEIGHT) / 2));
                j = ((j + 1) % stringlen);
            }
            BitmapBlitTransScreen(&text[i], tr_font_Bitmap[0]);
        }

        // Menu selection
        btn = PadDigitalDown(PAD_CHANNEL_0);
        if (btn & PAD_DIGITAL_UP) {
            menu_pos--;
            if (menu_pos < 0) menu_pos = 0;
            else mz = 0;
            if ((menu_pos - menu_scroll) < 0) menu_scroll--;
        }
        else if (btn & PAD_DIGITAL_DOWN) {
            menu_pos++;
            if (menu_pos > num_menus) menu_pos = num_menus;
            else mz = 0;
            if ((menu_pos - menu_scroll) > (MENU_NUM_DISPLAY - 1)) menu_scroll++;
        }

        if (btn & PAD_DIGITAL_A) mainmenu[menu_pos].option ^= 1; // Enable & Disable Options
        if (btn & PAD_DIGITAL_START) LoadDisc(); // Load DVD
//		if (btn & PAD_DIGITAL_Z) M_HOTRESET; // Reset Cube

        // Display Menu
        for (i = 0; i <= ((num_menus > (MENU_NUM_DISPLAY - 1)) ? (MENU_NUM_DISPLAY - 1) : num_menus); i++) {
            k = (i + menu_scroll);
            if (menu_pos == k) FontString((sin88[mz] + MENU_X_POSITION), (MENU_Y_POSITION + (i*MENU_V_DIFFRENCE)), mainmenu[k].str);
            else FontString(MENU_X_POSITION, (MENU_Y_POSITION + (i*MENU_V_DIFFRENCE)), mainmenu[k].str);
        }
        mz += menu_speed;
        if (mz >= 39) mz = 0;

        // Display Menu Arrows
        if ((num_menus > MENU_NUM_DISPLAY) && (!arrows_flash)) {
            if (menu_scroll) BitmapBlitTransScreen(&arrows[0], tr_arrows_Bitmap[0]);
            if ((menu_scroll + (MENU_NUM_DISPLAY - 1)) != num_menus) BitmapBlitTransScreen(&arrows[1], tr_arrows_Bitmap[0]);
        }
        arrows_flash ^= 1;

        // Display Options
        for (i = 0; i <= ((num_menus > (MENU_NUM_DISPLAY - 1)) ? (MENU_NUM_DISPLAY - 1) : num_menus); i++) {
            FontString(MENU_OPTION_X_POSITION, (MENU_Y_POSITION + (i*MENU_V_DIFFRENCE)), menuoptions[mainmenu[i + menu_scroll].option]);
        }

        VideoFlip(); //display screen updates!
    }
}
