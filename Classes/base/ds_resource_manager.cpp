#include "ds_resource_manager.h"


DsResourceManager::DsResourceManager()
{
	_objectMap = new Map<std::string, DsResourceObject*>();
}

DsResourceManager::~DsResourceManager()
{
	_objectMap->clear();
	delete(_objectMap);
}

void DsResourceManager::insert(std::string key, DsResourceObject* obj)
{
	_objectMap->insert(key, obj);
}

bool DsResourceManager::contains(std::string key)
{
	return (_objectMap->at(key) != NULL);
}

DsResourceObject* DsResourceManager::load(std::string key)
{
	_objectMap->at(key)->increase_usage();
	return _objectMap->at(key);
}

void DsResourceManager::unload(std::string key)
{
	_objectMap->at(key)->decrease_usage();
}

