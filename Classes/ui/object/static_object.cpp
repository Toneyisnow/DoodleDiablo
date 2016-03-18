#include "static_object.h"
#include "..\..\definition\definition_library.h"
#include "..\..\definition\data_definition.h"

StaticObject::StaticObject(int act, long type, long id, Vec2 subtilepos)
{
	this->_act = act;
	this->_type = type;
	this->_id = id;
	this->_subtile_position = subtilepos;
	
	// Initialize
	this->_path_num = 0;
	this->_desc_idx = -1;
	this->_flags = 0;
	this->_frame_delta = rand() % 256;
	this->_label = new StaticObjectLabel();

	int key = ObjectInstanceDefinition::generateKey(act, type, id);
	ExcelDefinition * objectMapping = DefinitionLibrary::getInstance()->getObjectInstanceDefinition(key);

	char * mode = objectMapping->getStringValue(ObjectInstanceColumns::ObjectInstance_Mode);
	this->_action = CompositeObject::parseAnimationAction(mode);

	// Retrieve the token
	int objectId = objectMapping->getIntValue(ObjectInstanceColumns::ObjectInstance_ObjectId);

	if (objectId > 0)
	{
		ExcelDefinition * object = DefinitionLibrary::getInstance()->getObjectDefinition(objectId);
		this->_token = object->getStringValue(ObjectsColumns::ObjectsColumns_Token);
	}
	else
	{
		this->_token = NULL;
	}
}

StaticObject::~StaticObject()
{
	this->_label->release();
}

void StaticObject::setType(long t)
{
	this->_type = t;
}

void StaticObject::setId(long id)
{
	this->_id = id;
}

void StaticObject::setSubtilePosition(Vec2 subtilepos)
{
	this->_subtile_position = subtilepos;
}

void StaticObject::setDsFlags(long flags)
{
	this->_ds1_flags = flags;
}

long StaticObject::getId()
{
	return this->_id;
}

AnimationGenera StaticObject::getGenera()
{
	// This should be overridden by sub class
	return AnimationGenera::AnimationGenera_Object;
}

Vec2 StaticObject::getSubtilePosition()
{
	return this->_subtile_position;
}
