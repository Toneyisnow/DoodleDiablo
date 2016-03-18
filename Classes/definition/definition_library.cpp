#include "definition_library.h"

DefinitionLibrary *DefinitionLibrary::_instance = NULL;


DefinitionLibrary * DefinitionLibrary::getInstance()
{
	if (_instance == NULL)
	{
		_instance = new DefinitionLibrary();
	}

	return _instance;
}

DefinitionLibrary::~DefinitionLibrary()
{

}

void DefinitionLibrary::loadResources()
{
	_levelPrestDefinitions = LevelPrestDefinition::load("data\\global\\excel\\LvlPrest.txt");
	if (_levelPrestDefinitions == NULL)
	{
		log("Loading for _levelPrestDefinitions has failed.");
	}

	_levelTypeDefinitions = LevelTypeDefinition::load("data\\global\\excel\\LvlTypes.txt");
	if (_levelTypeDefinitions == NULL)
	{
		log("Loading for _levelTypeDefinitions has failed.");
	}
	
	_objectDefinitions = ObjectsDefinition::load("data\\global\\excel\\objects.txt");
	if (_objectDefinitions == NULL)
	{
		log("Loading for _objectDefinitions has failed.");
	}
	
	_objectInstanceDefinitions = ObjectInstanceDefinition::load("data\\global\\excel\\ObjectInstance.txt");
	if (_objectInstanceDefinitions == NULL)
	{
		log("Loading for _objectInstanceDefinitions has failed.");
	}

}

ExcelDefinition * DefinitionLibrary::getLevelPrestDefinition(int defId)
{
	if (_levelPrestDefinitions == NULL)
	{
		return NULL;
	}

	ExcelDefinition* def = this->_levelPrestDefinitions->at(defId);
	return def;
}


ExcelDefinition * DefinitionLibrary::getLevelTypeDefinition(int defId)
{
	if (_levelTypeDefinitions == NULL)
	{
		return NULL;
	}

	ExcelDefinition* def = this->_levelTypeDefinitions->at(defId);
	return def;
}

ExcelDefinition * DefinitionLibrary::getObjectDefinition(int defId)
{
	if (_objectDefinitions == NULL)
	{
		return NULL;
	}

	ExcelDefinition* def = this->_objectDefinitions->at(defId);
	return def;
}


ExcelDefinition * DefinitionLibrary::getObjectInstanceDefinition(int defId)
{
	if (_objectInstanceDefinitions == NULL)
	{
		return NULL;
	}

	ExcelDefinition* def = this->_objectInstanceDefinitions->at(defId);
	return def;
}