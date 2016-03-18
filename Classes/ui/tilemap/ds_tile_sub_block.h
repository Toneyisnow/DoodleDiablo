
#ifndef _DS_TILE_SUB_BLOCK_H_
#define _DS_TILE_SUB_BLOCK_H_


#include <cocos2d.h>
#include "..\..\base\global_definition.h"
#include "..\..\base\ds_types.h"

USING_NS_CC;


class DsTileSubBlock : public Ref
{
private:

	UBYTE _flag;

	DS_WORD  x_pos;
	DS_WORD  y_pos;
	//   WORD  unknown1;
	int   x_grid;
	int   y_grid;
	DS_WORD  format;
	long  length;
	//   WORD  unknown2;
	long  data_offset;

public:

	DsTileSubBlock();
	~DsTileSubBlock();
	void set_flag(UBYTE * ptr);
	void read_data(UBYTE * ptr);

	bool is_block_walk();
	bool is_block_teleport();
};

#endif