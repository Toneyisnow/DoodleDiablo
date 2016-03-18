#ifndef _DS_TILE_INDEXED_OBJECT_H_
#define _DS_TILE_INDEXED_OBJECT_H_


#include <cocos2d.h>
#include "..\..\base\ds_structs.h"

USING_NS_CC;

class DsTileIndexedObject : public Ref
{
protected:

	long  _main_index;
	long  _sub_index;
	long  _orientation;

public:

	static DsTileIndexedObject * generate(long main, long sub, long orientation);

	DsTileIndexedObject(long main, long sub, long orientation);
	DsTileIndexedObject();
	~DsTileIndexedObject();

	void setIdentity(DsTileIndexedObject *other);
	int getIdentityKey();

	long getMainIndex();
	long getSubIndex();
	long getOrientation();


	bool is_match(DsTileIndexedObject *other);
	bool is_match(long main, long sub, long orientation);

};

#endif