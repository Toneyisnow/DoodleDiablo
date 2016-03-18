

#include "character_definition.h"

CharacterDefinition::CharacterDefinition()
{

}
CharacterDefinition::~CharacterDefinition()
{

}


CharacterDefinition* CharacterDefinition::load(char * defId)
{
	CharacterDefinition *def = new	CharacterDefinition();
	def->_defId = defId;

	return def;
}

char * CharacterDefinition::getId()
{
	return _defId;
}