
#ifndef _DS_BITMAP_H_
#define _DS_BITMAP_H_

#include <cocos2d.h>

#include "..\..\base\ds_types.h"

USING_NS_CC;

class DsBitMapData : public Ref
{
private:

	int width;
	int height;
	UBYTE  ** data;
	bool needDisposeData;

public:

	static int referenceCount;
	static int destructCount;
	static int allocatedSize;
	static int deallocatedSize;

	DsBitMapData(bool needDispose);
	~DsBitMapData();
	static DsBitMapData * create_bitmap(int w, int h);
	static DsBitMapData * create_sub_bitmap(DsBitMapData * source, int x0, int y0, int w, int h);
	static DsBitMapData * clone_bitmap(DsBitMapData * source);
	static void blit(DsBitMapData * source, DsBitMapData * dest, int sourceX, int sourceY, int destX, int destY, int width, int height);
	static void destroy_bitmap(DsBitMapData * val);

	void putpixel(int x, int y, UBYTE color);
	void clear_bitmap();
	void clear_to_color(UBYTE color);

	int getWidth() const;
	int getHeight() const;
	UBYTE getByte(int x, int y) const;

	void copy(const DsBitMapData *bitMap);
};


#endif