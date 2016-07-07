#include "creature.h"


Creature::Creature(char * defId)
	: CompositeObject(defId)
{

}

Creature::~Creature()
{

}

void Creature::mainTick(float delta)
{
	CompositeObject::mainTick(delta);
}