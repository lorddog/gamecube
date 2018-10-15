OBJECTS	= crt0.o main.o

EURLIB	= .
EABI	= C:/devkitcube/powerpc-eabi-elf
RM	= rm
AS	= powerpc-eabi-elf-as
CC	= powerpc-eabi-elf-gcc
LD	= powerpc-eabi-elf-ld
STRIP	= powerpc-eabi-elf-strip
OBJDUMP	= powerpc-eabi-elf-objdump

LFLAGS	= -s -Ttext 0x81300000 -L${EABI}/lib/
#LFLAGS	= -s -Ttext 0x80600000 -L${EABI}/lib/
LIBFLAGS= -leur
CFLAGS	= -I${EURLIB}/include/ -I${EABI}/include/ -O2

NAME	= trainer


all: ${NAME}.dol

clean:
	${RM} ${OBJECTS} ${NAME}.dol ${NAME}.elf ${NAME}.bin


${NAME}.dol: ${NAME}.elf
#	${OBJDUMP} -S ${NAME}.elf >${NAME}.asm
	${STRIP} --strip-unneeded ${NAME}.elf
	bin/doltool -d ${NAME}.elf
	${RM} ${NAME}.elf

${NAME}.elf: ${OBJECTS}
	${LD} ${LFLAGS} -o $@ $^ ${LIBFLAGS}

crt0.o: crt0.s
	${AS} -o $@ crt0.s

main.o: main.c tr_logo.raw.c tr_bg.raw.c tr_font.raw.c tr_menufont.raw.c tr_arrows.raw.c trainvalues.c code_engine.h
	${CC} -c ${CFLAGS} -o $@ main.c
