#ifndef _DS_IMAGE_H_
#define _DS_IMAGE_H_


#include <cocos2d.h>
#include "ds_bitmap.h"
#include "palette.h"
#include "base\memory_object.h"

USING_NS_CC;

class DsImage : public MemoryObject
{
private:

	// DsBitMapData * _data;
	//int _sizeInByte;

	int _height;
	int _width;

	float _boxminX;
	float _boxminY;

	int _dataLength;
	UBYTE * _data;

	int _readerPointer;
	UBYTE _readCount;

public:

	DsImage(DsBitMapData *data);
	~DsImage();

	void setBoxAnchor(float x, float y);
	Vec2 getBoxAnchor();
	Size getOriginalSizeInPixels();

	void resetReader();
	UBYTE readNext();

	SpriteFrame* render(Palette * palette);
	SpriteFrame* render();		// Render the black and white image


};


#endif