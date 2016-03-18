#include "data_definition.h"

//////////////////////  LevelPrestDefinition  ////////////////

Map<int, ExcelDefinition*>* LevelPrestDefinition::load(const char * resourceKey)
{
	return ExcelDefinition::load(resourceKey, LevelPrestColumnCount, LevelPrestTypes, LevelPrestColumns::LevelPrest_Def);
}

int LevelPrestDefinition::getFileIndex(int fileNumber)
{
	return fileNumber + 15;
}

//////////////////////  LevelTypeDefinition  ////////////////

Map<int, ExcelDefinition*>* LevelTypeDefinition::load(const char * resourceKey)
{
	return ExcelDefinition::load(resourceKey, LevelTypeColumnCount, LevelTypeTypes, LevelTypeColumns::LevelType_Id);
}

int LevelTypeDefinition::getFileIndex(int fileNumber)
{
	return fileNumber + 2;
}


//////////////////////  ObjectsDefinition  ////////////////

Map<int, ExcelDefinition*>* ObjectsDefinition::load(const char * resourceKey)
{
	return ExcelDefinition::load(resourceKey, ObjectsColumnCount, ObjectsTypes, ObjectsColumns::ObjectsColumns_Id);
}

//////////////////////  ObjectInstanceDefinition  ////////////////

Map<int, ExcelDefinition*>* ObjectInstanceDefinition::load(const char * resourceKey)
{
	return ExcelDefinition::load(resourceKey, ObjectInstanceColumnCount, ObjectInstanceTypes, -1, ObjectInstanceDefinition::generateKey);
}

int ObjectInstanceDefinition::generateKey(ExcelDefinition *def)
{
	return ObjectInstanceDefinition::generateKey(def->getIntValue(ObjectInstanceColumns::ObjectInstance_Act), def->getIntValue(ObjectInstanceColumns::ObjectInstance_Type), def->getIntValue(ObjectInstanceColumns::ObjectInstance_Id));
}

int ObjectInstanceDefinition::generateKey(int act, int type, int id)
{
	// The key for Object Mapping: Act + Type + Id
	int a = id << 7;
	int b = act << 2;
	return ((id << 7) + (act << 2) + type);
}