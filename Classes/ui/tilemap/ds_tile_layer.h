#ifndef _DS_TILE_LAYER_H_
#define _DS_TILE_LAYER_H_


#include <cocos2d.h>
#include "ds_tile.h"

USING_NS_CC;

template <class TILE>
class DsTileLayer : public Ref
{
private:

	//int _currentTileIndex;
public:

	int _width;
	int _height;
	int _mask;
	TILE** _tiles;
	UBYTE _layer_mask;

	
public:

	DsTileLayer<TILE>(int w, int h)
	{
		this->_width = w;
		this->_height = h;

		this->_tiles = new TILE*[w*h];
		for (int j = 0; j < h; j++)
		{
			for (int i = 0; i < w; i++)
			{
				this->_tiles[i + j * w] = new TILE();
			}
		}
	}

	~DsTileLayer<TILE>()
	{

	}

	//void initTileIterator();
	//void read_prop(UBYTE *buffer);

	TILE * getTile(int w, int h)
	{
		if (w < 0 || w >= this->_width || h < 0 || h >= this->_height)
		{
			return NULL;
		}

		return this->_tiles[w + this->_width * h];
	}


};

#endif