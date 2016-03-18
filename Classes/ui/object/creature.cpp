#include "creature.h"


Creature::Creature(char * defId)
	: CompositeObject(defId)
{

}

Creature::~Creature()
{

}

void Creature::takeTick(float delta)
{
	CompositeObject::takeTick(delta);
}