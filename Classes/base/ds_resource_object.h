#ifndef _RESOURCE_OBJECT_H_
#define _RESOURCE_OBJECT_H_


#include <cocos2d.h>
#include "memory_object.h"

USING_NS_CC;

class DsResourceObject : public MemoryObject
{
private:

	int _usageCount;
	int _lifeTimeSeconds;
	long _lastUsedTimestamp;


protected:

	char * _resourceKey;
	void * _buffer;
	long _buffer_len;

public:

	DsResourceObject();
	~DsResourceObject();

	void initFromStorage(char* filepath);

	// This should be implemented fromr child class
	void virtual initializeData();


	void increase_usage();
	void decrease_usage();
	bool no_longer_used();


};


#endif