#ifndef _CREATURE_H_
#define _CREATURE_H_

#include <cocos2d.h>
#include "composite_object.h"

USING_NS_CC;

class Creature : public CompositeObject
{

protected:

	// Not used?
	CreatureAction _action;

public:

	Creature(char * defId);
	virtual ~Creature();

	void takeTick(float delta);
};

#endif