#include "ds_tile_layer.h"


/*
template <class TILE>
DsTileLayer<TILE>::DsTileLayer<TILE>(int w, int h)
{
	this->_width = w;
	this->_height = h;

	this->_tiles = new TILE*[w*h];
	for (int j = 0; j < h; j++)
		for (int i = 0; i < w; i++)
		{
			this->_tiles[i + j * w] = new TILE();
		}
}

template <class TILE>
DsTileLayer<TILE>::~DsTileLayer<TILE>()
{
}

template <class TILE>
TILE * DsTileLayer<TILE>::getTile(int w, int h)
{
	if (w < 0 || w >= this->_width || h < 0 || h >= this->_height)
	{
		return NULL;
	}

	return this->_tiles[w + this->_width * h];
}
*/

/*
void DsTileLayer<DsTile>::initTileIterator()
{
	_currentTileIndex = 0;

}

void DsTileLayer<DsTile>::read_prop(UBYTE *buffer)
{
	if (_currentTileIndex >= 255)
	{
		return;
	}

	this->_tiles[_currentTileIndex]->
}


*/