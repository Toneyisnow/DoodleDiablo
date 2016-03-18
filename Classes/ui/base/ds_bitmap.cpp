
#include "ds_bitmap.h"
#include <stdio.h>
#include <string>

int DsBitMapData::referenceCount = 0;
int DsBitMapData::allocatedSize = 0;
int DsBitMapData::destructCount = 0;
int DsBitMapData::deallocatedSize = 0;

DsBitMapData::DsBitMapData(bool needDispose)
{
	this->needDisposeData = needDispose;
	referenceCount++;
}

DsBitMapData::~DsBitMapData()
{
	destructCount++;
	if (data != NULL)
	{
		if (needDisposeData)
		{
			deallocatedSize += height * width;
			
			for (int y = 0; y < height; y++)
			{
				if (data[y] != NULL)
				{
					delete[] data[y];
					data[y] = NULL;
				}
			}
		}

		delete[] data;
		data = NULL;
	}
}

DsBitMapData * DsBitMapData::create_bitmap(int w, int h)
{
	allocatedSize += w * h;
	
	DsBitMapData * bitMap = new DsBitMapData(true);
	bitMap->width = w;
	bitMap->height = h;

	bitMap->data = (UBYTE **)malloc(bitMap->height * sizeof(UBYTE *));
	for (int j = 0; j < bitMap->height; j++)
	{
		bitMap->data[j] = (UBYTE *)malloc(bitMap->width * sizeof(UBYTE));
		memset(bitMap->data[j], 0, bitMap->width * sizeof(UBYTE));
	}

	return bitMap;
}

DsBitMapData * DsBitMapData::create_sub_bitmap(DsBitMapData * source, int x0, int y0, int w, int h)
{
	// DsBitMapData * data = (DsBitMapData *)malloc(sizeof(DsBitMapData));
	DsBitMapData * data = new DsBitMapData(false);
	data->width = w;
	data->height = h;

	data->data = (UBYTE **)malloc(data->height * sizeof(UBYTE *));
	for (int j = 0; j < data->height; j++)
	{
		data->data[j] = source->data[j + y0] + x0 * sizeof(UBYTE);
	}

	return data;
}

DsBitMapData * DsBitMapData::clone_bitmap(DsBitMapData * source)
{
	allocatedSize += source->width * source->height;

	DsBitMapData * data = new DsBitMapData(true);
	//DsBitMapData * data = (DsBitMapData *)malloc(sizeof(DsBitMapData));

	if (data == NULL)
	{
		return NULL;
	}

	data->width = source->width;
	data->height = source->height;

	data->data = (UBYTE **)malloc(data->height * sizeof(UBYTE *));
	for (int j = 0; j < data->height; j++)
	{
		data->data[j] = (UBYTE *)malloc(data->width * sizeof(UBYTE));
		for (int i = 0; i < data->width; i++)
		{
			data->data[j][i] = source->data[j][i];
		}
	}

	return data;
}

void DsBitMapData::blit(DsBitMapData * source, DsBitMapData * dest, int sourceX, int sourceY, int destX, int destY, int width, int height)
{
	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
		{
			if (destX + i >= dest->width || destY + j >= dest->height)
			{
				continue;
			}

			dest->data[destY + j][destX + i] = source->data[sourceY + j][sourceX + i];
		}
}

void DsBitMapData::putpixel(int x, int y, UBYTE color)
{
	if (x < 0 || x >= width || y < 0 || y >= height)
		return;

	data[y][x] = color;
}

void DsBitMapData::destroy_bitmap(DsBitMapData * val)
{
	if (val->data != NULL)
	{
		for (int y = 0; y < val->height; y++)
		{
			free(val->data[y]);
			val->data[y] = NULL;
		}

		free(val->data);
		val->data = NULL;
	}

	free(val);
}

void DsBitMapData::clear_bitmap()
{
	for (int j = 0; j < height; j++)
		for (int i = 0; i < width; i++)
		{
			data[j][i] = 0;
		}
}

void DsBitMapData::clear_to_color(UBYTE color)
{
	for (int j = 0; j < height; j++)
		for (int i = 0; i < width; i++)
		{
			data[j][i] = color;
		}
}

int DsBitMapData::getWidth() const
{
	return width;
}

int DsBitMapData::getHeight() const
{
	return height;
}

UBYTE DsBitMapData::getByte(int x, int y) const
{
	return data[y][x];
}

void DsBitMapData::copy(const DsBitMapData *bitMap)
{
	this->width = bitMap->width;
	this->height = bitMap->height;
	this->data = bitMap->data;
}