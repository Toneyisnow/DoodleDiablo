#ifndef _RESOURCE_MANAGER_H_
#define _RESOURCE_MANAGER_H_


#include <cocos2d.h>
#include "ds_resource_object.h"

USING_NS_CC;

class DsResourceManager : public Ref
{
private:

	Map<std::string, DsResourceObject*> * _objectMap;
	int _wipeInterval;

public:

	DsResourceManager();
	~DsResourceManager();

	void insert(std::string key, DsResourceObject* obj);
	bool contains(std::string key);
	DsResourceObject* load(std::string key);
	void unload(std::string key);

};


#endif