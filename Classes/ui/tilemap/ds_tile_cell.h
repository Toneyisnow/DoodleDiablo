#ifndef _DS_TILE_CELL_H_
#define _DS_TILE_CELL_H_


#include <cocos2d.h>
#include "ds_tile_image.h"
#include "base\ds_structs.h"
#include "ds_tile_sub_block.h"

USING_NS_CC;

class DsTileCell : public DsTileIndexedObject
{
private:

	int _mapIndex;
	int _imageIndex;
	Vector<Texture2D *>* _tileTextureList;

	DsTileSubBlock * _subBlocks[25];

	// datas
	long      rarity;
	BLK_TYP_E type;
	int       zero_line;
	int       roof_y;

	// conflicts managment
	char      conflict;
	char      used_by_game;   // True / False
	char      used_by_editor; // True / False

	// animated tile
	long      curr_frame;
	int       updated;

	SpriteFrame* generateFrame(int index);

	// Get random texture according to the rarity
	SpriteFrame* generateRandomFrame();

public:


	DsTileCell(int mapIndex, int imageIndex, DsTileImage * image);
	DsTileCell();
	~DsTileCell();

	void addImage(DsTileImage *image);
	DsTileSubBlock * getSubBlock(int t);
	
	Sprite* createSprite();

};

#endif