#ifndef _DS_TILE_IMAGE_H_
#define _DS_TILE_IMAGE_H_


#include <cocos2d.h>
#include "..\..\base\global_definition.h"
#include "..\..\base\ds_types.h"
#include "..\base\palette.h"
#include "..\base\ds_bitmap.h"
#include "ds_tile_sub_block.h"
#include "ds_tile_indexed_object.h"

USING_NS_CC;


class DsTileImage : public DsTileIndexedObject
{
private:

	static const int SUB_TILE_COUNT = 25;
	
	static int _subIndexTable[SUB_TILE_COUNT];
	DsTileSubBlock * _subBlocks[SUB_TILE_COUNT];

	Texture2D * _renderedTexture;
	
	DsBitMapData *_bitMapData;

	bool _hasRendered;

	/*
	UBYTE      unknown_a;
	UBYTE      unknown_b;
	UBYTE      unknown_c;
	UBYTE      unknown_d;
	*/
	// UBYTE      sub_tiles_flags[25];
	// int        zeros2[7];
	long       tiles_ptr;
	long       tiles_length;
	long       tiles_number;
	// int        zeros3[12];


	void draw_sub_tile_isometric(DsBitMapData * dst, int x0, int y0, UBYTE * data, int length);
	void draw_sub_tile_normal(DsBitMapData * dst, int x0, int y0, UBYTE * data, int length);

public:

	long       direction;
	DS_WORD       roof_y;
	UBYTE      sound;
	UBYTE      animated;
	long       size_y;
	long       size_x;
	// long       zeros1;
	
	long       rarity;

	DsTileImage();
	~DsTileImage();

	// Read the block from the stream
	void init_from_buffer(UBYTE * buffer, void * data);

	// Render the image from the sub tiles
	void render(const Palette * pal);

	Texture2D * getTexture();
	// SpriteFrame* getImage();

	bool hasRendered();

	DsTileSubBlock * getSubBlock(int t);
};


#endif