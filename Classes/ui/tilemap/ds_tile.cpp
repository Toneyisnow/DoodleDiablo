

#include "ds_tile.h"

DsTile::DsTile()
{
	_cell = NULL;
}

DsTile::~DsTile()
{
	_cell = NULL;
}

void DsTile::set_prop(UBYTE *buffer)
{
	this->prop1 = *buffer;
	this->prop2 = *(buffer + 1);
	this->prop3 = *(buffer + 2);
	this->prop4 = *(buffer + 3);

	_main_index = (prop3 >> 4) + ((prop4 & 0x03) << 4);
	_sub_index = prop2;
	_orientation = -1;
}

void DsTile::set_cell(DsTileCell *c)
{
	this->_cell = c;
}

DsTileCell* DsTile::getCell()
{
	return this->_cell;
}

bool DsTile::find_matching_cell(Map<int, DsTileCell *>* cellDictionary)
{
	if (this->prop1 == 0)
	    return false;

	int key = this->getIdentityKey();
	if (cellDictionary->at(key) != NULL)
	{
		this->set_cell(cellDictionary->at(key));
		return true;
	}
	else
	{
		this->set_cell(NULL);
		return false;
	}
}

//////////////////////////		DsWallTile		/////////////////////////////////////////////

void DsWallTile::set_orientation(UBYTE or)
{
	this->_orientation = (int)or;
}

void DsWallTile::set_prop(UBYTE * buffer)
{
	DsTile::set_prop(buffer);
}


bool DsWallTile::find_matching_cell(Map<int, DsTileCell *>* cellDictionary)
{
	if (this->_orientation == 3)
	{
		int key = DsTileIndexedObject::generate(this->_main_index, this->_sub_index, 4)->getIdentityKey();
		if (cellDictionary->at(key) != NULL)
		{
			this->set_cell(cellDictionary->at(key));
			return true;
		}
	}

	if (DsTile::find_matching_cell(cellDictionary))
	{
		return true;
	}

	// Trick for 18 and 19
	if (_orientation != 18 && _orientation != 19)
	{ 
		return false;
	}

	int orientation2 = (_orientation == 18) ? 19 : (_orientation == 19) ? 18 : _orientation;
	int key2 = DsTileIndexedObject::generate(_main_index, orientation2, _sub_index)->getIdentityKey();
	int key3 = DsTileIndexedObject::generate(_main_index, orientation2, 0)->getIdentityKey();

	if (cellDictionary->at(key2) != NULL)
	{
		this->set_cell(cellDictionary->at(key2));
		return true;
	}
	else if (cellDictionary->at(key3) != NULL)
	{
		this->set_cell(cellDictionary->at(key3));
		return true;
	}
	else
	{
		this->set_cell(NULL);
		return false;
	}
}

//////////////////////////		DsFloorTile		/////////////////////////////////////////////

void DsFloorTile::set_prop(UBYTE * buffer)
{
	DsTile::set_prop(buffer);
	_orientation = 0;
}



//////////////////////////		DsShadowTile		/////////////////////////////////////////////

void DsShadowTile::set_prop(UBYTE * buffer)
{
	DsTile::set_prop(buffer);
	_orientation = 13;
}
