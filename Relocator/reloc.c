/*==================================================**
* =      RELOC 2-The Better Way  © by LordDog      = *
* ================================================== *
*                                                    *
*  LordDog in Jan. / May / Jul. 2004.                *
*                                                    *
*  Version 2.04                                      *
*                                                    *
*  Histroy                                           *
*  =======                                           *
*  28.Jul.04  Adding Game Fix - And 2nd RL ID 0x300  *
*  28.Jul.04  Changing Fingerpringt (0x500)          *
*                                                    *
*  27.May.04  Adding FingerPrint to 0x500            *
*  24.May.04  Adding Filename for display moving file*
*  24.May.04  Move "Size Fix" after Open Relocated   *
*             Image. So no Data could be overwrite!  *
*  24.May.04  Internal Release of Reloc 2 Final      *
*                                                    *
*  23.May.04  Building Executeabe for W32 and Linux  *
*  23.May.04  Optimizing Code for W32 and Linux      *
*                                                    *
*  22.May.04  Internal Release of Reloc 2 Beta       *
*  22.May.04  Adding -n -r -d -f Option              *
*  22.May.04  Add Extraction of BI2, FST, Maindol    *
*             and Apploader to Options               *
*  22.May.04  Add Reloc 1 function to Option         *
*                                                    *
*  21.May.04  Internal Release of Reloc 2 Beta       *
*  21.May.04  Update to Reloc 2 function             *
*                                                    *
*  xx.Jan.04  Internal Release of Reloc 1 Beta       *
*  xx.Jan.04  Removing Metroid Bug Fix               *
*  xx.Jan.04  First Version                          *
*                                                    *
*  Win32 and Linux Compatible                        *
*  ==========================                        *
*  Linux: g++ RELOC.cpp (Change IS_LINUX from 0 to 1)*
*                                                    *
*  Win32: cl -GX RELOC.cpp  (Visual Studio 6)        *
*                                                    *
*****************************************************/

// NOTE:
// Fingerprint should be edit !  rcversion = pc_u32(0x520202) -=>> // 52 = R, 0202 = Version -> 2.02

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define IS_LINUX 0				// Switches: 0 = Windows | 1 = Linux 
#define BUF_MAX 1024000			// Copy Buffer
#define IMAGESIZE 1459978240	// Cube Image Size

#define RLVERSION   "2"			// Reloc Version
#define RLREVISION  "04"		// Reloc Revision
#define BINREVISION 0x0204		// Reloc Vesion as Binary 

// a few helpful data types ;)

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct __MYFILE {
    u32 filenamelength;
    u32 fileoffset;
    u32 filesize;
    char filename[256];
} MYFILE;

MYFILE myfile[65536];

u16 pc_u16(u16 gcn_u16)
{
    u8 *src, *dst;
    u16 i;
    src = (u8*)&gcn_u16;
    dst = (u8*)&i;
    dst[0] = src[1];
    dst[1] = src[0];
    return i;
}

u32 pc_u32(u32 gcn_u32)
{
    u8 *src, *dst;
    u32 i;
    src = (u8*)&gcn_u32;
    dst = (u8*)&i;
    dst[0] = src[3];
    dst[1] = src[2];
    dst[2] = src[1];
    dst[3] = src[0];
    return i;
}

int main(int argc, char *argv[])
{
    if (IS_LINUX == 1) { system("clear"); }
    else { system("cls"); }

    printf("Reloc %s.%s - The Better Way - StarCube\n", RLVERSION, RLREVISION);
    printf("======================================\n");

    if (argc < 3)
    {
        printf("Usage:  Reloc <Ripped Image> [Image name or Extract Options] -Options\n");
        printf("\nOptions are:\n============\n\n");
        printf(" -r     Relocate Image - Files will get new Position, FST will be touched\n");
        printf(" -f     Extract Original FST also\n");
        printf(" -d     Disable Debug/Progress Diplay Output\n");
        printf(" -n     Disable Image-Size-Fix (Image will be keep only needed size only)\n\n");
        printf(" -nofix Disable AutoFix Game Image (If Needed)\n\n");

        printf("\nExtract Options are:\n====================\n\n");
        printf(" -bi2   Extract BI2.bin\n");
        printf(" -md    Extract Main.Dol\n");
        printf(" -ap    Extract Apploader\n");
        printf(" -fst   Extract Original FST\n");

        printf("\n");
        printf("\n Screen-Chars: X = New File begin's\n               . = Data of File (X)\n               O = One File Relocated (-r Only!)\n\n");
        exit(1);
    }

    // Options
    int ScreenLog = 1; // Default: should be On
    int SizeFix = 1; // Default: should be On
    int NoFixGame = 0; // Default: should be Off
    int WriteFST = 0; // Default: should be Off
    int OldReloc = 0; // Default: should be Off
    int BI2 = 0; // Default: should be Off
    int MainDol = 0; // Default: should be Off
    int Appld = 0; // Default: should be Off
    int ExtFST = 0; // Default: should be Off

    for (int ai = 1; ai < argc; ai++)
    {
        if (!strcmp(argv[ai], "-d"))     ScreenLog = 0;
        if (!strcmp(argv[ai], "-n"))     SizeFix = 0;
        if (!strcmp(argv[ai], "-f"))     WriteFST = 1;
        if (!strcmp(argv[ai], "-r"))     OldReloc = 1;
        if (!strcmp(argv[ai], "-bi2"))   BI2 = 1;
        if (!strcmp(argv[ai], "-md"))    MainDol = 1;
        if (!strcmp(argv[ai], "-ap"))    Appld = 1;
        if (!strcmp(argv[ai], "-fst"))   ExtFST = 1;
        if (!strcmp(argv[ai], "-nofix")) NoFixGame = 1;
    }

    FILE *o_image, *r_image, *omisc; // Original - Relocated File - misc files

    if ((o_image = fopen(argv[1], "r+b")) == NULL)
    {
        fprintf(stderr, "Original Image could not be opened!\n");
        exit(1);
    }

    // ############################
    // ## Game Info's #############
    // ############################

    char writebuffer[BUF_MAX];
    char game_name[100];
    char game_code[4];
    char game_contry[12];
    char game_devcode[2];
    char game_developer[50];
    fseek(o_image, 0, SEEK_SET);
    fread(game_code, 4, 1, o_image);

    fseek(o_image, 4, SEEK_SET);
    fread(game_devcode, 2, 1, o_image);

    fseek(o_image, 32, SEEK_SET);
    fread(game_name, 100, 1, o_image);

    if (game_code[3] == 'P') strcpy(game_contry, "Europe (PAL)");
    if (game_code[3] == 'D') strcpy(game_contry, "Europe (PAL/GERMANY)");
    else if (game_code[3] == 'E') strcpy(game_contry, "USA (NTSC)");
    else if (game_code[3] == 'J') strcpy(game_contry, "Japan (NTSC)");
    rewind(o_image);

    if (!strncmp(game_devcode, "01", 2)) strcpy(game_developer, "Nintendo");
    if (!strncmp(game_devcode, "08", 2)) strcpy(game_developer, "Capcom");
    if (!strncmp(game_devcode, "41", 2)) strcpy(game_developer, "UbiSoft");
    if (!strncmp(game_devcode, "42", 2)) strcpy(game_developer, "Hudson Soft");
    if (!strncmp(game_devcode, "4Z", 2)) strcpy(game_developer, "Crave");
    if (!strncmp(game_devcode, "51", 2)) strcpy(game_developer, "Acclaim Entertainment");
    if (!strncmp(game_devcode, "5D", 2)) strcpy(game_developer, "Midway");
    if (!strncmp(game_devcode, "64", 2)) strcpy(game_developer, "Lucasarts / Factor5");
    if (!strncmp(game_devcode, "70", 2)) strcpy(game_developer, "Atari / Infogrames");
    if (!strncmp(game_devcode, "78", 2)) strcpy(game_developer, "THQ");
    if (!strncmp(game_devcode, "8P", 2)) strcpy(game_developer, "SEGA");
    if (!strncmp(game_devcode, "A4", 2)) strcpy(game_developer, "Konami");
    if (!strncmp(game_devcode, "AF", 2)) strcpy(game_developer, "Namco");
    if (!strncmp(game_devcode, "GC", 2)) strcpy(game_developer, "Square Enix");
    if (!strncmp(game_devcode, "FF", 2)) strcpy(game_developer, "GC-Image-Builder");

    printf("Game Name......: %s\n", game_name);
    printf("Game Serial....: DOL-%.3s-%s\n", game_code, game_contry);
    printf("Game Developer.: %s\n", game_developer);

    // MainDol
    u32 maindol;
    fseek(o_image, 1056, SEEK_SET);
    fread(&maindol, 4, 1, o_image);
    maindol = pc_u32(maindol);

    // FST-Entry
    u32 fstentry;
    fseek(o_image, 1060, SEEK_SET);
    fread(&fstentry, 4, 1, o_image);
    fstentry = pc_u32(fstentry);

    // FST-Size
    u32 fstlen;
    fseek(o_image, 1064, SEEK_SET);
    fread(&fstlen, 4, 1, o_image);
    fstlen = pc_u32(fstlen);

    // Check if patch is needed
    u16 needfix;
    int NoFixtmp = 0;
    fseek(o_image, 1098, SEEK_SET);
    fread(&needfix, 2, 1, o_image);
    needfix = pc_u16(needfix);
    if (needfix == 0x1FDC) NoFixtmp = 1;

    // Nr-Files
    u32 nrfiles;
    fseek(o_image, fstentry + 8, SEEK_SET);
    fread(&nrfiles, 4, 1, o_image);
    nrfiles = pc_u32(nrfiles);

    // Apploader Date
    char appdate[11];
    fseek(o_image, 9280, SEEK_SET);
    fread(&appdate, 11, 1, o_image);

    printf("\nImage Info:\n-----------\n");
    printf("Apploader.: %.10s\n", appdate);
    printf("Maindol...: %X			Files.....: %d\n", maindol, nrfiles - 1);
    printf("FST-Entry.: %X			FST-length: %d bytes\n\n", fstentry, fstlen);
    if (NoFixtmp == 1)
    {
        printf("GamePatch.: Needed			Status....: ");
        if (NoFixGame == 0)
        {
            printf("will be patched\n\n");
        }
        else
        {
            printf("Skipped\n\n");
        }
    }
    else
    {
        printf("GamePatch.: Not Needed");
    }

    /**********************************************
    * Writing Original FST                       *
    * this is for Debug Output / Feature         *
    **********************************************/
    if (WriteFST == 1)
    {
        char *miscfile;
        omisc = fopen("Original.fst", "wb");
        fseek(o_image, fstentry, SEEK_SET);
        fread(writebuffer, fstlen, 1, o_image);
        fwrite(writebuffer, fstlen, 1, omisc);
        fclose(omisc);
    }

     /**********************************************
      * Writing Misc Stuff                         *
      **********************************************/
    int eexxiitt = 0;

    if (BI2 == 1)
    {
        printf("Extracting: BI2.bin\n");
        omisc = fopen("Bi2.bin", "wb");
        fseek(o_image, 1088, SEEK_SET);
        fread(writebuffer, 8192, 1, o_image);
        fwrite(writebuffer, 8192, 1, omisc);
        fclose(omisc);
        eexxiitt = 1;
    }

    if (MainDol == 1)
    {
        printf("Extracting: Main.dol\n");
        omisc = fopen("Main.DOL", "wb");
        fseek(o_image, maindol, SEEK_SET);
        fread(writebuffer, fstentry - maindol, 1, o_image);
        fwrite(writebuffer, fstentry - maindol, 1, omisc);
        fclose(omisc);
        eexxiitt = 1;
    }

    if (Appld == 1)
    {
        printf("Extracting: Apploader.ldr\n");
        omisc = fopen("Apploader.ldr", "wb");
        fseek(o_image, 9280, SEEK_SET);
        fread(writebuffer, maindol - 9280, 1, o_image);
        fwrite(writebuffer, maindol - 9280, 1, omisc);
        fclose(omisc);
        eexxiitt = 1;
    }

    if (ExtFST == 1)
    {
        printf("Extracting: Original FST\n");
        omisc = fopen("Original.fst", "wb");
        fseek(o_image, fstentry, SEEK_SET);
        fread(writebuffer, fstlen, 1, o_image);
        fwrite(writebuffer, fstlen, 1, omisc);
        fclose(omisc);
        eexxiitt = 1;
    }
    if (eexxiitt == 1) { exit(0); }


    /**********************************************
    * Opening Relocation File                    *
    **********************************************/
    if ((r_image = fopen(argv[2], "wb")) == NULL)
    {
        fprintf(stderr, "Reloc Image could not be opened!\n");
        exit(1);
    }

    /**********************************************
     * Fixing Image Size                          *
     **********************************************/
    if (SizeFix == 1)
    {
        rewind(r_image);
        printf("\nCreatig %d Bytes (1,35GB)", IMAGESIZE);
        fseek(r_image, IMAGESIZE - 1, SEEK_SET);
        fwrite("", 1, 1, r_image);

        rewind(r_image);
    }

    /**********************************************
    * Done Opening Relocation File               *
    **********************************************/
    int counter, multipl, ssiizzee;
    ssiizzee = (fstlen + fstentry);
    multipl = ssiizzee / BUF_MAX;

    // Read/Writing Engine
    fseek(o_image, 0, SEEK_SET);
    for (counter = 0; counter < multipl; counter++)
    {
        fread(writebuffer, BUF_MAX, 1, o_image);
        fwrite(writebuffer, BUF_MAX, 1, r_image);
    }
    // Write the rest of needed size
    fread(writebuffer, ssiizzee - (BUF_MAX * (multipl)), 1, o_image);
    fwrite(writebuffer, ssiizzee - (BUF_MAX * (multipl)), 1, r_image);

    /**********************************************
    * Writing FingerPrint                        *
    **********************************************/
    int fixdone = 0;
    if (NoFixGame == 0)
    {
        int fixx = pc_u16(0x0000);
        fseek(r_image, 1098, SEEK_SET);
        fwrite(&fixx, 4, 1, r_image);
        rewind(r_image);
        fixdone = 1;
    }

    //int rcversion = pc_u32(0x0204);
    int rcversion = pc_u32(BINREVISION);

    rewind(r_image);
    fseek(r_image, 768, SEEK_SET);
    fwrite(&rcversion, 4, 1, r_image);
    rewind(r_image);

    rewind(r_image);
    fseek(r_image, 1280, SEEK_SET);
    fwrite(&rcversion, 4, 1, r_image);
    rewind(r_image);
    // Done Writing FingerPrint


    myfile[0].filenamelength = 0;
    myfile[0].fileoffset = 0;
    myfile[0].filesize = 0;

    // Prepare Reading File Offsets / File len / Nsmes	
    int fstcount;
    int tmpnamecnt = 0;
    fseek(o_image, fstentry + 12, SEEK_SET);

    u32 tmpreader;
    for (fstcount = 1; fstcount < nrfiles; fstcount++)
    {
        fread(&tmpreader, 4, 1, o_image);
        myfile[fstcount].filenamelength = pc_u32(tmpreader);

        fread(&tmpreader, 4, 1, o_image);
        myfile[fstcount].fileoffset = pc_u32(tmpreader);

        fread(&tmpreader, 4, 1, o_image);
        myfile[fstcount].filesize = pc_u32(tmpreader);

    }
    myfile[fstcount].filenamelength = fstlen - (nrfiles * 12), myfile[fstcount - 1].filenamelength;


    /**********************************************
     * Start Getting FileNames (Display Only)     *
     **********************************************/
    char chrreader;
    int posa = 0, posb = 0; // posa

    fseek(o_image, fstentry + (12 * (nrfiles)), SEEK_SET);
    for (fstcount = 1; fstcount < nrfiles; fstcount++)
    {
        if (myfile[fstcount].filenamelength >= 0x1000000) { posa = myfile[fstcount].filenamelength - 0x1000000; }
        else { posa = myfile[fstcount].filenamelength; }
        if (myfile[fstcount + 1].filenamelength >= 0x1000000) { posb = myfile[fstcount + 1].filenamelength - 0x1000000; }
        else { posb = myfile[fstcount + 1].filenamelength; }
        fread(myfile[fstcount].filename, 1, (posb - posa), o_image);
    }

     /**********************************************
      * Start Adding Files to new Image            *
      **********************************************/
    printf("\n");
    long NeedSpace = 0;
    for (fstcount = 1; fstcount < nrfiles; fstcount++)
    {
        if (ScreenLog == 1) printf("\n%s: ", myfile[fstcount].filename);

        if (myfile[fstcount].fileoffset >= (fstlen + fstentry))
        {
            NeedSpace += myfile[fstcount].filesize;
            ssiizzee = myfile[fstcount].filesize;
            multipl = ssiizzee / BUF_MAX;

            // Read/Writing Engine
            fseek(o_image, myfile[fstcount].fileoffset, SEEK_SET);

            // NEW !!
            if (OldReloc == 0) { fseek(r_image, myfile[fstcount].fileoffset, SEEK_SET); }
            else { fseek(o_image, myfile[fstcount].fileoffset, SEEK_SET); }


            for (counter = 0; counter < multipl; counter++)
            {
                fread(writebuffer, BUF_MAX, 1, o_image);
                fwrite(writebuffer, BUF_MAX, 1, r_image);
                strcpy(writebuffer, "");
                if (ScreenLog == 1) printf(".");
            }
            // Write the rest of needed size
            fread(writebuffer, ssiizzee - (BUF_MAX * (multipl)), 1, o_image);
            fwrite(writebuffer, ssiizzee - (BUF_MAX * (multipl)), 1, r_image);
            strcpy(writebuffer, "");
            if (ScreenLog == 1) printf(".");
        }
    }

     /**********************************************
      * Start Fixing Offsets - Only for -r Option  *
      **********************************************/
    if (OldReloc == 1)
    {
        int totalsize = (fstlen + fstentry);
        int pos;
        rewind(r_image);

        pos = fstentry + 16;
        int fuckit;
        for (fstcount = 1; fstcount < nrfiles; fstcount++)
        {
            fseek(r_image, pos, SEEK_SET);

            if (myfile[fstcount].fileoffset >= (fstlen + fstentry))
            {
                fuckit = pc_u32(totalsize);
                fwrite(&fuckit, 4, 1, r_image);
                totalsize = (totalsize + myfile[fstcount].filesize);
                if (ScreenLog == 1) printf("O");
            }

            pos = pos + 12;
        }
    }

    printf("\n\n\nStatistics\n----------\n");
    printf("Plain Data.: %d bytes (%d mb)\n", NeedSpace, (NeedSpace / 1024 / 1000));
    printf("Garbage....: %d bytes (%d mb) ignored\n", (IMAGESIZE - NeedSpace), (IMAGESIZE - NeedSpace) / 1024 / 1000);

    if (fixdone == 1)
    {
        printf("\nNote.......: Image has been Patched - In some Cases the Game may not Work!\n");
    }

    printf("\nAll Done!\n\n");
    fclose(o_image);
    fclose(r_image);

    return 0;
}
