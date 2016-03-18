#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "cocos2d.h"

#include "ds_tile_map.h"
#include "base\ds_resource_storage.h"

USING_NS_CC;


//int DsTileMap::ZM_MAX = 5;
//int DsTileMap::FILE_MAX = DT1_MAX;

DsTileMap::DsTileMap()
{

}

DsTileMap::~DsTileMap()
{

}

DsTileMap* DsTileMap::load(const char * filename)
{
	char file[255];
	sprintf(file, "%s%s", TILE_MAP_RELATIVE_PATH, filename);

	DsTileMap *tm = new DsTileMap();
	tm->initFromStorage(file);
	tm->autorelease();
	
	return tm;
}

void DsTileMap::debug()
{
	for (int i = 0; i < this->getBlockCount(); i++)
	{
		DsTileImage *image = this->_blocks[i];
		log("Block %d, main(%d), sub(%d), orientation(%d).", i, image->getMainIndex(), image->getSubIndex(), image->getOrientation());
	}
}

// ==========================================================================
// fill / make all the datas of 1 dt1
void DsTileMap::initializeData()
{
	void * ptr = _buffer;
	int  size;
	char tmp[100];

	if (ptr == NULL)
		return;
	this->x1 = *(long *)ptr;
	this->x2 = *(long *)((UBYTE *)ptr + 4);
	this->block_num = *(long *)((UBYTE *)ptr + 268);
	this->bh_start = *(long *)((UBYTE *)ptr + 272);

	// debug
	/////printf("struct data of glb_dt1[%i] :\n", i);
	log("   x1        = %li\n", this->x1);
	log("   x2        = %li\n", this->x2);
	log("   block_num = %li\n", this->block_num);
	log("   bh_start  = 0x%0lX\n", this->bh_start);

	// blocks
	UBYTE *bptr = (UBYTE *)_buffer + this->bh_start;
	for (int block = 0; block < this->block_num; block++)
	{
		this->_blocks[block] = new DsTileImage();
		this->_blocks[block]->init_from_buffer(bptr, _buffer);
		bptr += 96;
	}

	_hasRendered = false;
}

void DsTileMap::render(const Palette * pal)
{
	if (_hasRendered)
		return;

	for (int block = 0; block < this->block_num; block++)
	{
		this->_blocks[block]->render(pal);
	}

	_hasRendered = true;
}

bool DsTileMap::hasRendered()
{
	return _hasRendered;
}

DsTileImage * DsTileMap::getBlock(int index)
{
	return this->_blocks[index];
}

int DsTileMap::getBlockCount()
{
	return this->block_num;
}

/*
// ==========================================================================
// draw a 3d-isometric sub-tile
void DsTileMap::draw_sub_tile_isometric(DsBitMapData * dst, int x0, int y0, UBYTE * data, int length)
{
	UBYTE * ptr = data;
	int   x, y = 0, n,
		xjump[15] = { 14, 12, 10, 8, 6, 4, 2, 0, 2, 4, 6, 8, 10, 12, 14 },
		nbpix[15] = { 4, 8, 12, 16, 20, 24, 28, 32, 28, 24, 20, 16, 12, 8, 4 };

	// 3d-isometric subtile is 256 bytes, no more, no less
	if (length != 256)
		return;

	// draw
	while (length > 0)
	{
		x = xjump[y];
		n = nbpix[y];
		length -= n;
		while (n)
		{
			dst->putpixel(x0 + x, y0 + y, *ptr);
			ptr++;
			x++;
			n--;
		}
		y++;
	}
}


// ==========================================================================
// draw a normal sub-tile (can be transparent, so there are "jump" coded)
void DsTileMap::draw_sub_tile_normal(DsBitMapData * dst, int x0, int y0, UBYTE * data, int length)
{
	UBYTE * ptr = data, b1, b2;
	int   x = 0, y = 0;

	// draw
	while (length > 0)
	{
		b1 = *ptr;
		b2 = *(ptr + 1);
		ptr += 2;
		length -= 2;
		if (b1 || b2)
		{
			x += b1;
			length -= b2;
			while (b2)
			{
				dst->putpixel(x0 + x, y0 + y, *ptr);
				ptr++;
				x++;
				b2--;
			}
		}
		else
		{
			x = 0;
			y++;
		}
	}
}
*/
