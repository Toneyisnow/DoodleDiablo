#include "memory_object.h"

MemoryObject::MemoryObject()
{
	_memory_in_byte = 0;
}

MemoryObject::~MemoryObject()
{

}

void MemoryObject::clear_memory_usage()
{
	_memory_in_byte = 0;
}

void MemoryObject::claim_memory_usage(int bt)
{
	_memory_in_byte += bt;
}

int MemoryObject::get_memory_used()
{
	return _memory_in_byte;
}
