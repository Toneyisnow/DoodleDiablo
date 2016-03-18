#include "ds_shared_memory.h"
#include "base\ds_types.h"


DsSharedMemory *DsSharedMemory::_instance = NULL;

DsSharedMemory * DsSharedMemory::getInstance()
{
	if (_instance == NULL)
	{
		_instance = new DsSharedMemory();
	}

	return _instance;
}

DsSharedMemory::DsSharedMemory()
{
	_compositeAnimationTempMemory = new UBYTE[512 * 255];
	_compositeAnimationTempMemory2 = new UBYTE[255 * 255];
	_directedAnimationTempMemory = new UBYTE[255 * 255 * 2];
	_tileImageTempMemory = new UBYTE[500 * 200 * 2];

}



DsSharedMemory::~DsSharedMemory()
{

}


UBYTE* DsSharedMemory::compositeAnimationTempMemory()
{
	return this->_compositeAnimationTempMemory;
}
UBYTE* DsSharedMemory::compositeAnimationTempMemory2()
{
	return this->_compositeAnimationTempMemory2;
}


UBYTE* DsSharedMemory::directedAnimationTempMemory()
{
	return this->_directedAnimationTempMemory;
}

UBYTE* DsSharedMemory::tileImageTempMemory()
{
	return this->_tileImageTempMemory;
}

