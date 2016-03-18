#include "ds_resource_object.h"
#include "ds_resource_storage.h"

DsResourceObject::DsResourceObject()
{
	_usageCount = 1;
}

DsResourceObject::~DsResourceObject()
{

}

void DsResourceObject::initFromStorage(char* filepath)
{
	_buffer = NULL;
	_buffer_len = 0;

	DsResourceStorage::load(filepath, &_buffer, &_buffer_len);
	_resourceKey = filepath;
	this->initializeData();

	free(_buffer);
	_buffer = NULL;
	_buffer_len = 0;
}

void DsResourceObject::initializeData()
{

}

void DsResourceObject::increase_usage()
{
	_usageCount++;
}

void DsResourceObject::decrease_usage()
{
	if (_usageCount > 0)
		_usageCount--;
}

bool DsResourceObject::no_longer_used()
{
	return (_usageCount <= 0);
}



