#ifndef _DS_SHARED_MEMORY_H_
#define _DS_SHARED_MEMORY_H_


#include <cocos2d.h>
#include "base\ds_types.h"

USING_NS_CC;

class DsSharedMemory : public Ref
{
private:
	static DsSharedMemory * _instance;

	UBYTE* _directedAnimationTempMemory;
	UBYTE* _compositeAnimationTempMemory;
	UBYTE* _compositeAnimationTempMemory2;
	UBYTE* _tileImageTempMemory;



public:

	static DsSharedMemory * getInstance();
	DsSharedMemory();
	~DsSharedMemory();

	UBYTE* directedAnimationTempMemory();
	UBYTE* compositeAnimationTempMemory();
	UBYTE* compositeAnimationTempMemory2();
	UBYTE* tileImageTempMemory();

};


#endif