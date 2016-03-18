#ifndef _DS_TILE_H_
#define _DS_TILE_H_


#include <cocos2d.h>
#include "ds_tile_cell.h"

USING_NS_CC;


class DsTile : public DsTileIndexedObject
{
private:

protected:

	DsTileCell * _cell;

	UBYTE prop1;
	UBYTE prop2;
	UBYTE prop3;
	UBYTE prop4;
	//int   bt_idx;
	UBYTE flags;

	
public:

	DsTile();
	~DsTile();

	virtual void set_prop(UBYTE *buffer);

	virtual bool find_matching_cell(Map<int, DsTileCell *>* cellDictionary);

	void set_cell(DsTileCell *c);
	DsTileCell* getCell();

};


class DsFloorTile : public DsTile
{
private:

public:

	virtual void set_prop(UBYTE *buffer);
};

class DsShadowTile : public DsTile
{
private:

public:

	virtual void set_prop(UBYTE *buffer);
};

class DsWallTile : public DsTile
{
private:
	
public:
	
	// UBYTE orientation;
	
	virtual void set_prop(UBYTE *buffer);
	virtual bool find_matching_cell(Map<int, DsTileCell *>* cellDictionary);

	void set_orientation(UBYTE or);
};


#endif