#ifndef __DEFINITION_LIBRARY_H_
#define __DEFINITION_LIBRARY_H_

#include <stdlib.h>
#include <string.h>
#include <cocos2d.h>
#include "..\base\ds_structs.h"
#include "..\base\global_definition.h"
#include "data_definition.h"

USING_NS_CC;

class DefinitionLibrary : public Ref
{

private:

	Map<int, ExcelDefinition*>* _levelPrestDefinitions;
	Map<int, ExcelDefinition*>* _levelTypeDefinitions;
	Map<int, ExcelDefinition*>* _objectDefinitions;
	Map<int, ExcelDefinition*>* _objectInstanceDefinitions;

	static DefinitionLibrary * _instance;


public:

	static DefinitionLibrary * getInstance();
	virtual ~DefinitionLibrary();

	void loadResources();

	ExcelDefinition * getLevelPrestDefinition(int defId);
	ExcelDefinition * getLevelTypeDefinition(int defId);
	ExcelDefinition * getObjectDefinition(int defId);
	ExcelDefinition * getObjectInstanceDefinition(int defId);

};

#endif