#include "ds_tile_indexed_object.h"

DsTileIndexedObject * DsTileIndexedObject::generate(long main, long sub, long orientation)
{
	DsTileIndexedObject *o = new DsTileIndexedObject(main, sub, orientation);
	o->autorelease();
	return o;
}

DsTileIndexedObject::DsTileIndexedObject(long main, long sub, long orientation)
{
	this->_main_index = main;
	this->_sub_index = sub;
	this->_orientation = orientation;
}

DsTileIndexedObject::DsTileIndexedObject()
{

}

DsTileIndexedObject::~DsTileIndexedObject()
{

}

long DsTileIndexedObject::getMainIndex()
{
	return this->_main_index;
}

long DsTileIndexedObject::getSubIndex()
{
	return this->_sub_index;
}

long DsTileIndexedObject::getOrientation()
{
	return this->_orientation;
}


void DsTileIndexedObject::setIdentity(DsTileIndexedObject *other)
{
	this->_main_index = other->getMainIndex();
	this->_sub_index = other->getSubIndex();
	this->_orientation = other->getOrientation();
}

int DsTileIndexedObject::getIdentityKey()
{
	return (this->_main_index * 1000 + this->_sub_index) * 100 + this->_orientation;
}

bool DsTileIndexedObject::is_match(DsTileIndexedObject *other)
{
	return this->getIdentityKey() == other->getIdentityKey();
}

bool DsTileIndexedObject::is_match(long main, long sub, long orientation)
{
	DsTileIndexedObject *other = generate(main, sub, orientation);
	return is_match(other);
}
