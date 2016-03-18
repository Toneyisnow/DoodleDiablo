#ifndef _MEMORY_OBJECT_H_
#define _MEMORY_OBJECT_H_


#include <cocos2d.h>

USING_NS_CC;

class MemoryObject : public Ref
{
private:

	int _memory_in_byte;

protected:
	void claim_memory_usage(int bt);
	void clear_memory_usage();

public:

	MemoryObject();
	virtual ~MemoryObject();


	
	int get_memory_used();

};


#endif