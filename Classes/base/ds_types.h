#ifndef _DSTYPES_H_
#define _DSTYPES_H_

#define FALSE  0
#define TRUE  -1

#define DCC_MAX_DIR    32
#define DCC_MAX_FRAME 256

#define DCC_MAX_PB_ENTRY 85000

typedef unsigned char      UBYTE;
typedef short int          DS_WORD;
typedef unsigned short int UWORD;
typedef unsigned long      UDWORD;

typedef struct
{
	int x0;
	int y0;
	int width;
	int height;
	UBYTE  ** data;
} BITMAP_DATA;


#endif