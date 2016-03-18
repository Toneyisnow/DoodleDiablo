#include "ds_tile_image.h"
#include "ui\base\ds_bitmap.h"
#include "base\ds_types.h"
#include "ui\base\palette.h"
#include "base\ds_shared_memory.h"

int DsTileImage::_subIndexTable[25] = { 20, 21, 22, 23, 24,
15, 16, 17, 18, 19,
10, 11, 12, 13, 14,
5, 6, 7, 8, 9,
0, 1, 2, 3, 4 };

DsTileImage::DsTileImage()
{
	_bitMapData = NULL;
	_renderedTexture = NULL;
	for (int t = 0; t < SUB_TILE_COUNT; t++)
	{
		this->_subBlocks[t] = NULL;
	}

	_hasRendered = false;
}

DsTileImage::~DsTileImage()
{
	for (int t = 0; t < SUB_TILE_COUNT; t++)
	{
		if (this->_subBlocks[t] != NULL)
		{
			this->_subBlocks[t]->release();
			this->_subBlocks[t] = NULL;
		}
	}
}

void DsTileImage::init_from_buffer(UBYTE * buffer, void * data)
{
	this->direction = *(long *)buffer;
	this->roof_y = *(DS_WORD *)(buffer + 4);
	this->sound = *(UBYTE *)(buffer + 6);
	this->animated = *(UBYTE *)(buffer + 7);
	this->size_y = *(long *)(buffer + 8);
	this->size_x = *(long *)(buffer + 12);
	// skip 4 bytes : zeros1
	this->_orientation = *(long *)(buffer + 20);
	this->_main_index = *(long *)(buffer + 24);
	this->_sub_index = *(long *)(buffer + 28);
	this->rarity = *(long *)(buffer + 32);
	// skip 4 bytes : unknown_a thru unknown_d
	for (int t = 0; t < SUB_TILE_COUNT; t++)
	{
		//this->_subBlocks[_subIndexTable[t]] = new DsTileSubBlock();
		// this->_subBlocks[_subIndexTable[t]]->read_data(buffer + 40 + t);
		//this->_subBlocks[_subIndexTable[t]]->set_flag(buffer + 40 + t);

		this->_subBlocks[t] = new DsTileSubBlock();
		this->_subBlocks[t]->set_flag(buffer + 40 + t);
	}
		
	// skip 7 bytes : zeros2
	this->tiles_ptr = *(long *)(buffer + 72);
	this->tiles_length = *(long *)(buffer + 76);
	this->tiles_number = *(long *)(buffer + 80);
	// skip 12 bytes : zeros3


	int w = size_x;
	if ((_orientation == 10) || (_orientation == 11))
		w = 160; // set it to 160 because we'll draw infos over it later
	int h = -size_y;

	// adjustment (which y line in the bitmap is the zero line ?)

	// by default, when orientation > 15 : lower wall
	int y_add = 96;
	if ((_orientation == 0) || (_orientation == 15)) // floor or roof
	{
		if (size_y)
		{
			size_y = -80;
			h = 80;
			y_add = 0;
		}
	}
	else if (_orientation < 15) // upper wall, shadow, special
	{
		if (size_y)
		{
			size_y += 32;
			h -= 32;
			y_add = h;
		}
	}

	// anti-bug (for empty block)
	if ((w == 0) || (h == 0))
	{
		return;
	}

	// normal block (non-empty)
	_bitMapData = DsBitMapData::create_bitmap(w, h);
	if (_bitMapData == NULL)
	{
		//sprintf(tmp_str, "dt1_all_zoom_make(), can't make a bitmap "
		//	"of %i * %i pixels\n", w, h);
		/// ds1edit_error(tmp_str);
	}
	// tmp_bmp->clear_bitmap();

	// draw sub-tiles in this bitmap
	for (int s = 0; s < this->tiles_number; s++) // for each sub-tiles
	{
		// get the sub-tile info
		/// this->dt1_fill_subt(&st_ptr, b_ptr->tiles_ptr, s);
		UBYTE * st_ptr = (UBYTE *)data + this->tiles_ptr + (20 * s);
		DS_WORD x_pos = *(DS_WORD *)st_ptr;
		DS_WORD y_pos = *(DS_WORD *)(st_ptr + 2);
		// skip 2 bytes : unknown1
		UBYTE x_grid = *(UBYTE *)(st_ptr + 6);
		UBYTE y_grid = *(UBYTE *)(st_ptr + 7);
		DS_WORD format = *(DS_WORD *)(st_ptr + 8);
		long length = *(long *)(st_ptr + 10);
		// skip 2 bytes : unknown2
		long data_offset = *(long *)((UBYTE *)st_ptr + 16);

		// get infos
		int x0 = x_pos;
		int y0 = y_add + y_pos;
		UBYTE * dat = (UBYTE *)((UBYTE *)data + tiles_ptr + data_offset);

		// draw the sub-tile
		if (format == 0x0001)
			this->draw_sub_tile_isometric(_bitMapData, x0, y0, dat, length);
		else
			this->draw_sub_tile_normal(_bitMapData, x0, y0, dat, length);
	}

	_hasRendered = false;
}

void DsTileImage::render(const Palette * pal)
{
	if (_bitMapData == NULL || _hasRendered)
	{
		return;
	}

	if (_renderedTexture != NULL)
	{
		_renderedTexture->release();
		_renderedTexture = NULL;
	}

	// make zoom from the bitmap, for each zoom
	int width = _bitMapData->getWidth();
	int height = _bitMapData->getHeight();
	//Color4B * data = new Color4B[500 * 200];
	UBYTE* data2 = DsSharedMemory::getInstance()->tileImageTempMemory();

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			UBYTE b = _bitMapData->getByte(i, j);
			int index = j * width + i;
			if (index >= 500 * 200)
				break;

			if (b != 0)
			{
				int colorIndex = (int)b;
				if (colorIndex < 256 && colorIndex >= 0)
				{
					RGB clr = pal->getColor(colorIndex);
					//data[index] = Color4B(clr.r * 4, clr.g * 4, clr.b * 4, 255);
					data2[index * 2 + 1] = (UBYTE)((clr.r / 16) * 16 + (clr.g / 16));
					data2[index * 2] = (UBYTE)((clr.b / 16) * 16 + 15);
				}
				else
				{
					//data[index] = Color4B(0, 0, 0, 0);
					data2[index * 2] = data2[index * 2 + 1] = 0;
				}
			}
			else
			{
				//data[index] = Color4B(0, 0, 0, 0);
				data2[index * 2] = data2[index * 2 + 1] = 0;
			}
		}
	}

	_renderedTexture = new Texture2D();
	_renderedTexture->initWithData(data2, sizeof(Color4B) * width * height / 2, kCCTexture2DPixelFormat_RGBA4444, width, height, CCSize(width, height));

	_bitMapData->release();
	_bitMapData = NULL;

	_hasRendered = true;
}

// ==========================================================================
// draw a 3d-isometric sub-tile
void DsTileImage::draw_sub_tile_isometric(DsBitMapData * dst, int x0, int y0, UBYTE * data, int length)
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
void DsTileImage::draw_sub_tile_normal(DsBitMapData * dst, int x0, int y0, UBYTE * data, int length)
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

Texture2D * DsTileImage::getTexture()
{
	return this->_renderedTexture;
}

DsTileSubBlock * DsTileImage::getSubBlock(int t)
{
	if (t < 0 || t > 25)
		return NULL;

	return this->_subBlocks[t];
}

bool DsTileImage::hasRendered()
{
	return _hasRendered;
}
